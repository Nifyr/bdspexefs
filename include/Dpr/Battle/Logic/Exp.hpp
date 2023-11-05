#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Exp_CalcParam_c;

            struct Exp_CalcParam_Fields {
                int32_t competitor;
                uint32_t playerLanguageId;
                uint32_t levelCap;
                uint32_t deadPokeExp;
                uint32_t deadPokeLevel;
                uint32_t getPokeLevel;
                uint32_t getPokeFriendship;
                uint32_t getPokeLanguageId;
                bool isMatch;
                bool isGakusyusoutiOn;
                bool haveSiawasetamago;
                bool isEvoCanceledPoke;
                bool isMyPoke;
            };

            struct Exp_CalcParam_o {
                Exp_CalcParam_c *klass;
                void *monitor;
                Exp_CalcParam_Fields fields;
            };
            
            struct Exp_CalcResult_c;
            
            struct Exp_CalcResult_Fields {
                uint32_t exp;
                bool byGakusyusouti;
                bool isContainBonus;
            };
            
            struct Exp_CalcResult_o {
                Exp_CalcResult_c *klass;
                void *monitor;
                Exp_CalcResult_Fields fields;
            };

            struct Exp {
                static uint32_t getexp_calc_adjust_level(uint32_t base_exp, uint16_t getpoke_lv, uint16_t deadpoke_lv, MethodInfo *method);
            };
        }
    }
}