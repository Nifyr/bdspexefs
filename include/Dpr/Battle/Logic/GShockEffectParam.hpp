#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct GShockEffectParam_SetupParam_c;
            
            struct GShockEffectParam_SetupParam_Fields {
                struct MainModule_o* pMainModule;
                struct BattleEnv_o* pBattleEnv;
                struct ActionDesc_o* pActionDesc;
                struct WazaParam_o* pWazaParam;
                struct BTL_POKEPARAM_o* pAttaker;
                struct BTL_POKEPARAM_o* pDefender;
                uint8_t gShockEffect;
            };
            
            struct GShockEffectParam_SetupParam_o {
                GShockEffectParam_SetupParam_c *klass;
                void *monitor;
                GShockEffectParam_SetupParam_Fields fields;
                
                void ctor(MethodInfo *method);
            };

            extern void *GShockEffectParam_SetupParam_TypeInfo;
            
            struct GShockEffectParam_o {
                void ctor(GShockEffectParam_SetupParam_o **param, MethodInfo *method);
            };

            extern void *GShockEffectParam_TypeInfo;
        }
    }
}