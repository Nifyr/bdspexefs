#pragma once

#include "il2cpp.hpp"
#include "BTL_SICKCONT.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct SICKCONT {
                static uint8_t GetPokeID(BTL_SICKCONT_o *cont, MethodInfo *method);
                static BTL_SICKCONT_o MakePokeTurn(uint8_t causePokeID, uint8_t pokeID, uint8_t turns, MethodInfo *method);
                static BTL_SICKCONT_o MakeTurnParam(uint8_t causePokeID, uint8_t turns, uint16_t param, MethodInfo *method);
                static BTL_SICKCONT_o MakeTurn(uint8_t causePokeID, uint8_t turns, MethodInfo *method);
            };
        }
    }
}