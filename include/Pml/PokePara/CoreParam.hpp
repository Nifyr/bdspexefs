#pragma once

#include "il2cpp.hpp"

namespace Pml
{
    namespace PokePara
    {
        struct CoreParam_FormChangeResult_o;

        struct CoreParam_o {
            void ChangeFormNo(uint16_t nextFormno, CoreParam_FormChangeResult_o *pResult, MethodInfo *method);
            bool EndFastMode(bool validFlag, MethodInfo *method);
            int32_t GetTokuseiNo(MethodInfo *method);
            bool StartFastMode(MethodInfo *method);
        };
    }
}