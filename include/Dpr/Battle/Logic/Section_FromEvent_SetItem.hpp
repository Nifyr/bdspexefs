#pragma once

#include "il2cpp.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_SetItem_Description_c;

            struct Section_FromEvent_SetItem_Description_Fields {
                uint8_t userPokeID;
                uint8_t targetPokeID;
                uint16_t itemID;
                bool isClearConsume;
                bool isClearConsumeOtherPoke;
                uint8_t clearConsumePokeID;
                bool isCallConsumedEvent;
                bool isDisplayTokuseiWindow;
                bool isConsumeItem;
                struct StrParam_o* successMessage;
            };

            struct Section_FromEvent_SetItem_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_SetItem_Description_c *klass;
                void *monitor;
                Section_FromEvent_SetItem_Description_Fields fields;
            };

            extern void *Section_FromEvent_SetItem_Description_TypeInfo;
        }
    }
}