#pragma once

#include "MonsLv.hpp"
#include "System/Array.hpp"

struct ZoneWork
{
    static bool IsUnderGround(int32_t zone_id, MethodInfo *method);
    static System::Array<MonsLv_o> * TairyouHassei_MonsLv(int32_t zoneId, MethodInfo * method);
};