#include "il2cpp.hpp"
#include "System/Array.hpp"

using namespace System;

namespace XLSXContent
{
    struct ItemTable_c;

    struct ItemTable_SheetItem_o;

    struct ItemTable_SheetWazaMachine_c;

    struct ItemTable_SheetWazaMachine_Fields {
        int32_t itemNo;
        int32_t machineNo;
        int32_t wazaNo;
    };

    struct ItemTable_SheetWazaMachine_o {
        ItemTable_SheetWazaMachine_c *klass;
        void *monitor;
        ItemTable_SheetWazaMachine_Fields fields;
    };

    struct ItemTable_Fields {
        UnityEngine_ScriptableObject_Fields super;
        Array<ItemTable_SheetItem_o *> * Item;
        Array<ItemTable_SheetWazaMachine_o *> * WazaMachine;
    };

    struct ItemTable_o {
        ItemTable_c *klass;
        void *monitor;
        ItemTable_Fields fields;
    };
}