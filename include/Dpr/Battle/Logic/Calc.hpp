#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"
#include "Dpr/Battle/Logic/BTL_SICKCONT.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Calc
            {
                static uint32_t DamageBase(uint32_t wazaPower, uint32_t atkPower, uint32_t atkLevel, uint32_t defGuard, MethodInfo *method);
                static uint32_t GetRand(uint32_t range, MethodInfo * method);
                static bool IsOccurPer(uint32_t per, MethodInfo *method);
                static int32_t ITEM_GetParam(uint16_t item, int32_t paramID, MethodInfo *method);
                static bool ITEM_IsBall(uint16_t itemID, MethodInfo *method);
                static bool ITEM_IsMail(uint16_t item,MethodInfo *method);
                static BTL_SICKCONT_o MakeDefaultPokeSickCont(uint32_t sick, uint8_t causePokeID, bool isCantUseRand, MethodInfo *method);
                static uint32_t MulRatio(uint32_t value, int32_t ratio, MethodInfo *method);
                static uint32_t PERSONAL_GetParam(int32_t mons_no, int32_t form_no, int32_t paramID, MethodInfo *method);
                static uint32_t QuotMaxHP(BTL_POKEPARAM_o *bpp, uint32_t denom, bool useBeforeGParam, MethodInfo *method);
                static uint32_t QuotMaxHP_Zero(BTL_POKEPARAM_o *bpp, uint32_t denom, bool useBeforeGParam, MethodInfo *method);
                static uint32_t RandRange(uint32_t min, uint32_t max, MethodInfo *method);
            };

            extern void* Calc_TypeInfo;
        }
    }
}