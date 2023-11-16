#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Exp.hpp"
#include "ItemWork.hpp"
#include "Pml/Personal/PersonalSystem.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"
#include "logger.hpp"

using namespace Pml::Personal;

// Template MethodInfo

// WorkIdx

// ItemIDs
constexpr uint16_t EXP_CHARM = 1587;

// DexIDs
constexpr uint16_t FARFETCH_D = 83;
constexpr uint16_t KYOGRE = 382;
constexpr uint16_t GROUDON = 383;
constexpr uint16_t SIRFETCH_D = 865;

// HanderTables

// --- EventHandler delegates ---
// Leek
void Dpr_Battle_Logic_Handler_Item_handler_Naganegi(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint16_t dexID = Common::GetPokeParam(args, pokeID, nullptr)->GetMonsNo(nullptr);
    if (dexID != FARFETCH_D && dexID != SIRFETCH_D) return;
    Common::RewriteEventVar(args, EventVar::CRITICAL_RANK, Common::GetEventVar(
            args, EventVar::CRITICAL_RANK, nullptr) + 2, nullptr);
}
// Red Orb
uint8_t HandlerRedOrbGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void Dpr_Battle_Logic_Handler_Item_handler_Beniironotama_Shinka(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint16_t dexID = bpp->GetMonsNo(nullptr);
    if (dexID != GROUDON) return;
    uint8_t formID = bpp->fields.m_formNo;
    if (formID != HandlerRedOrbGetFormID(formID, 0)) return;
    uint8_t nextForm = HandlerRedOrbGetFormID(formID, 1);
    if (nextForm >= PersonalSystem::GetPersonalData(dexID, 0, nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, true,
                      false, true);
}
// Blue Orb
uint8_t HandlerBlueOrbGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void Dpr_Battle_Logic_Handler_Item_handler_Aiironotama_Shinka(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint16_t dexID = bpp->GetMonsNo(nullptr);
    if (dexID != KYOGRE) return;
    uint8_t formID = bpp->fields.m_formNo;
    if (formID != HandlerRedOrbGetFormID(formID, 0)) return;
    uint8_t nextForm = HandlerRedOrbGetFormID(formID, 1);
    if (nextForm >= PersonalSystem::GetPersonalData(dexID, 0, nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, true,
                      false, true);
}

// --- HandlerGetFunc delegates ---

// Adds an entry to GET_FUNC_TABLE

// Remember to update when adding handlers

// Entry point. Replaces system_array_new.

// --- Other functions ---
// Exp. Charm
extern bool DAT_7104cbc139;
void Dpr_Battle_Logic_Exp_CalcExp(Exp_CalcParam_o **calcParam, Exp_CalcResult_o *pResult, MethodInfo *method) {
    pResult->fields.exp = 0;
    pResult->fields.byGakusyusouti = false;
    pResult->fields.isContainBonus = false;
    Exp_CalcParam_o *ecp = *calcParam;
    bool isMatch = ecp->fields.isMatch;
    if (!isMatch && !ecp->fields.isGakusyusoutiOn) return;
    uint32_t deadPokeLevel = ecp->fields.deadPokeLevel;
    uint32_t levelCap = ecp->fields.levelCap;
    if (deadPokeLevel > levelCap)
        deadPokeLevel = levelCap;
    uint32_t exp = deadPokeLevel * ecp->fields.deadPokeExp / 5;
    if (!isMatch) {
        exp /= 2;
        pResult->fields.byGakusyusouti = true;
    }
    if (exp < 1)
        exp = 1;
    exp = Exp::getexp_calc_adjust_level(exp, ecp->fields.getPokeLevel, deadPokeLevel,
                                        nullptr);
    EnsureTypeInfoInit(&DAT_7104cbc139, 0x47a5);
    EnsureClassInit(Calc_TypeInfo);
    if (!ecp->fields.isMyPoke) {
        int32_t ratio = 0x1800;
        if (ecp->fields.playerLanguageId != ecp->fields.getPokeLanguageId)
            ratio = 0x1b33;
        exp = Calc::MulRatio(exp, ratio, nullptr);
        pResult->fields.isContainBonus = true;
    }
    if (ecp->fields.haveSiawasetamago) {
        exp = Calc::MulRatio(exp, 0x1800, nullptr);
        pResult->fields.isContainBonus = true;
    }
    if (ecp->fields.isEvoCanceledPoke) {
        exp = Calc::MulRatio(exp,0x1333,nullptr);
        pResult->fields.isContainBonus = true;
    }
    if (ecp->fields.getPokeFriendship >= 220) {
        exp = Calc::MulRatio(exp,0x1333,nullptr);
        pResult->fields.isContainBonus = true;
    }
    if (ItemWork::GetItemInfo(EXP_CHARM, nullptr)->get_count(nullptr) > 0) {
        socket_log_initialize();
        exp = Calc::MulRatio(exp,0x1800,nullptr);
        pResult->fields.isContainBonus = true;
    }
    pResult->fields.exp = exp;
}