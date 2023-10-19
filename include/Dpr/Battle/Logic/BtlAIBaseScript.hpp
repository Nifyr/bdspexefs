#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BtlAIBaseScript_c;

            struct BtlAIBaseScript_Fields {
                int32_t p_PokeChangeEnable;
                int32_t p_Score;
                int32_t MyClientID;
            };

            struct BtlAIBaseScript_o {
                BtlAIBaseScript_c *klass;
                void *monitor;
                BtlAIBaseScript_Fields fields;

                int64_t Call(uint8_t cmd, System_Int64_array *args, MethodInfo *method);
                void ScoreCtrl(int32_t value, MethodInfo *method);
            };
        }
    }
}