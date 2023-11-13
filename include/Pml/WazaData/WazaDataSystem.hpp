#include "il2cpp.hpp"

#include "XLSXContent/WazaTable.hpp"

using namespace XLSXContent;

namespace Pml
{
    namespace WazaData
    {
        struct WazaDataSystem {
            static uint32_t GetPower(int32_t id, MethodInfo *method);
        };

        struct WazaDataSystem_RGCTXs;

        struct WazaDataSystem_VTable {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };

        struct WazaDataSystem_StaticFields {
            WazaTable_o* s_wazaTable;
        };

        struct WazaDataSystem_c {
            Il2CppClass_1 _1;
            struct WazaDataSystem_StaticFields* static_fields;
            WazaDataSystem_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            WazaDataSystem_VTable vtable;
        };

        extern WazaDataSystem_c *WazaDataSystem_TypeInfo;
    }
}