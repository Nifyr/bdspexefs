#pragma once

#include "il2cpp.hpp"
#include "Dpr/Field/Walking/FieldWalkingManager.hpp"

using namespace Dpr::Field::Walking;

struct FieldManager_RGCTXs;

struct FieldManager_VTable {
    VirtualInvokeData _0_Equals;
    VirtualInvokeData _1_Finalize;
    VirtualInvokeData _2_GetHashCode;
    VirtualInvokeData _3_ToString;
};

struct FieldManager_StaticFields {
    struct FieldManager_o* _Instance_k__BackingField;
    FieldWalkingManager_o* fwMng;
    struct Dpr_SubContents_Utils_AssetUnloader_o* abUnloader;
    bool _IsResume_k__BackingField;
    bool SealPrevFalg;
};

struct FieldManager_c {
    Il2CppClass_1 _1;
    struct FieldManager_StaticFields* static_fields;
    FieldManager_RGCTXs* rgctx_data;
    Il2CppClass_2 _2;
    FieldManager_VTable vtable;
};

extern FieldManager_c *FieldManager_TypeInfo;