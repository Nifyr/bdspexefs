#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "Pml/PokePara/PokemonParam.h"

namespace Pml
{
    struct PokeParty_Fields {
        System::Array<Pml::PokePara::PokemonParam_o *> * m_member;
        uint32_t m_memberCount;
        uint8_t markingIndex;
    };

    struct PokeParty_c;

    struct PokeParty_o {
        // 0249e980
        void CopyFrom(PokeParty_o *src, MethodInfo *method);
        Pml::PokePara::PokemonParam_o * GetMemberPointer(uint32_t idx, MethodInfo * method);

        void ctor(MethodInfo* method);

        PokeParty_c *klass;
        void *monitor;
        PokeParty_Fields fields;
    };

    struct PokeParty_array {
        Il2CppObject obj;
        Il2CppArrayBounds *bounds;
        il2cpp_array_size_t max_length;
        PokeParty_o* m_Items[65535];
    };

    extern void ** PTR_PokeParty_TypeInfo;
}