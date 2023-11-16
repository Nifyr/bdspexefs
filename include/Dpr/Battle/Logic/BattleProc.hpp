#include "il2cpp.hpp"

#include "SmartPoint/AssetAssistant/SingletonMonoBehaviour.hpp"

using namespace SmartPoint::AssetAssistant;

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BattleProc__FinalizeCoroutine_d__34_c;

            struct BattleProc_RGCTXs;

            struct BattleProc_VTable {
                VirtualInvokeData _0_Equals;
                VirtualInvokeData _1_Finalize;
                VirtualInvokeData _2_GetHashCode;
                VirtualInvokeData _3_ToString;
                VirtualInvokeData _4_Awake;
                VirtualInvokeData _5_OnApplicationQuit;
            };

            struct BattleProc_StaticFields {
                struct BATTLE_SETUP_PARAM_o* setupParam;
                bool _isInitialized;
                bool _isEnd;
                struct BattleProc_EndFuncDelegate_o* onEndFunc;
                struct BattleProc_EndFuncDelegate_o* onInitializedFunc;
                bool isDebugLoopStop;
            };

            struct BattleProc_c {
                Il2CppClass_1 _1;
                struct BattleProc_StaticFields* static_fields;
                BattleProc_RGCTXs* rgctx_data;
                Il2CppClass_2 _2;
                BattleProc_VTable vtable;
            };

            struct BattleProc_Fields {
                SingletonMonoBehaviour_BattleProc__Fields super;
                struct UnityEngine_Transform_o* cluster;
                struct MainModule_o* mainModule;
                struct BattleProc_UpdateCoreFunc_o* updateCore;
                int32_t subSeq;
                bool isFinalized;
            };

            struct BattleProc_o {
                BattleProc_c *klass;
                void *monitor;
                BattleProc_Fields fields;
            };

            struct BattleProc___c__DisplayClass34_0_c;

            struct BattleProc___c__DisplayClass34_0_Fields {
                bool talking;
            };
            
            struct BattleProc___c__DisplayClass34_0_o {
                BattleProc___c__DisplayClass34_0_c *klass;
                void *monitor;
                BattleProc___c__DisplayClass34_0_Fields fields;
            };

            struct BattleProc__FinalizeCoroutine_d__34_Fields {
                int32_t __1__state;
                Il2CppObject* __2__current;
                struct BattleProc_o* __4__this;
                struct BattleProc___c__DisplayClass34_0_o* __8__1;
                int32_t _evolveCheckTargetIndices_5__2;
            };

            struct BattleProc__FinalizeCoroutine_d__34_o {
                BattleProc__FinalizeCoroutine_d__34_c *klass;
                void *monitor;
                BattleProc__FinalizeCoroutine_d__34_Fields fields;
            };

            struct BattleProc {
                static void StopBGM(BattleProc_o *__this, MethodInfo *method);
            };

            extern BattleProc_c *BattleProc_TypeInfo;
            extern void *BattleProc___c__DisplayClass34_0_TypeInfo;

            extern MethodInfo *BattleProc___c__DisplayClass34_0__FinalizeCoroutine_b__0;
        }
    }
}