#include "il2cpp.hpp"

#include "Dpr/Message/MessageMsgFile.hpp"
#include "System/Action.hpp"
#include "System/Nullable.hpp"
#include "System/String.hpp"

using namespace Dpr::Message;
using namespace System;

namespace Dpr {
    namespace MsgWindow {
        struct MsgWindowParam_c;

        struct MsgWindowParam_Fields {
            String_o* labelName;
            int32_t labelIndex;
            MessageMsgFile_o* useMsgFile;
            struct Dpr_Message_MessageTextParseDataModel_o* textDataModel;
            bool bBatchDisplay;
            int32_t dataValue;
            bool inputEnabled;
            bool inputCloseEnabled;
            bool playTextFeedSe;
            int32_t frameTypeIndex;
            Nullable_Vector2__o wndAnchorPos;
            int32_t sortingOrder;
            int32_t forceSetMsgSpeed;
            struct System_String_o* originalSpeakerName;
            bool showLastKeywaitIcon;
            bool isNetwork;
            bool showLoadingIcon;
            struct System_Action_o* onFinishedOpenWindow;
            Action_o* onFinishedCloseWindow;
            struct System_Action_o* onFinishedShowAllMessage;
        };

        struct MsgWindowParam_o {
            MsgWindowParam_c *klass;
            void *monitor;
            MsgWindowParam_Fields fields;
            
            void ctor(MethodInfo *method);
        };

        extern void *MsgWindowParam_TypeInfo;
    }
}