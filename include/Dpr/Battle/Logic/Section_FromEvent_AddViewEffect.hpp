#pragma once

#include "il2cpp.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_AddViewEffect_Description_c;

            struct Section_FromEvent_AddViewEffect_Description_Fields {
                uint16_t effectNo;
                uint8_t pos_from;
                uint8_t pos_to;
                uint16_t reservedQueuePos;
                bool isQueueReserved;
                bool isMessageWindowVanish;
                struct StrParam_o* afterMessage;
            };

            struct Section_FromEvent_AddViewEffect_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_AddViewEffect_Description_c *klass;
                void *monitor;
                Section_FromEvent_AddViewEffect_Description_Fields fields;
            };

            extern void *Section_FromEvent_AddViewEffect_Description_TypeInfo;
        }
    }
}