#pragma once

#include "il2cpp.hpp"
#include "Section.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_Shrink_Description_c;

            struct Section_FromEvent_Shrink_Description_Fields {
                uint8_t pokeID;
                uint8_t percentage;
            };

            struct Section_FromEvent_Shrink_Description_o {
                Section_FromEvent_Shrink_Description_c *klass;
                void *monitor;
                Section_FromEvent_Shrink_Description_Fields fields;

                void ctor(MethodInfo *method);
            };

            extern void *Section_FromEvent_Shrink_Description_TypeInfo;
        }
    }
}