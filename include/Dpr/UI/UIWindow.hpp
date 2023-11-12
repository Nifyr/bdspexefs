#include "il2cpp.hpp"

#include "UnityEngine/Color.hpp"
#include "System/Collections/IEnumerator.hpp"

using namespace UnityEngine;
using namespace System::Collections;

namespace Dpr
{
    namespace UI 
    {
        struct UIWindow_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            struct UIInputController_o* _input;
            struct UnityEngine_Canvas_o* _canvas;
            struct UnityEngine_Animator_o* _animator;
            struct UIAnimationEvent_o* _animEvent;
            int32_t _transitionFadeType;
            int32_t _prevWindowId;
            struct MsgWindow_o* _messageWindow;
            struct UIManager_UIInstance_o* instance;
            struct UnityEngine_Events_UnityAction_UIWindow__o* onClosed;
            struct UnityEngine_Events_UnityAction_UIWindow__o* onPreClose;
            bool _IsClosing_k__BackingField;
            int32_t _animStateIn;
            int32_t _animStateOut;
        };

        struct UIWindow_RGCTXs;

        struct UIWindow_VTable {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
            VirtualInvokeData _4_OnCreate;
            VirtualInvokeData _5_OnDestroy;
            VirtualInvokeData _6_OnTransition;
            VirtualInvokeData _7_OnTransitionComplete;
            VirtualInvokeData _8_OnOpen;
            VirtualInvokeData _9_PlayOpenWindowAnimation;
            VirtualInvokeData _10_OpPlayOpenWindowAnimation;
            VirtualInvokeData _11_GetWindowAnimationConnectId;
            VirtualInvokeData _12_OpPlayCloseWindowAnimationAndWaiting;
            VirtualInvokeData _13_EnableMainCameraByUiMode;
            VirtualInvokeData _14_OnCloseKeyguide;
            VirtualInvokeData _15_OpenMessageWindow;
            VirtualInvokeData _16_CloseMessageWindow;
            VirtualInvokeData _17_IsActiveMessageWindow;
            VirtualInvokeData _18_CreateContextMenuYesNo;
            VirtualInvokeData _19_CreateContextMenuYesNo;
            VirtualInvokeData _20_OnAddContextMenuYesNoItemParams;
        };

        struct UIWindow_StaticFields {
            Color_o TransitionFadeFillColor;
        };

        struct UIWindow_c {
            Il2CppClass_1 _1;
            struct UIWindow_StaticFields* static_fields;
            UIWindow_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            UIWindow_VTable vtable;
        };

        struct UIWindow_o {
            IEnumerator_o * FadeTransition_object_(Color_o color, float duration, Action_o *action, MethodInfo *method);
        };

        extern UIWindow_c *UIWindow_TypeInfo;

        extern MethodInfo *UIWindow_FadeTransition_AdventureNoteWindow_;
    }
}