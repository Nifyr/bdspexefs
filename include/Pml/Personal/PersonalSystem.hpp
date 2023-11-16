#include "il2cpp.hpp"

#include "XLSXContent/PersonalTable/SheetPersonal.hpp"
#include "XLSXContent/EvolveTable.hpp"

using namespace XLSXContent;

namespace Pml
{
    namespace Personal
    {
        struct PersonalSystem
        {
            static bool CheckPersonalWazaMachine(uint16_t machineNo, MethodInfo *method);
            static int32_t GetEvolutionCondition(uint8_t route_index, MethodInfo *method);
            static EvolveTable_SheetEvolve_o * GetEvolutionTable(int32_t monsno, uint16_t formno, MethodInfo *method);
            static uint16_t GetEvolvedFormNo(uint8_t route_index, MethodInfo *method);
            static XLSXContent::PersonalTable::SheetPersonal_o * GetPersonalData(int32_t monsno, uint16_t formno, MethodInfo *method);
            static uint8_t GetWazaOboeNum(MethodInfo *method);
            static uint16_t GetWazaOboeWazaNo(uint16_t index, MethodInfo *method);
            static bool IsEvolvedFormNoSpecified(uint8_t route_index, MethodInfo *method);
            static void LoadEvolutionTable(int32_t monsno, uint16_t formno, MethodInfo *method);
            static void LoadPersonalData(int32_t monsno, uint16_t formno, MethodInfo *method);
            static void LoadWazaOboeData(int32_t monsno, uint16_t formno, MethodInfo *method);
        };

        extern void *PersonalSystem_TypeInfo;
    }
}