#pragma once

#include "il2cpp.hpp"

namespace Dpr::UI {
    struct PokemonPartyItem_array;
}

namespace System
{
    namespace Collections
    {
        namespace Generic
        {
            struct List_ZoneID__o {
                void ctor(MethodInfo *method);

                void Add(int32_t item, MethodInfo *method);
            };

            struct List_Int32Enum__o {
                System_Int32Enum_array *ToArray(MethodInfo *method);
            };

            struct List_PokemonPartyItem__c;

            struct List_PokemonPartyItem__Fields {
                struct Dpr::UI::PokemonPartyItem_array* _items;
                int32_t _size;
                int32_t _version;
                Il2CppObject* _syncRoot;
            };

            struct List_PokemonPartyItem__o {
                List_PokemonPartyItem__c *klass;
                void *monitor;
                List_PokemonPartyItem__Fields fields;
            };

            struct List_XMenuTopItem__c;

            struct List_XMenuTopItem__Fields {
                struct XMenuTopItem_array* _items;
                int32_t _size;
                int32_t _version;
                Il2CppObject* _syncRoot;
            };

            struct List_XMenuTopItem__o {
                List_XMenuTopItem__c *klass;
                void *monitor;
                List_XMenuTopItem__Fields fields;

                void ctor(MethodInfo *method);

                void Add(void *item, MethodInfo *method);
            };

            struct List_EvolveDemoTools_Param__c;

            struct List_EvolveDemoTools_Param__Fields {
                struct EvolveDemoTools_Param_array* _items;
                int32_t _size;
                int32_t _version;
                Il2CppObject* _syncRoot;
            };

            struct List_EvolveDemoTools_Param__o {
                List_EvolveDemoTools_Param__c *klass;
                void *monitor;
                List_EvolveDemoTools_Param__Fields fields;

                void Add(void *item, MethodInfo *method);
                void Clear(MethodInfo *method);
            };

            extern void *List_ContextMenuID__TypeInfo;
            extern void *List_PokemonPartyItem__TypeInfo;

            extern MethodInfo *List_ContextMenuID__ctor;
            extern MethodInfo *List_PokemonPartyItem__ctor;

            extern MethodInfo *List_ContextMenuID__Add;
            extern MethodInfo *List_ContextMenuID__ToArray;
            extern MethodInfo *List_EvolveDemoTools_Param__Add;
            extern MethodInfo *List_PokemonPartyItem__Add;
        }
    }
}