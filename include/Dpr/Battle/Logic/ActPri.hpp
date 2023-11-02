#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ActPri {
                static uint32_t ToHandlerPri(uint32_t priority, MethodInfo *method);
            };
        }
    }
}