#include "il2cpp.hpp"

#include "Dpr/UI/UIBag.hpp"

using namespace UnityEngine::Events;

namespace Audio {
    struct AudioInstance_o;

    struct AudioManager_o {
        AudioInstance_o * PlaySe(uint32_t playEventId, UnityAction_AudioInstance__o *onFinished, MethodInfo *method);
        void SetBgmEvent(uint32_t eventId, bool isThroughSameEvent, MethodInfo *method);
        void StopBgm(MethodInfo *method);
    };
}