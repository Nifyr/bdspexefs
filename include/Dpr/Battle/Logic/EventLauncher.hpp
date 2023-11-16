#pragma once

#include "il2cpp.hpp"
#include "PokeAction.hpp"
#include "EventSystem.hpp"
#include "WazaParam.hpp"

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
                uint16_t Event_getAttackPower(BTL_POKEPARAM_o *attacker, BTL_POKEPARAM_o *defender, WazaParam_o *wazaParam, bool isCritical, bool *isYakedoDisable, MethodInfo *method);
                uint16_t Event_getDefenderGuard(BTL_POKEPARAM_o *attacker, BTL_POKEPARAM_o *defender, WazaParam_o *wazaParam, bool isCritical, MethodInfo *method);
                void Event_GetWazaParam(int32_t waza, int32_t orgWaza, int32_t gSrcWaza, int32_t wazaPri, BTL_POKEPARAM_o *attacker, WazaParam_o *param, MethodInfo *method);
                uint16_t Event_getWazaPower(BTL_POKEPARAM_o *attacker, BTL_POKEPARAM_o *defender, WazaParam_o *wazaParam, MethodInfo *method);
                uint8_t Event_GetWazaPriority(int32_t waza, BTL_POKEPARAM_o *bpp, MethodInfo *method);
            };
        }
    }
}