#pragma once

#include "il2cpp.hpp"
#include "BgComponentData.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BTL_FIELD_SITUATION_c;

            struct BTL_FIELD_SITUATION_Fields {
                struct BgComponentData_o* bgComponent;
                uint8_t weather;
                uint8_t fieldWeather;
                uint8_t ground;
            };

            struct BTL_FIELD_SITUATION_o {
                BTL_FIELD_SITUATION_c *klass;
                void *monitor;
                BTL_FIELD_SITUATION_Fields fields;
            };
        }
    }
}