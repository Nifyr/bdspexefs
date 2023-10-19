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
            struct Section_FromEvent_ChangePokeType_Description_c;

            struct Section_FromEvent_ChangePokeType_Description_Fields {
                uint8_t pokeID;
                struct PokeTypePair_o nextType;
                int32_t exTypeCause;
                bool isStandardMessageDisable;
                bool isFailMessageEnable;
                bool isDisplayTokuseiWindow;
                struct StrParam_o* changedMessage;
            };

            struct Section_FromEvent_ChangePokeType_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_ChangePokeType_Description_c *klass;
                void *monitor;
                Section_FromEvent_ChangePokeType_Description_Fields fields;
            };

            extern void *Section_FromEvent_ChangePokeType_Description_TypeInfo;
        }
    }
}