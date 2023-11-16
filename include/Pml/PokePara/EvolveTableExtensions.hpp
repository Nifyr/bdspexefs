#include "XLSXContent/EvolveTable.hpp"

using namespace XLSXContent;

namespace Pml
{
    namespace PokePara
    {
        struct EvolveTableExtensions {
            static int32_t GetEvolutionCondition(EvolveTable_SheetEvolve_o *self, int32_t index, MethodInfo *method);
            static uint16_t GetEvolutionParam(EvolveTable_SheetEvolve_o *self, int32_t index, MethodInfo *method);
            static uint8_t GetEvolutionRouteNum(EvolveTable_SheetEvolve_o *self, MethodInfo *method);
            static uint8_t GetEvolveEnableLevel(EvolveTable_SheetEvolve_o *self, int32_t index, MethodInfo *method);
        };
    }
}