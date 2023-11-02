#pragma once

#include "il2cpp.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_DecrementPP_Description_c;

            struct Section_FromEvent_DecrementPP_Description_Fields {
                uint8_t pokeID;
                uint8_t wazaIdx;
                uint8_t volume;
                bool isSurfacePP;
                bool isDeadPokeEnable;
                struct StrParam_o* successMessage;
            };

            struct Section_FromEvent_DecrementPP_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_DecrementPP_Description_c *klass;
                void *monitor;
                Section_FromEvent_DecrementPP_Description_Fields fields;
            };

            extern void *Section_FromEvent_DecrementPP_Description_TypeInfo;
        }
    }
}