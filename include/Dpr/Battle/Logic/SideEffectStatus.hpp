#pragma once

#include "il2cpp.hpp"
#include "BTL_SICKCONT.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct SideEffectStatus_c;

            struct SideEffectStatus_Fields {
                struct SideEffectStatus_DATA_o* m_data;
            };

            struct SideEffectStatus_o {
                SideEffectStatus_c *klass;
                void *monitor;
                SideEffectStatus_Fields fields;

                BTL_SICKCONT_o GetContParam(MethodInfo *method);
            };
        }
    }
}