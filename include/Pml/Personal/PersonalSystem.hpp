#pragma once

#include "XLSXContent/PersonalTable/SheetPersonal.hpp"

namespace Pml
{
    namespace Personal
    {
        struct PersonalSystem
        {
            static bool CheckPersonalWazaMachine(uint16_t machineNo, MethodInfo *method);
            static XLSXContent::PersonalTable::SheetPersonal_o * GetPersonalData(int32_t monsno, uint16_t formno, MethodInfo *method);
            static uint8_t GetWazaOboeNum(MethodInfo *method);
            static uint16_t GetWazaOboeWazaNo(uint16_t index, MethodInfo *method);
            static void LoadPersonalData(int32_t monsno, uint16_t formno, MethodInfo *method);
            static void LoadWazaOboeData(int32_t monsno, uint16_t formno, MethodInfo *method);
        };
    }
}