#pragma once 

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PokeResult_c;

            struct PokeResult_Fields {
                uint16_t totalTurnCount;
                uint16_t criticalCount;
                uint16_t totalDamageRecieved;
                uint16_t deadCount;
            };

            struct PokeResult_o {
                PokeResult_c *klass;
                void *monitor;
                PokeResult_Fields fields;
            };
            
            struct PokeResult_array {
                Il2CppObject obj;
                Il2CppArrayBounds *bounds;
                il2cpp_array_size_t max_length;
                PokeResult_o* m_Items[65535];
            };
        }
    }
}