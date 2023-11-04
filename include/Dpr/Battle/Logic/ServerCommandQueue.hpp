#pragma once

#include "il2cpp.hpp"
#include "InsertActionInfo.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ServerCommandQueue_o {
                void Put_ToReservedPos(uint16_t pos, uint16_t cmd, System_Int32_array *LegacyParamArray, MethodInfo *method);
                uint16_t ReservePutPos(uint16_t cmd, MethodInfo *method);
            };
        }
    }
}