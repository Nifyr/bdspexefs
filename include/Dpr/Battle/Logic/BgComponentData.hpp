#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BgComponentData_c;

            struct BgComponentData_Fields {
                int32_t arenaIndex;
                int32_t sizennotikaraWazaNo;
                bool enableDarkBall;
                uint8_t minomuttiFormNo;
                int32_t footEffectID;
                int32_t attachJoint;
                bool isIndoor;
                int32_t reflectionResolution;
                int32_t shadowResolution;
                struct XLSXContent_BattleSetupEffectLots_SheetArenaEffTable_o* arenaEffTable;
            };

            struct BgComponentData_o {
                BgComponentData_c *klass;
                void *monitor;
                BgComponentData_Fields fields;
            };
        }
    }
}