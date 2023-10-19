#pragma once 

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct WazaEffectParams_c;

            struct WazaEffectParams_Fields {
                int32_t effectWazaID;
                uint8_t attackerPos;
                uint8_t targetPos;
                uint8_t effectIndex;
                uint8_t pluralHitIndex;
                bool isGShockOccur;
                bool fEnable;
                bool fDone;
                uint16_t commandQueuePos;
                bool isSyncDamageEffect;
                uint8_t subEff_pokeCnt;
                uint8_t subEff_pokeID_1;
                uint8_t subEff_pokeID_2;
                uint8_t subEff_pokeID_3;
                uint8_t subEff_pokeID_4;
                uint8_t subEff_pokeID_5;
            };

            struct WazaEffectParams_o {
                WazaEffectParams_c *klass;
                void *monitor;
                WazaEffectParams_Fields fields;
            };
        }
    }
}