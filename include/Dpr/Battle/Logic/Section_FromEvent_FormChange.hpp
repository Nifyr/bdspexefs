#pragma once 

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/StrParam.hpp"
#include "Section.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_FormChange_Description_c;

            struct Section_FromEvent_FormChange_Description_Fields {
                uint8_t pokeID;
                uint8_t formNo;
                bool isDontResetFormByOut;
                bool isEnableInCaseOfDead;
                bool isDisplayTokuseiWindow;
                bool isDisplayChangeEffect;
                struct StrParam_o* successMessage;
            };

            struct Section_FromEvent_FormChange_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_FormChange_Description_c *klass;
                void *monitor;
                Section_FromEvent_FormChange_Description_Fields fields;
            };

            struct Section_FromEvent_FormChange_Result_c;

            struct Section_FromEvent_FormChange_Result_Fields {
                bool isChanged;
            };

            struct Section_FromEvent_FormChange_Result_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_FormChange_Result_c *klass;
                void *monitor;
                Section_FromEvent_FormChange_Result_Fields fields;
            };

            struct Section_FromEvent_FormChange_c;

            struct Section_FromEvent_FormChange_Fields {
                Section_Fields super;
            };

            struct Section_FromEvent_FormChange_o {
                Section_FromEvent_FormChange_c *klass;
                void *monitor;
                Section_FromEvent_FormChange_Fields fields;

                void Execute(Section_FromEvent_FormChange_Result_o *result, Section_FromEvent_FormChange_Description_o **description, MethodInfo *method);
            };

            extern void *Section_FromEvent_FormChange_Description_TypeInfo;
            extern void *Section_FromEvent_FormChange_Result_TypeInfo;
        }
    }
}