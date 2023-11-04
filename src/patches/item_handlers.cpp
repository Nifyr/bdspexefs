#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
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

// DexIDs
constexpr uint16_t KYOGRE = 382;
constexpr uint16_t GROUDON = 383;

// HanderTables

// --- EventHandler delegates ---
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