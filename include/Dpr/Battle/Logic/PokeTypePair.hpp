#pragma once 

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PokeTypePair_Fields {
                uint16_t value;
            };

            struct PokeTypePair_o {
                PokeTypePair_Fields fields;
            };

            struct PokeTypePair {
                static PokeTypePair_o MakePure(uint8_t type,MethodInfo *method);
                static void Split(PokeTypePair_o pair, uint8_t *type1, uint8_t *type2, uint8_t *typeEx, MethodInfo *method);
            };
        }
    }
}