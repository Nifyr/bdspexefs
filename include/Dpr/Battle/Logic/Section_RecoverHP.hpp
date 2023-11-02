#pragma once

#include "il2cpp.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_RecoverHP_Description_c;

            struct Section_RecoverHP_Description_Fields {
                uint8_t userPokeID;
                uint8_t targetPokeID;
                uint16_t recoverHP;
                uint16_t itemID;
                bool isDisplayTokuseiWindow;
                bool isDisplayFailMessage_HPFull;
                bool isDisplayFailMessage_SP;
                bool isDisplayRecoverEffect;
                bool isSkipFailCheckSP;
                struct StrParam_o* successMessage;
            };

            struct Section_RecoverHP_Description_o {
                void ctor(MethodInfo *method);

                Section_RecoverHP_Description_c *klass;
                void *monitor;
                Section_RecoverHP_Description_Fields fields;
            };

            extern void *Section_RecoverHP_Description_TypeInfo;
        }
    }
}