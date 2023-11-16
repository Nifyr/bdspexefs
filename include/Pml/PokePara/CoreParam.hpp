#pragma once

#include "il2cpp.hpp"
#include "Pml/PokePara/CoreParam.h"
#include "System/Collections/Generic/HashSet.hpp"

using namespace System::Collections::Generic;

namespace Pml
{
    namespace PokePara
    {
        struct CoreParam_FormChangeResult_o;

        struct CoreParam_o {
            CoreParam_c *klass;
            void *monitor;
            CoreParam_Fields fields;

            uint8_t CalcLevel(MethodInfo *method);
            void ChangeFormNo(uint16_t nextFormno, CoreParam_FormChangeResult_o *pResult, MethodInfo *method);
            void ChangeMonsNo(int32_t newMonsno, uint16_t newFormno, MethodInfo *method);
            void CloseUpWazaPos(MethodInfo *method);
            bool EndFastMode(bool validFlag, MethodInfo *method);
            uint16_t GetFormNo(MethodInfo *method);
            uint32_t GetHp(MethodInfo *method);
            uint32_t GetMaxHp(MethodInfo *method);
            int32_t GetMonsNo(MethodInfo *method);
            uint32_t GetSick(MethodInfo *method);
            int32_t GetTamagoWazaNo(uint8_t index, MethodInfo *method);
            int32_t GetTokuseiNo(MethodInfo *method);
            uint8_t GetWazaCount(MethodInfo *method);
            uint8_t GetWazaIndex(int32_t wazano, MethodInfo *method);
            uint32_t GetWazaMaxPP(uint8_t index, MethodInfo *method);
            int32_t GetWazaNo(uint8_t index, MethodInfo *method);
            bool IsHpZero(MethodInfo *method);
            void RecoverHp(uint32_t value, MethodInfo *method);
            void SetWaza(uint8_t wazaIndex, int32_t wazano, MethodInfo *method);
            void SetWazaPP(uint8_t wazaIndex, uint8_t value, MethodInfo *method);
            void SetWazaPPUpCount(uint8_t wazaIndex, uint8_t value, MethodInfo *method);
            bool StartFastMode(MethodInfo *method);
            void UpdateCalcDatas(bool keepDead, MethodInfo *method);
        };
    }
}