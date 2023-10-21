#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FreeFall_Release_Description_c;

            struct Section_FreeFall_Release_Description_Fields {
                struct BTL_POKEPARAM_o* attacker;
                bool canAppearSelf;
                bool canAppearTarget;
            };

            struct Section_FreeFall_Release_Description_o {
                void ctor(MethodInfo *method);

                Section_FreeFall_Release_Description_c *klass;
                void *monitor;
                Section_FreeFall_Release_Description_Fields fields;
            };
        }
    }
}