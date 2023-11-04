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
            struct Section_FromEvent_ChangeTokusei_Description_c;

            struct Section_FromEvent_ChangeTokusei_Description_Fields {
                uint8_t userPokeID;
                uint8_t targetPokeID;
                int32_t tokuseiID;
                uint8_t cause;
                bool isEffectiveToSameTokusei;
                bool isSkipMemberInEvent;
                bool isDisplayTokuseiWindow;
                struct StrParam_o* successMessage;
            };

            struct Section_FromEvent_ChangeTokusei_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_ChangeTokusei_Description_c *klass;
                void *monitor;
                Section_FromEvent_ChangeTokusei_Description_Fields fields;
            };

            extern void *Section_FromEvent_ChangeTokusei_Description_TypeInfo;

            struct Section_FromEvent_ChangeTokusei_Result_o {
                void ctor(MethodInfo *method);
            };

            extern void *Section_FromEvent_ChangeTokusei_Result_TypeInfo;

            struct Section_FromEvent_ChangeTokusei_o {
                void Execute(Section_FromEvent_ChangeTokusei_Result_o *result, Section_FromEvent_ChangeTokusei_Description_o **description, MethodInfo *method);
            };
        }
    }
}