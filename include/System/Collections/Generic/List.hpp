#pragma once

#include "il2cpp.hpp"

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

            extern void *List_ContextMenuID__TypeInfo;

            extern MethodInfo *List_ContextMenuID__ctor;

            extern MethodInfo *List_ContextMenuID__Add;
            extern MethodInfo *List_ContextMenuID__ToArray;
        }
    }
}