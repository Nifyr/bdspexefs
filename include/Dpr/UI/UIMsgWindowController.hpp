#include "il2cpp.hpp"

#include "System/String.hpp"

using namespace System;

namespace Dpr
{
    namespace UI 
    {
        struct UIMsgWindowController_o {
            void OpenMsgWindow(int32_t messageFileType, String_o *labelName, bool isWait, bool isBatchDisplay, Action_o *onFinishedMessage, Action_o *onCloseWindow, MethodInfo *method);
        };
    }
}