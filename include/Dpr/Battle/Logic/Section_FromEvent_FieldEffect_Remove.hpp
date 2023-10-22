#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_FieldEffect_Remove_Description_c;

            struct Section_FromEvent_FieldEffect_Remove_Description_Fields {
                int32_t effect;
                struct BTL_POKEPARAM_o* pDependPoke;
            };

            struct Section_FromEvent_FieldEffect_Remove_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_FieldEffect_Remove_Description_c *klass;
                void *monitor;
                Section_FromEvent_FieldEffect_Remove_Description_Fields fields;
            };

            extern void *Section_FromEvent_FieldEffect_Remove_Description_TypeInfo;
        }
    }
}