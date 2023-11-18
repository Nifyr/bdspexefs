#include "il2cpp.hpp"

#include "BaseEntity.hpp"

struct FieldObjectEntity_Fields {
    BaseEntity_Fields super;
    struct UnityEngine_Vector3_o moveVector;
    bool isExtruded;
    bool isLanding;
    struct UnityEngine_Vector3_o _oldMoveVector_k__BackingField;
    struct Dpr_RouteSearch_FieldObjectRouteMove_o* _routeMove;
    bool IsIgnorePlayerCollision;
    struct EvEntityCommand_o* _evEntityCmd;
    struct UnityEngine_Vector2Int_o _oldGridPosition_k__BackingField;
    struct UnityEngine_Vector3_array* logPosition;
    uint8_t logcount;
    bool _scaleChangeFlag;
    float _scaleStart;
    float _scaleEnd;
    float _scaleTime;
    float _scaleProgressTime;
    struct Dpr_EvScript_EvDataManager_EntityParam_o* EventParams;
};