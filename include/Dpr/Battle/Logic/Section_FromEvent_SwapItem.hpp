#pragma once

#include "il2cpp.hpp"
#include "PokeTypePair.hpp"
#include "Section.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_SwapItem_Description_c;

            struct Section_FromEvent_SwapItem_Description_Fields {
                uint8_t userPokeID;
                uint8_t targetPokeID;
                bool isIncRecordCount_StealItemFromWildPoke;
                bool isDisplayTokuseiWindow;
                struct Dpr_Battle_Logic_StrParam_o* successMessage1;
                struct Dpr_Battle_Logic_StrParam_o* successMessage2;
                struct Dpr_Battle_Logic_StrParam_o* successMessage3;
            };

            struct Section_FromEvent_SwapItem_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_SwapItem_Description_c *klass;
                void *monitor;
                Section_FromEvent_SwapItem_Description_Fields fields;
            };

            extern void *Section_FromEvent_SwapItem_Description_TypeInfo;
        }
    }
}