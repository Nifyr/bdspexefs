#pragma once
#include "il2cpp.hpp"
#include "Pml/PokePara/CoreParam.hpp"

using namespace Pml::PokePara;

namespace Dpr
{
    namespace Message
    {
        struct MessageWordSetHelper
        {
            static void SetDigitWord(int32_t tagIndex, int32_t number, MethodInfo *method);
            static void SetPokemonNickNameWord(int32_t tagIndex, CoreParam_o *pp, bool isShowNickName, MethodInfo *method);
            static void SetWazaNameWord(int32_t tagIndex, int32_t wazaNo, MethodInfo *method);
        };
    }
}
