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

            extern void *List_ContextMenuID__TypeInfo;

            extern MethodInfo *List_ContextMenuID__ctor;

            extern MethodInfo *List_ContextMenuID__Add;
            extern MethodInfo *List_ContextMenuID__ToArray;
        }
    }
}