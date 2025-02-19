#pragma once

#include <string>
#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_SICKCONT.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "System/Array.hpp"

using namespace Dpr::Battle::Logic;

void * _system_array_new(void * typeInfo, uint32_t len);

void _system_array_init(void * array);

void _system_load_typeinfo(void * typeInfo);

void il2cpp_object_init(void * arg0, void * arg1);

void il2cpp_runtime_class_init(void *typeInfo);

void system_load_typeinfo(void * typeInfo);

void system_array_init(void *array);

void * system_array_new(void * typeInfo, uint32_t len);

extern void * System_Int64_array_TypeInfo;
extern void * System_UInt32_array_TypeInfo;
extern void * System_Int32_array_TypeInfo;
extern void * System_Byte_array_TypeInfo;

MethodInfo * copyMethodInfo(MethodInfo * src, Il2CppMethodPointer methodPointer);
uint32_t GetBadgeCount();
uint8_t RKSSystemType(uint32_t itemNo);
uint8_t MultitypeType(uint32_t itemNo);
EventFactor_EventHandlerTable_o * CreateEventHandler(uint16_t eventID, MethodInfo * src, Il2CppMethodPointer methodPointer);
System::Array<EventFactor_EventHandlerTable_o *> * CreateEventHandlerTable(uint32_t size);
void EnsureClassInit(void *typeInfo);
void EnsureTypeInfoInit(bool *datBool, uint64_t datPtr);
uint8_t HighestMultiple(uint8_t max, uint8_t factor);
bool HandlerAddFieldEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t effect, uint8_t turns);
void HandlerAddPosEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID);
void HandlerAddSick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t targetPokeID, int32_t sickID, int64_t sickCont);
bool HandlerAddSideEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t effect, int32_t side, BTL_SICKCONT_o cont);
void HandlerDamage(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID, uint16_t damage, bool disableDeadProcess, bool displayAbility);
void HandlerCureSick(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, int32_t sickID, uint8_t targetPokeID);
void HandlerFormChange(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t nextForm, bool persistOnSwitch, bool displayAbility, bool animationEnabled);
void HandlerMessage(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool displayAbility);
void HandlerRankEffect(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID, int32_t rankType, int8_t rankVolume, bool displayAbility, bool ignoreSubstitute, bool messageOnFail, bool byWazaEffect);
void HandlerRankReset(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID);
void HandlerRankResetAll(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID);
void HandlerShrink(EventFactor_EventHandlerArgs_o **args, uint8_t targetPokeID, uint8_t percentage);
System_Int64_array *NewInt64Array(uint32_t len);