#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Tables
            {
                static System::Array<uint16_t> * GetYubiFuruPermitTable(MethodInfo * method);
                static bool IsDaiWallGuardDisable(int32_t waza, MethodInfo *method);
                static bool IsKodawariItem(uint16_t itemID, MethodInfo *method);
                static bool IsSakidoriFailWaza(int32_t waza, MethodInfo *method);
            };
        }
    }
}