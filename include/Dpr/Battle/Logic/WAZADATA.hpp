#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct WAZADATA
            {
                static int32_t GetDamageType(int32_t id, MethodInfo *method);
                static bool GetFlag(int32_t id, int32_t flag, MethodInfo *method);
                static uint32_t GetPower(int32_t id, MethodInfo *method);
                static int32_t GetSickPer(int32_t id, MethodInfo *method);
                static uint8_t GetType(int32_t id, MethodInfo *method);
                static int32_t GetWazaTarget(int32_t id, MethodInfo *method);
                static bool IsDamage(int32_t id, MethodInfo *method);
                static bool IsValid(int32_t id, MethodInfo *method);
            };
        }
    }
}