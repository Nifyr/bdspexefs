#pragma once

// #include "Pml/MonsNo.h"
// #include "types.h"

namespace Pml
{
    namespace PokePara
    {
        struct Accessor_o {
            uint32_t GetExp(MethodInfo * method);
            uint16_t GetFormNo(MethodInfo *method);
            uint32_t GetItemNo(MethodInfo *method);
            uint32_t GetLevel(MethodInfo *method);
            int32_t GetMonsNo(MethodInfo *method);
            uint8_t GetSex(MethodInfo *method);
            int32_t GetTokuseiNo(MethodInfo *method);
            int32_t GetWazaNo(uint8_t wazaIndex, MethodInfo *method);
            bool IsTokusei2(MethodInfo *method);
            bool IsTokusei3(MethodInfo *method);
            void SetFormNo(uint16_t formno, MethodInfo *method);
            void SetPP(uint8_t wazaIndex, uint8_t pp, MethodInfo *method);
            void SetSex(uint8_t sex, MethodInfo *method);
            uint32_t SetTalentAgi(uint8_t value, MethodInfo * method);
            uint32_t SetTalentAtk(uint8_t value, MethodInfo * method);
            uint32_t SetTalentDef(uint8_t value, MethodInfo * method);
            uint32_t SetTalentHp(uint8_t value, MethodInfo * method);
            uint32_t SetTalentSpAtk(uint8_t value, MethodInfo * method);
            uint32_t SetTalentSpDef(uint8_t value, MethodInfo * method);
            void SetTokuseiNo(uint32_t tokusei, MethodInfo *method);
            void SetWazaNo(uint8_t wazaIndex, uint32_t wazano, MethodInfo *method);
            void SetWazaPPUpCount(uint8_t wazaIndex, uint8_t count, MethodInfo *method);
        };
    } // namespace PokePara
    
} // namespace Pml


