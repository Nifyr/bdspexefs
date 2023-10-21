#pragma once

#include <string>
#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "System/Array.hpp"

using namespace Dpr::Battle::Logic;

// FUN_0009acf0
void * _system_array_new(void * typeInfo, uint32_t len);
// thunk_FUN_0007d9c0
void _system_array_init(void * array);
// void FUN_000502c0(ulong param_1)
void _system_load_typeinfo(void * typeInfo);

void il2cpp_object_init(void * arg0, void * arg1);


// thunk_FUN_00048708?
// 00048708
void il2cpp_runtime_class_init(void *param_1);

void system_load_typeinfo(void * typeInfo);
void * system_array_new(void * typeInfo, uint32_t len);

extern void * System_Int64_array_TypeInfo;
extern void * System_Byte_array_TypeInfo;

MethodInfo * copyMethodInfo(MethodInfo * src, Il2CppMethodPointer methodPointer);
uint32_t GetBadgeCount();
EventFactor_EventHandlerTable_o * CreateEventHandler(uint16_t eventID, MethodInfo * src, Il2CppMethodPointer methodPointer);
System::Array<EventFactor_EventHandlerTable_o *> * CreateEventHandlerTable(uint32_t size);
uint8_t HighestMultiple(uint8_t max, uint8_t factor);
bool HandlerAddFieldEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t effect, uint8_t turns);
void HandlerAddPosEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID);
void HandlerAddSick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t targetPokeID, int32_t sickID, int64_t sickCont);
void HandlerDamage(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID, uint16_t damage, bool disableDeadProcess, bool displayAbility);
void HandlerCureSick(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, int32_t sickID, uint8_t targetPokeID);
void HandlerFormChange(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t nextForm, bool persistOnSwitch, bool displayAbility, bool animationEnabled);
void HandlerMessage(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool displayAbility);
void HandlerRankEffect(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID, int32_t rankType, int8_t rankVolume, bool displayAbility, bool ignoreSubstitute, bool messageOnFail);
void HandlerRankReset(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID);
void HandlerShrink(EventFactor_EventHandlerArgs_o **args, uint8_t targetPokeID, uint8_t percentage);
System_Int64_array *NewInt64Array(uint32_t len);