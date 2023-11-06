#include "il2cpp.hpp"

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
            struct Dpr_MsgWindow_MsgWindow_o* _messageWindow;
            struct UIManager_UIInstance_o* instance;
            struct UnityEngine_Events_UnityAction_UIWindow__o* onClosed;
            struct UnityEngine_Events_UnityAction_UIWindow__o* onPreClose;
            int32_t _animStateIn;
            int32_t _animStateOut;
        };
    }
}