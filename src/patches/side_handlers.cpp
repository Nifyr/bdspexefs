#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/SICKCONT.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"
#include "logger.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;

// Template MethodInfo
extern MethodInfo * handler_rainbow;

// WorkIdx
constexpr uint8_t A = 0;
constexpr uint8_t B = 1;
constexpr uint8_t C = 2;
constexpr uint8_t D = 3;
constexpr uint8_t E = 4;
constexpr uint8_t WORKIDX_SICKCONT_LOW = 5;
constexpr uint8_t WORKIDX_SICKCONT_HIGH = 6;

// BtlSideEffectID
constexpr int32_t G_MAX_CANNONADE_SIDE = 22;
constexpr int32_t G_MAX_VINE_LASH_SIDE = 23;

// TempTargetPriorityIDs
constexpr uint8_t WAZA_2_TEMPT_TARGET_PRIORITY = 3;

// TempTargetCauseIDs
constexpr uint8_t OTHER_TEMPT_TARGET_CAUSE = 3;

// PokeIDs
constexpr uint8_t NULL_POKEID = 31;

// TypeIDs
constexpr uint8_t NORMAL = 0;
constexpr uint8_t FIGHTING = 1;
constexpr uint8_t FLYING = 2;
constexpr uint8_t POISON = 3;
constexpr uint8_t GROUND = 4;
constexpr uint8_t ROCK = 5;
constexpr uint8_t BUG = 6;
constexpr uint8_t GHOST = 7;
constexpr uint8_t STEEL = 8;
constexpr uint8_t FIRE = 9;
constexpr uint8_t WATER = 10;
constexpr uint8_t GRASS = 11;
constexpr uint8_t ELECTRIC = 12;
constexpr uint8_t PSYCHIC = 13;
constexpr uint8_t ICE = 14;
constexpr uint8_t DRAGON = 15;
constexpr uint8_t DARK = 16;
constexpr uint8_t FAIRY = 17;
constexpr uint8_t NULL_TYPE = 18;

// HanderTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGMaxCannonadeSide;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGMaxVineLashSide;

// --- EventHandler delegates ---
// Lucky Chant
void Dpr_Battle_Logic_Handler_Side_handler_side_Omajinai(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr);
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
}
// Spotlight
void Dpr_Battle_Logic_Handler_Side_handler_SpotLight_TemptTarget(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr);
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    BTL_SICKCONT_o cont = (*args)->fields.pBattleEnv->
            GetSideEffectStatus(mySide, Common::GetSubID(args, nullptr),
                                nullptr)->GetContParam(nullptr);
    Common::RewriteEventVar(args, EventVar::POKEID_DEF, SICKCONT::GetPokeID(&cont, nullptr),
                            nullptr);
    Common::RewriteEventVar(args, EventVar::TEMPT_TARGET_PRIORITY, WAZA_2_TEMPT_TARGET_PRIORITY,
                            nullptr);
    Common::RewriteEventVar(args, EventVar::TEMPT_TARGET_CAUSE, OTHER_TEMPT_TARGET_CAUSE, nullptr);
}
// G-Max Wildfire
void Dpr_Battle_Logic_Handler_Side_handler_side_GShock_Honoo(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID, nullptr);
    if (pokeID == NULL_POKEID) return;
    if (!Common::IsExistPoke(args, &pokeID, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->IsMatchType(FIRE, nullptr)) return;
    HandlerDamage(args, NULL_POKEID, pokeID,
                  Calc::QuotMaxHP(bpp, 6, true, nullptr), false,
                  false);
}
// G-Max Volcalith
void Dpr_Battle_Logic_Handler_Side_handler_side_GShock_Iwa(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID, nullptr);
    if (pokeID == NULL_POKEID) return;
    if (!Common::IsExistPoke(args, &pokeID, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->IsMatchType(ROCK, nullptr)) return;
    HandlerDamage(args, NULL_POKEID, pokeID,
                  Calc::QuotMaxHP(bpp, 6, true, nullptr), false,
                  false);
}
// G-Max Cannonade
void HandlerGMaxCannonadeSideTurncheckBegin(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID, nullptr);
    if (pokeID == NULL_POKEID) return;
    if (!Common::IsExistPoke(args, &pokeID, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->IsMatchType(WATER, nullptr)) return;
    HandlerDamage(args, NULL_POKEID, pokeID,
                  Calc::QuotMaxHP(bpp, 6, true, nullptr), false,
                  false);
}
// G-Max Vine Lash
void HandlerGMaxVineLashSideTurncheckBegin(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID, nullptr);
    if (pokeID == NULL_POKEID) return;
    if (!Common::IsExistPoke(args, &pokeID, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->IsMatchType(GRASS, nullptr)) return;
    HandlerDamage(args, NULL_POKEID, pokeID,
                  Calc::QuotMaxHP(bpp, 6, true, nullptr), false,
                  false);
}

EventFactor_EventHandlerTable_o * CreateSideEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, handler_rainbow, methodPointer);
}

// --- HandlerGetFunc delegates ---
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GMaxCannonadeSide(MethodInfo *method) {
    if (sHandlerTableGMaxCannonadeSide == nullptr) {
        sHandlerTableGMaxCannonadeSide = CreateEventHandlerTable(1);
        sHandlerTableGMaxCannonadeSide->m_Items[0] = CreateSideEventHandler(EventID::TURNCHECK_BEGIN, (Il2CppMethodPointer) &HandlerGMaxCannonadeSideTurncheckBegin);
    }
    return sHandlerTableGMaxCannonadeSide;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GMaxVineLashSide(MethodInfo *method) {
    if (sHandlerTableGMaxVineLashSide == nullptr) {
        sHandlerTableGMaxVineLashSide = CreateEventHandlerTable(1);
        sHandlerTableGMaxVineLashSide->m_Items[0] = CreateSideEventHandler(EventID::TURNCHECK_BEGIN, (Il2CppMethodPointer) &HandlerGMaxVineLashSideTurncheckBegin);
    }
    return sHandlerTableGMaxVineLashSide;
}

// Adds an entry to GET_FUNC_TABLE
void SetSideFunctionTable(System::Array<Side_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t effect, Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Method_ADD_SIDE_AuroraVeil, methodPointer);
    Side_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    auto * func = (Side_HandlerGetFunc_o *) il2cpp_object_new(Side_HandlerGetFunc_TypeInfo);
    func->ctor((intptr_t)methodPointer, method);
    elem->fields.eff = effect;
    elem->fields.func = func;
    *idx += 1;
}

// Remember to update when adding handlers
constexpr uint32_t NEW_SIDE_EFFECTS_COUNT = 2;

// Entry point. Replaces system_array_new.
void * Side_system_array_new(void * typeInfo, uint32_t len) {
    auto * getFuncTable = (System::Array<Side_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_SIDE_EFFECTS_COUNT);
    uint32_t idx = len;

    //0
    SetSideFunctionTable(getFuncTable, &idx, G_MAX_CANNONADE_SIDE, (Il2CppMethodPointer) &ADD_GMaxCannonadeSide);
    SetSideFunctionTable(getFuncTable, &idx, G_MAX_VINE_LASH_SIDE, (Il2CppMethodPointer) &ADD_GMaxVineLashSide);

    socket_log_fmt("%i/%i side HandlerGetFunc delegates added", NEW_SIDE_EFFECTS_COUNT, idx - len);

    return getFuncTable;
}
