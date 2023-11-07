#include "il2cpp.hpp"

#include "System/String.hpp"
#include "System/Nullable.hpp"

using namespace System;

namespace Dpr
{
    namespace UI 
    {
        struct UIMsgWindowController_c;
        struct UIMsgWindowController_Fields {
            struct MsgWindow_o* msgWindow;
            struct Action_o* onCloseMsgWindow;
            struct Action_o* onFinishedContinueMessage;
            bool isWaitMsgWindow;
            struct Nullable_Vector2__o windowAnchorPosition;
            struct MsgWindowParam_o* msgWindowParam;
            struct List_string__o* continueMessageLabels;
            struct List_Action__o* continueMessageOnSets;
        };

        struct UIMsgWindowController_o {
            UIMsgWindowController_c *klass;
            void *monitor;
            UIMsgWindowController_Fields fields;

            void OpenMsgWindow(int32_t messageFileType, String_o *labelName, bool isWait, bool isBatchDisplay, Action_o *onFinishedMessage, Action_o *onCloseWindow, MethodInfo *method);
        };
    }
}