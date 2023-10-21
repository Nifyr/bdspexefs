#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            namespace Handler
            {
                struct Field
                {
                    static bool common_isGroundEffective(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                };
            }
        }
    }
}