#include "il2cpp.hpp"

#include "DpData.hpp"
#include "Dpr/NetworkUtils/UgStationID_to_DigFossilIDList.hpp"

using namespace DPData;
using namespace Dpr::NetworkUtils;

namespace Dpr {
    namespace UnderGround {
        struct UgFieldManager_RGCTXs;
        
        struct UgFieldManager_VTable {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
        };
        
        struct UgFieldManager_c;
        
        struct UgFieldManager_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            int32_t d_stationIndex;
            int32_t d_digGroupID;
            bool isUgExiting;
            bool isErrorDialogVisible;
            struct System_Action_o* OnCloseErrorDialog;
            bool IsClosableMessage;
            struct System_Action_o* OnFinishMsg;
            struct System_Action_o* OnFinishBusy;
            struct System_Action_o* OnCreateOtherSecretBase;
            bool IsBase;
            bool isLoadedOrVisit;
            struct UgNetworkManager_o* ugNetManager;
            float KousekiBonusTime;
            uint8_t KousekiCount;
            uint8_t BonusCount;
            struct XLSXContent_StatueEffectRawData_o* ugStatueEffectData;
            struct UgFieldDataManager_o* dataMng;
            struct UgMiniMapComponent_o* miniMap;
            int32_t prevZoneID;
            int32_t nowZoneType;
            struct Dpr_Field_Walking_WalkingAIManager_o* walkingManager;
            struct FieldObjectEntity_o* NpcEntity;
            struct StatueBuff_o* statueBuff;
            UgSecretBase_o nowBaseModel;
            int32_t nowBasePlayerIndex;
            struct UgNetworkManager_UgOnlinePlayerData_o* nowBasePlayerData;
            UgSecretBase_o EffectiveBase;
            int32_t _effectiveBasePlayerIndex_k__BackingField;
            struct System_Collections_Generic_List_UgFieldManager_SecretBaseModel__o* SecretBases;
            UgStationID_to_DigFossilIDList_o ugDigGroupList;
            bool isDigCancel;
            int32_t targetStationIndex;
            struct System_Action_o* OnLeaveTargetPlayer;
            struct System_Action_o* OnDestroyCallBack;
            struct System_Action_o* OnZoneChangeCallBack;
            float OnZoneChangeTime;
            bool isDebugDraw;
            float duration;
            float searchSize;
            float searchDist;
            float TalkDistance;
            struct System_Collections_Generic_List_Vector2Int__o* buffPosList;
            bool isSearching;
            struct UnityEngine_Transform_o* _dummy;
            int32_t Button02;
            int32_t Button04;
            struct Dpr_UI_ContextMenuWindow_o* contextMenu;
            bool isContextMenuOpend;
            int32_t Button03;
            struct System_Action_o* OnComplete;
            struct Dpr_FieldObjectMove_o* move;
            struct Dpr_FieldObjectRotateYaw_o* rot;
            int32_t Button01;
            int32_t Button05;
            int32_t Button06;
            struct UgNPCTalkModel_o* NpcTalkModel;
            struct System_Boolean_array* results;
            int32_t button111;
            int32_t Button001;
            int32_t button01;
            int32_t button02;
            int32_t button03;
            int32_t Button010;
            bool _isInitAddUpdate;
        };
        
        struct UgFieldManager_o {
            UgFieldManager_c *klass;
            void *monitor;
            UgFieldManager_Fields fields;
            
            void CreateReturnPoint(MethodInfo *method);
        };
        
        struct UgFieldManager_StaticFields {
            UnityEngine_MonoBehaviour_Fields super;
            struct UgFieldManager_o* Instance;
            bool isFallEnter;
            bool isDebug_RarePoke;
            bool isForceRareColor;
            struct System_String_array* Y_MENU_LABEL;
            struct System_String_array* Y_MENU_LABEL_ONLINE;
            struct UgFieldManager_DigData_o* digData;
            struct System_Collections_Generic_List_UgFieldManager_DigPointModel__o* DigPoints;
            bool isEnableInput;
            bool isStartLeave;
            bool isGuruGuruAnimEnd;
            struct UnityEngine_Vector3_array* eightDirect;
        };
        
        struct UgFieldManager_c {
            Il2CppClass_1 _1;
            struct UgFieldManager_StaticFields* static_fields;
            UgFieldManager_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            UgFieldManager_VTable vtable;
        };
        
        extern UgFieldManager_c *UgFieldManager_TypeInfo;
        
        extern MethodInfo *UgFieldManager_CreateHyouta;
    }
}