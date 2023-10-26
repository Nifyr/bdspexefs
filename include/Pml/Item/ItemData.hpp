#pragma once

#include "il2cpp.hpp"

namespace Pml
{
    namespace Item
    {
        struct ItemData {
            static bool IsNuts(uint16_t itemno, MethodInfo *method);
        };

        enum ItemData_PrmID {
            ITEMNUMBER,
            PRICE,
            WAT_PRICE,
            BP_PRICE,
            ICONID,
            EQUIP,
            ATTACK,
            TUIBAMU_EFF,
            NAGE_EFF,
            NAGE_ATC,
            SIZEN_ATC,
            SIZEN_TYPE,
            IMP,
            CNV,
            F_POCKET,
            F_FUNC,
            B_FUNC,
            WORK_TYPE,
            ITEM_TYPE,
            SPEND,
            USE_SPEND,
            SORT,
            GROUP,
            GROUPID,
            SET_TO_POKE,
            B_SELECTABLE,
            INACTIVE,
            WORK,
            SLEEP_RCV = 27,
            POISON_RCV,
            BURN_RCV,
            ICE_RCV,
            PARALYZE_RCV,
            PANIC_RCV,
            MEROMERO_RCV,
            ABILITY_GUARD,
            DEATH_RCV,
            ALL_DEATH_RCV,
            LV_UP,
            EVOLUTION,
            ATTACK_UP,
            DEFENCE_UP,
            SP_ATTACK_UP,
            SP_DEFENCE_UP,
            AGILITY_UP,
            HIT_UP,
            CRITICAL_UP,
            PP_UP,
            PP_3UP,
            PP_RCV,
            ALL_PP_RCV,
            HP_RCV,
            HP_EXP,
            POWER_EXP,
            DEFENCE_EXP,
            AGILITY_EXP,
            SP_ATTACK_EXP,
            SP_DEFENCE_EXP,
            EXP_LIMIT_FLAG,
            FRIEND1,
            FRIEND2,
            FRIEND3,
            HP_EXP_POINT,
            POWER_EXP_POINT,
            DEFENCE_EXP_POINT,
            AGILITY_EXP_POINT,
            SP_ATTACK_EXP_POINT,
            SP_DEFENCE_EXP_POINT,
            HP_RCV_POINT,
            PP_RCV_POINT,
            FRIEND1_POINT,
            FRIEND2_POINT,
            FRIEND3_POINT
        };
    }
}