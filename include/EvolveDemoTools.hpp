#include "il2cpp.hpp"

#include "Pml/PokeParty.hpp"
#include "Pml/PokePara/EvolveManager.hpp"
#include "System/Action.hpp"
#include "System/Collections/IEnumerator.hpp"

using namespace Pml;
using namespace Pml::PokePara;
using namespace System;
using namespace System::Collections;

struct EvolveDemoTools {
    static bool CanEvolve(int32_t *nextMonsNo, uint32_t *evolutionRoot, PokeParty_o *playerParty, PokemonParam_o *poke, EvolveSituation_o *situation, PokemonParam_o *pairPoke,uint16_t itemNo, MethodInfo *method);
    static IEnumerator_o * RegisterZukanCoroutine(PokemonParam_o *capturedPokemon, Action_o *onEnd, MethodInfo *method);
};

struct EvolveDemoTools_Param_Fields {
    PokeParty_o* party;
    PokemonParam_o* pp;
    int32_t criticalCount;
    EvolveSituation_o* situation;
};

struct EvolveDemoTools_param_o {
    EvolveDemoTools_Param_Fields fields;
};