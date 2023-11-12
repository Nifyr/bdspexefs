#include "il2cpp.hpp"

namespace Dpr
{
    namespace Item
    {
        struct ItemInfo_o
        {
            int32_t get_count(MethodInfo *method);
            int32_t get_Id(MethodInfo *method);
            bool get_IsNoSpend(MethodInfo *method);
            bool get_IsRecoveryAllDead(MethodInfo *method);
            int32_t get_RecoveryHpValue(MethodInfo *method);
            int32_t GetFieldFunctionType(MethodInfo * method);
            int32_t GetParam(int32_t pid, MethodInfo *method);
        };
    }
}