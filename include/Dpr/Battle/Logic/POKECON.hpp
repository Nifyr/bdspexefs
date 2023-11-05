#pragma once

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "MyStatus.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct POKECON_c;
            
            struct POKECON_Fields {
                struct MainModule_o* m_mainModule;
                struct BTL_PARTY_array* m_party;
                struct BTL_POKEPARAM_array* m_activePokeParam;
                struct BTL_POKEPARAM_array* m_storedPokeParam;
            };
            
            struct POKECON_o {
                POKECON_c *klass;
                void *monitor;
                POKECON_Fields fields;
                
                BTL_POKEPARAM_o * GetPokeParam(uint8_t pokeID, MethodInfo *method);
                void setupPokeParam(BTL_POKEPARAM_o *pokeParam, uint8_t pokeID, PokemonParam_o *srcParam, DefaultPowerUpDesc_o **defaultPowerUpDesc, MyStatus_o *playerData, MethodInfo *method);
            };
        }
    }
}