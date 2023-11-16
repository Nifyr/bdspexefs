#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"

namespace SmartPoint
{
    namespace AssetAssistant
    {
        struct SingletonMonoBehaviour_object_ {
            static Il2CppObject * get_Instance(MethodInfo *method);
        };

        struct SingletonMonoBehaviour_BattleProc__Fields {
            UnityEngine_MonoBehaviour_Fields super;
        };

        extern void *SingletonMonoBehaviour_AudioManager__TypeInfo;
        extern void *SingletonMonoBehaviour_MessageManager__TypeInfo;
        extern void *SingletonMonoBehaviour_UIManager__TypeInfo;

        extern MethodInfo *SingletonMonoBehaviour_AudioManager__get_Instance;
        extern MethodInfo *SingletonMonoBehaviour_MessageManager__get_Instance;
        extern MethodInfo *SingletonMonoBehaviour_UIManager__get_Instance;
    }
}