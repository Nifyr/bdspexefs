#include "il2cpp.hpp"

#include "CoreParam.hpp"
#include "EvolveSituation.hpp"
#include "Pml/PokeParty.hpp"
#include "XLSXContent/EvolveTable.hpp"

using namespace XLSXContent;

namespace Pml
{
    namespace PokePara
    {
        struct EvolveManager_o;

        struct EvolveManager {
            static bool IsSatisfyEvolveConditionLevelUp(EvolveManager_o *__this, CoreParam_o *poke, PokeParty_o *party, EvolveSituation_o *situation, EvolveTable_SheetEvolve_o *evolveData, int32_t evolveRouteIndex, MethodInfo *method);
        };
    }
}