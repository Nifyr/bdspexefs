#pragma once

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct POKECON_o {
                BTL_POKEPARAM_o * GetPokeParam(uint8_t pokeID, MethodInfo *method);
            };
        }
    }
}