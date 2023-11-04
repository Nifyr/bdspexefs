#pragma once

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "ServerCommandExecutor.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ServerCommandPutter_c;

            struct ServerCommandPutter_Fields {
                struct MainModule_o* m_pMainModule;
                struct BattleEnv_o* m_pBattleEnv;
                struct ServerCommandQueue_o* m_pQueue;
                struct ServerCommandExecutor_o* m_pExecutor;
            };

            struct ServerCommandPutter_o
            {
                ServerCommandPutter_c *klass;
                void *monitor;
                ServerCommandPutter_Fields fields;

                void Act_ChangeForm(uint8_t pokeID, MethodInfo *method);
                void AddTokuseiHandler(uint8_t pokeID, MethodInfo *method);
                bool AddWazaHandler(uint8_t pokeID, int32_t waza, uint32_t subPri, MethodInfo *method);
                void ChangeForm(uint8_t pokeID, uint8_t formNo, bool dontResetFormByOut, MethodInfo *method);
                void IncBattleCount(uint8_t counterID, MethodInfo *method);
                void InsertWazaInfo(uint8_t pokeID, bool isTokuseiWindowDisplay, StrParam_o **message, MethodInfo *method);
                bool Message(StrParam_o **strParam, MethodInfo *method);
                void Message_Std(uint16_t strID, MethodInfo *method);
                void Message_Std(uint16_t strID, int32_t arg1, int32_t arg2, MethodInfo *method);
                void RemoveTokuseiHandler(uint8_t pokeID, MethodInfo *method);
                void RemoveWazaHandler(uint8_t pokeID, int32_t waza, MethodInfo *method);
                void SetBppCounter(BTL_POKEPARAM_o *poke, int32_t counterID, uint8_t value, MethodInfo *method);
                void SetContFlag(BTL_POKEPARAM_o *poke, int32_t flag, MethodInfo *method);
                void TokWin_In(BTL_POKEPARAM_o *poke, MethodInfo *method);
                void TokWin_Out(BTL_POKEPARAM_o *poke, MethodInfo *method);
            };

            struct ServerCommandPutter {
                static void SCQUE_PUT_OP_ChangeForm(ServerCommandQueue_o *queue, uint8_t pokeID, uint8_t formNo, bool dontResetFormByOut, MethodInfo *method);
            };
        }
    }
}