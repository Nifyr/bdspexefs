#pragma once

#include "il2cpp.hpp"
#include "PokeAction.hpp"
#include "EventSystem.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct EventLauncher_c;

            struct EventLauncher_Fields {
                struct Dpr_Battle_Logic_MainModule_o* m_pMainModule;
                struct EventSystem_o* m_pEventSystem;
                struct Dpr_Battle_Logic_BattleEnv_o* m_pBattleEnv;
            };

            struct EventLauncher_o {
                EventLauncher_c *klass;
                void *monitor;
                EventLauncher_Fields fields;

                void Event_ActProcCanceled(PokeAction_o *action, MethodInfo *method);
                void Event_ActProcEnd(BTL_POKEPARAM_o *bpp, int32_t actionCmd, MethodInfo *method);
                void Event_ActProcStart(PokeAction_o *action, MethodInfo *method);
                uint32_t Event_CheckSpecialWazaAdditionalPer(uint8_t atkPokeID, uint8_t defPokeID, uint32_t defaultPer, MethodInfo *method);
                void Event_GetWazaParam(int32_t waza, int32_t orgWaza, int32_t gSrcWaza, int32_t wazaPri, BTL_POKEPARAM_o *attacker, WazaParam_o *param, MethodInfo *method);
            };
        }
    }
}