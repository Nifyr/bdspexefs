#include "Pml/PokePara/CalcTool.h"
#include "Pml/PokePara/CoreParam.hpp"
#include "Pml/WazaData/WazaDataSystem.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Pml::PokePara;
using namespace Pml::WazaData;

// DexIDs
constexpr uint16_t UNOWN = 201;
constexpr uint16_t KELDEO = 647;
constexpr uint16_t XERNEAS = 716;
constexpr uint16_t ZACIAN = 888;
constexpr uint16_t ZAMAZENTA = 889;

// ItemIDs
constexpr uint16_t RUSTED_SWORD = 1103;
constexpr uint16_t RUSTED_SHIELD = 1104;

// MoveIDs
constexpr int32_t NULL_WAZA = 0;
constexpr int32_t IRON_HEAD = 442;
constexpr int32_t SECRET_SWORD = 548;
constexpr int32_t BEHEMOTH_BLADE = 781;
constexpr int32_t BEHEMOTH_BASH = 782;

// WazaIdxIDs
constexpr uint8_t NULL_WAZA_IDX = 4;

void Dpr_Battle_Logic_POKECON_setupPokeParam(POKECON_o *__this, BTL_POKEPARAM_o *pokeParam, uint8_t pokeID,
                                             PokemonParam_o *srcParam, DefaultPowerUpDesc_o **defaultPowerUpDesc,
                                             MyStatus_o *playerData, MethodInfo *method) {
    __this->setupPokeParam(pokeParam, pokeID, srcParam, defaultPowerUpDesc, playerData, nullptr);
    auto *cp = (CoreParam_o *)pokeParam->fields.m_coreParam->fields.ppSrc;
    bool fastModeStarted = cp->StartFastMode(nullptr);
    uint16_t dexID = pokeParam->GetMonsNo(nullptr);
    uint16_t formID = pokeParam->fields.m_formNo;
    uint16_t itemID = pokeParam->GetItem(nullptr);
    if (dexID == XERNEAS && formID == 0) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
    }
    if (dexID == ZACIAN && formID == 0 && itemID == RUSTED_SWORD) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
        uint8_t wazaIdx = pokeParam->WAZA_SearchIdx(IRON_HEAD, nullptr);
        if (wazaIdx != NULL_WAZA_IDX)
            pokeParam->WAZA_UpdateID(wazaIdx, BEHEMOTH_BLADE, 0, false, nullptr);
    }
    if (dexID == ZAMAZENTA && formID == 0 && itemID == RUSTED_SHIELD) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
        uint8_t wazaIdx = pokeParam->WAZA_SearchIdx(IRON_HEAD, nullptr);
        if (wazaIdx != NULL_WAZA_IDX)
            pokeParam->WAZA_UpdateID(wazaIdx, BEHEMOTH_BASH, 0, false, nullptr);
    }
    if (dexID == KELDEO) {
        uint8_t wazaIdx = pokeParam->WAZA_SearchIdx(SECRET_SWORD, nullptr);
        uint16_t nextFormID = 1;
        if (wazaIdx == NULL_WAZA_IDX)
            nextFormID = 0;
        if (formID != nextFormID) {
            pokeParam->ChangeForm(nextFormID, true, nullptr);
            pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
            pokeParam->fields.m_coreParam->fields.defaultFormNo = nextFormID;
        }
    }
    cp->EndFastMode(fastModeStarted, nullptr);
}
extern bool DAT_7104cc0077;
void FormChange(CoreParam_o *cp, uint16_t nextFormID) {
    EnsureTypeInfoLoaded(&DAT_7104cc0077, 0x3191);
    Accessor_o *a = cp->fields.m_accessor;
    int32_t dexID = cp->GetMonsNo(nullptr);
    a->SetFormNo(nextFormID, nullptr);
    uint8_t tokuseiIndex = 0x2;
    if (!a->IsTokusei3(nullptr))
        tokuseiIndex = a->IsTokusei2(nullptr);
    EnsureClassInit(CalcTool_TypeInfo);
    a->SetTokuseiNo(CalcTool::GetTokuseiNo(dexID, nextFormID, tokuseiIndex, nullptr), nullptr);
    a->SetSex(CalcTool::GetCorrectSexInPersonalData(dexID, nextFormID, a->GetSex(nullptr), nullptr),nullptr);
    cp->UpdateCalcDatas(true, nullptr);
}
extern bool DAT_7104cc00ff;
void Pml_PokePara_CoreParam_SetWaza(CoreParam_o *__this,uint8_t wazaIndex, int32_t wazano, MethodInfo *method) {
    if (wazaIndex > 3) return;
    EnsureTypeInfoLoaded(&DAT_7104cc00ff, 0xa7c0);
    WazaTable_SheetWaza_array *wtsws = WazaDataSystem_TypeInfo->static_fields->s_wazaTable->fields.Waza;
    if ((uint32_t)wazano >= wtsws->max_length) return;
    Accessor_o *a = __this->fields.m_accessor;
    int32_t oldMoveID = a->GetWazaNo(wazaIndex, nullptr);
    a->SetWazaNo(wazaIndex, wazano, nullptr);
    a->SetWazaPPUpCount(wazaIndex, 0, nullptr);
    a->SetPP(wazaIndex, wtsws->m_Items[wazano]->fields.basePP, nullptr);
    if (__this->GetMonsNo(nullptr) != KELDEO) return;
    uint16_t formID = __this->GetFormNo(nullptr);
    uint16_t nextFormID = formID;
    if (oldMoveID == SECRET_SWORD && wazano != SECRET_SWORD)
        nextFormID = 0;
    if (oldMoveID != SECRET_SWORD && wazano == SECRET_SWORD)
        nextFormID = 1;
    if (nextFormID == formID) return;
    FormChange(__this, nextFormID);
}

void Pml_PokePara_CoreParam_RemoveWaza(CoreParam_o *__this, uint8_t wazaIndex, MethodInfo *method) {
    if (wazaIndex > 3) return;
    Accessor_o *a = __this->fields.m_accessor;
    int32_t oldMoveID = a->GetWazaNo(wazaIndex, nullptr);
    a->SetWazaNo(wazaIndex, NULL_WAZA, nullptr);
    a->SetWazaPPUpCount(wazaIndex, 0, nullptr);
    a->SetPP(wazaIndex, 0, nullptr);
    if (a->GetMonsNo(nullptr) == KELDEO && oldMoveID == SECRET_SWORD)
        FormChange(__this, 0);
}
