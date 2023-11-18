#include "il2cpp.hpp"

#include "FieldObjectEntity.hpp"

struct FieldCharacterEntity_Fields {
    FieldObjectEntity_Fields super;
    float HandScale;
    struct AnimationPlayer_o* _animationPlayer;
    struct CurvePatterns_o* _blinkPatterns;
    struct FieldCharacterVariation_array* _variations;
    int32_t _eyePatternIndex;
    int32_t _mouthPatternIndex;
    int32_t _currentVariation;
    struct UnityEngine_Renderer_o* _watchRenderer;
    int32_t _blinkCurveIndex;
    float _blinkTime;
    int32_t _UVOffsetID;
    struct UnityEngine_MaterialPropertyBlock_o* _propertyBlock;
    struct System_Single_array* _effectCoolTime;
    struct UnityEngine_Vector3_o NeckAngle;
    struct UnityEngine_Vector3_o _updateNeckAngle;
    struct UnityEngine_Vector3_o _updateNeckAngle2;
    struct UnityEngine_Transform_o* _subductionNode;
    struct UnityEngine_Transform_o* _hipNode;
    float SubductionDepth;
    struct Effect_EffectInstance_o* SwimEffect;
    bool isPlayingSwimEffect;
    struct Effect_EffectInstance_o* _swimWalkEffect;
    bool _isPlayingSwimWalkEffect;
    bool _IsForceBlink_k__BackingField;
    bool _reqestStopFootEffect;
    bool _isStopFootEffect;
    float _stopFootEffectRetrunTime;
    int32_t _oldAnimEventIndex;
    int32_t _oldAnimClipIndex;
    struct XLSXContent_CharcterAnimeEvent_SheetanimeEvent_array_array* _animEvents;
    struct System_Func_AnimationPlayer__bool__o* animeEndCallBack;
};