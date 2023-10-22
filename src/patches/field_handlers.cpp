#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/FieldStatus.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;

// Template MethodInfo
extern MethodInfo * handler_elec_checkFail;

// EffectTypeID
constexpr int32_t MUD_SPORT_FIELD = 10;
constexpr int32_t WATER_SPORT_FIELD = 11;

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

// HanderTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMudSportField;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableWaterSportField;

// --- EventHandler delegates ---
// Mud Sport Field
void HandlerMudSportFieldWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t subParam, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr) != ELECTRIC) return;
    Common::MulEventVar(args, EventVar::WAZA_POWER_RATIO, (int32_t)(0x1000 * 0.33), nullptr);
}
// Water Sport Field
void HandlerWaterSportFieldWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t subParam, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr) != FIRE) return;
    Common::MulEventVar(args, EventVar::WAZA_POWER_RATIO, (int32_t)(0x1000 * 0.33), nullptr);
}

EventFactor_EventHandlerTable_o * CreateFieldEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, handler_elec_checkFail, methodPointer);
}

// --- HandlerGetFunc delegates ---
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MudSportField(MethodInfo *method) {
    if (sHandlerTableMudSportField == nullptr) {
        sHandlerTableMudSportField = CreateEventHandlerTable( 1);
        sHandlerTableMudSportField->m_Items[0] = CreateFieldEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerMudSportFieldWazaPower);
    }
    return sHandlerTableMudSportField;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_WaterSportField(MethodInfo *method) {
    if (sHandlerTableWaterSportField == nullptr) {
        sHandlerTableWaterSportField = CreateEventHandlerTable( 1);
        sHandlerTableWaterSportField->m_Items[0] = CreateFieldEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerWaterSportFieldWazaPower);
    }
    return sHandlerTableWaterSportField;
}

// Adds an entry to GET_FUNC_TABLE
void SetFieldFunctionTable(System::Array<Field_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t effect, Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Method_ADD_Fld_Ground, methodPointer);
    Field_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    auto * func = (Field_HandlerGetFunc_o *) il2cpp_object_new(Field_HandlerGetFunc_TypeInfo);
    func->ctor((intptr_t)methodPointer, method);
    elem->fields.effect = effect;
    elem->fields.func = func;
    *idx += 1;
}

// Remember to update when adding handlers
constexpr uint32_t NEW_FIELD_EFFECT_COUNT = 2;

// Entry point. Replaces system_array_new.
void * Field_system_array_new(void * typeInfo, uint32_t len) {
    auto * getFuncTable = (System::Array<Field_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_FIELD_EFFECT_COUNT);
    uint32_t idx = len;

    //0
    SetFieldFunctionTable(getFuncTable, &idx, MUD_SPORT_FIELD, (Il2CppMethodPointer) &ADD_MudSportField);
    SetFieldFunctionTable(getFuncTable, &idx, WATER_SPORT_FIELD, (Il2CppMethodPointer) &ADD_WaterSportField);

    return getFuncTable;
}

void Dpr_Battle_Logic_FieldStatus_initWork(FieldStatus_o *__this, MethodInfo *method) {
    for (uint32_t i = 0; i < 10 + NEW_FIELD_EFFECT_COUNT; ++i)
        __this->clearFactorWork((int32_t)i, nullptr);
    __this->fields.m_data->fields.weather = 0;
    __this->fields.m_data->fields.weatherTurn = 255;
    __this->fields.m_data->fields.weatherTurnCount = 0;
    __this->fields.m_data->fields.weatherCausePokeID = 31;
}