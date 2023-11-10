#pragma once

#include "il2cpp.hpp"

namespace Pml
{
    namespace PokePara
    {
        struct CoreParam_FormChangeResult_o;

        struct CoreParam_o {
            void ChangeFormNo(uint16_t nextFormno, CoreParam_FormChangeResult_o *pResult, MethodInfo *method);
            void CloseUpWazaPos(MethodInfo *method);
            bool EndFastMode(bool validFlag, MethodInfo *method);
            uint16_t GetFormNo(MethodInfo *method);
            int32_t GetMonsNo(MethodInfo *method);
            uint32_t GetSick(MethodInfo *method);
            int32_t GetTokuseiNo(MethodInfo *method);
            uint8_t GetWazaCount(MethodInfo *method);
            uint8_t GetWazaIndex(int32_t wazano, MethodInfo *method);
            uint32_t GetWazaMaxPP(uint8_t index, MethodInfo *method);
            void SetWaza(uint8_t wazaIndex, int32_t wazano, MethodInfo *method);
            void SetWazaPP(uint8_t wazaIndex, uint8_t value, MethodInfo *method);
            void SetWazaPPUpCount(uint8_t wazaIndex, uint8_t value, MethodInfo *method);
            bool StartFastMode(MethodInfo *method);
        };
    }
}