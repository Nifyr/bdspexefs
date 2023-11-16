#pragma once

#include "Pml/PokePara/CoreParam.h"
#include "Dpr/Battle/Logic/POKECON.hpp"
#include "System/Collections/IEnumerator.hpp"

using namespace Dpr::Battle::Logic;
using namespace Pml;
using namespace Pml::PokePara;
using namespace System::Collections;

namespace Dpr
{
    struct EncountTools
    {
        static void OnPostBattle(BATTLE_SETUP_PARAM_o *bsp, PokeParty_o *iPtrPlayerParty, int32_t *outEvolveCheckTargetIndices, IEnumerator_o **outDispError, MethodInfo *method);
        static void OnPostRegisterZukan(PokemonParam_o *capturePokemonParam, int32_t throwBallCount, MethodInfo *method);
        static uint16_t SetWildPokemonItem(Pml::PokePara::CoreParam * pp, int32_t itemRnd, int32_t rnd1, int32_t rnd2, MethodInfo *method);
    };

    extern void *EncountTools_TypeInfo;
}