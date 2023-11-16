#include "il2cpp.hpp"

#include "OwnerInfo.hpp"
#include "poketool/poketool_evolution_util.hpp"

namespace Pml
{
    namespace PokePara
    {
        struct EvolveSituation_c;

        struct EvolveSituation_Fields {
            bool isMagneticField;
            bool isIceField;
            bool isMossField;
            bool isSnowMountain;
            bool isUltraSpace;
            bool isMorningOrNoon;
            bool isNight;
            bool isEvening;
            bool isRain;
            bool isDeviceTurnedOver;
            bool isTurnRoundOnField;
            uint8_t criticalHitCount;
            struct OwnerInfo_o* owner_info;
        };

        struct EvolveSituation_o {
            EvolveSituation_c *klass;
            void *monitor;
            EvolveSituation_Fields fields;

            void ctor(MethodInfo *method);
        };

        extern void *EvolveSituation_TypeInfo;
    }
}