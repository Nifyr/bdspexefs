#pragma once

#include "il2cpp.hpp"
#include "BTL_FIELD_SITUATION.hpp"
#include "BTL_PARTY.hpp"
#include "BTL_POKEPARAM.hpp"
#include "EventFactor.hpp"
#include "ExPokePos.hpp"
#include "PokeAction.hpp"
#include "Section_AddSick.hpp"
#include "Section_CureSick.hpp"
#include "Section_FieldEffect_Add.hpp"
#include "Section_FreeFall_Release.hpp"
#include "Section_FromEvent_AddViewEffect.hpp"
#include "Section_FromEvent_ChangePokeType.hpp"
#include "Section_FromEvent_ConsumeItem.hpp"
#include "Section_FromEvent_Damage.hpp"
#include "Section_FromEvent_FieldEffect_Remove.hpp"
#include "Section_FromEvent_FormChange.hpp"
#include "Section_FromEvent_FreeFallStart.hpp"
#include "Section_FromEvent_Message.hpp"
#include "Section_FromEvent_PosEffect_Add.hpp"
#include "Section_FromEvent_RankEffect.hpp"
#include "Section_FromEvent_RankReset.hpp"
#include "Section_FromEvent_Shrink.hpp"
#include "Section_FromEvent_SwapItem.hpp"
#include "Section_SideEffect_Add.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Common
            {
                static bool AddFieldEffect(EventFactor_EventHandlerArgs_o **args, Section_FieldEffect_Add_Description_o **desc, MethodInfo *method);
                static bool AddPosEffect(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_PosEffect_Add_Description_o **desc, MethodInfo *method);
                static bool AddSick(EventFactor_EventHandlerArgs_o **args, Section_AddSick_Description_o **desc,MethodInfo *method);
                static bool AddSideEffect(EventFactor_EventHandlerArgs_o **args, Section_SideEffect_Add_Description_o **desc, MethodInfo *method);
                static void AddViewEffect(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_AddViewEffect_Description_o **desc, MethodInfo *method);
                static bool ChangeType(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_ChangePokeType_Description_o **desc, MethodInfo *method);
                static bool CheckFieldEffect(EventFactor_EventHandlerArgs_o **args, int32_t *effType, MethodInfo *method);
                static bool CheckItemUsable(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static uint32_t CheckPokeSick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static bool CheckShowDown(EventFactor_EventHandlerArgs_o **args, MethodInfo *method);
                static bool CheckUnbreakablePokeItem(uint16_t monsno, uint16_t itemID, MethodInfo *method);
                static void ConsumeItem(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_ConsumeItem_Description_o **desc, MethodInfo *method);
                static bool CureSick(EventFactor_EventHandlerArgs_o **args, Section_CureSick_Description_o **desc, MethodInfo *method);
                static bool Damage(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_Damage_Description_o **desc,MethodInfo *method);
                static uint8_t DecideWazaTargetAuto(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t wazano, MethodInfo *method);
                static uint8_t ExpandExistPokeID(EventFactor_EventHandlerArgs_o **args, ExPokePos_o **exPos, System_Byte_array *dst_pokeID, MethodInfo *method);
                static bool FormChange(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_FormChange_Description_o **desc,MethodInfo *method);
                static void FreeFallRelease(EventFactor_EventHandlerArgs_o **args, Section_FreeFall_Release_Description_o **desc, MethodInfo *method);
                static bool FreeFallStart(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_FreeFallStart_Description_o **desc, MethodInfo *method);
                static uint8_t GetAllOpponentFrontPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t basePokeID, System_Byte_array *dst, MethodInfo *method);
                static int32_t GetEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, MethodInfo *method);
                static void * GetEventVarAddress(EventFactor_EventHandlerArgs_o **args, uint16_t label, MethodInfo *method);
                static uint8_t GetExistFrontPokePos(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static BTL_FIELD_SITUATION_o *GetFieldSituation(EventFactor_EventHandlerArgs_o **args, MethodInfo *method);
                static uint8_t GetFrontPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t *pos, MethodInfo *method);
                static uint8_t GetGround(EventFactor_EventHandlerArgs_o **args, MethodInfo *method);
                static uint32_t GetKillCount(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static uint8_t GetLocalWeather(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static BTL_PARTY_o *GetPartyData(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static BTL_POKEPARAM_o * GetPokeParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static uint16_t GetSubID(EventFactor_EventHandlerArgs_o **args,MethodInfo *method);
                static int32_t GetWorkValue(EventFactor_EventHandlerArgs_o **args, uint8_t workIdx, MethodInfo *method);
                static bool IsExistPoke(EventFactor_EventHandlerArgs_o **args, uint8_t *pokeID, MethodInfo *method);
                static bool IsFriendPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID1, uint8_t pokeID2, MethodInfo *method);
                static void Message(EventFactor_EventHandlerArgs_o ** args, Section_FromEvent_Message::Description_o ** desc, MethodInfo * method);
                static void MulEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, int32_t value, MethodInfo *method);
                static int32_t PokeIDtoOpponentSide(EventFactor_EventHandlerArgs_o **args, uint8_t *pokeID, MethodInfo *method);
                static uint8_t PokeIDtoPokePos(EventFactor_EventHandlerArgs_o **args, uint8_t *pokeID, MethodInfo *method);
                static int32_t PokeIDtoSide(EventFactor_EventHandlerArgs_o **args, uint8_t *pokeID, MethodInfo *method);
                static bool RankEffect(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_RankEffect_Description_o **desc, MethodInfo *method);
                static bool RemoveFieldEffect(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_FieldEffect_Remove_Description_o **desc, MethodInfo *method);
                static bool RankReset(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_RankReset_Description_o **desc, MethodInfo *method);
                static bool RewriteEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, int32_t value, MethodInfo *method);
                static bool RewriteEventVar_FAIL_CAUSE(EventFactor_EventHandlerArgs_o **args, uint8_t value, MethodInfo *method);
                static PokeAction_o * SearchByPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool isSkipGStart, bool isSkipNull, MethodInfo *method);
                static void SetWorkValue(EventFactor_EventHandlerArgs_o **args, uint8_t workIdx, int32_t value ,MethodInfo *method);
                static bool Shrink(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_Shrink_Description_o **desc, MethodInfo *method);
                static bool SwapItem(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_SwapItem_Description_o **desc, MethodInfo *method);
            };

            extern void * Common_TypeInfo;
        }
    }
}