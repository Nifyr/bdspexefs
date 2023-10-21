#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_FreeFallStart_c;

            struct Section_FromEvent_FreeFallStart_Fields {
                struct Section_Fields super;
            };

            struct Section_FromEvent_FreeFallStart_o {
                Section_FromEvent_FreeFallStart_c *klass;
                void *monitor;
                Section_FromEvent_FreeFallStart_Fields fields;
            };

            struct Section_FromEvent_FreeFallStart_Description_c;

            struct Section_FromEvent_FreeFallStart_Description_Fields {
                uint8_t attackerID;
                uint8_t targetID;
                struct WazaParam_o* wazaParam;
            };

            struct Section_FromEvent_FreeFallStart_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_FreeFallStart_Description_c *klass;
                void *monitor;
                Section_FromEvent_FreeFallStart_Description_Fields fields;
            };
        }
    }
}