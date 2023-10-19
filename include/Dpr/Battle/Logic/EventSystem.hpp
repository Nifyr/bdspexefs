#pragma once

#include "il2cpp.hpp"
#include "EventVarSet.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct EventSystem_c;

            struct EventSystem_Fields {
                struct MainModule_o* m_pMainModule;
                struct BattleEnv_o* m_pBattleEnv;
                struct PokeActionContainer_o* m_pPokeActionContainer;
                struct PokeChangeRequest_o* m_pPokeChangeRequest;
                struct SectionContainer_o* m_pSectionContainer;
                struct SectionSharedData_o* m_pSectionSharedData;
                struct EventVarStack_o* m_variableStack;
                struct EventVarSetStack_o* m_variableSetStack;
                struct EventVarSet_o* m_pCurrentEventVarSet;
                uint32_t m_eventLevel;
            };

            struct EventSystem_o {
                EventSystem_c *klass;
                void *monitor;
                EventSystem_Fields fields;

                void CallEvent(uint16_t eventID, MethodInfo *method);
                int32_t EVENTVAR_GetValue(uint16_t label, MethodInfo *method);
                void EVENTVAR_Pop(MethodInfo *method);
                void EVENTVAR_Push(MethodInfo *method);
                void EVENTVAR_SetConstValue(uint16_t label, int32_t value, MethodInfo *method);
                void EVENTVAR_SetRewriteOnceValue(uint16_t label, int32_t value, MethodInfo *method);
            };
        }
    }
}