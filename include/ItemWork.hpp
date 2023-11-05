#pragma once

#include "il2cpp.hpp"
#include "Dpr/Item/ItemInfo.hpp"

using namespace Dpr::Item;

struct ItemWork {
    static ItemInfo_o * GetItemInfo(int32_t itemno, MethodInfo *method);
    static bool IsDsPlayer(MethodInfo *method);
    static int32_t SubItem(int32_t itemno, int32_t num, MethodInfo * method);
};