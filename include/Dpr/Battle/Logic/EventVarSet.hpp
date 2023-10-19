#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct EventVarSet_c;

            struct EventVarSet_Fields {
                struct EventVar_array* m_pVariables;
            };

            struct EventVarSet_o {
                EventVarSet_c *klass;
                void *monitor;
                EventVarSet_Fields fields;
            };
        }
    }
}