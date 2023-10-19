#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BTL_PARTY_c;

            struct BTL_PARTY_Fields {
                struct Dpr_Battle_Logic_BTL_POKEPARAM_array* m_pMember;
                uint8_t m_memberCount;
            };

            struct BTL_PARTY_o {
                BTL_PARTY_c *klass;
                void *monitor;
                BTL_PARTY_Fields fields;

                BTL_POKEPARAM_o *GetMemberDataConst(uint8_t idx, MethodInfo *method);
            };
        }
    }
}