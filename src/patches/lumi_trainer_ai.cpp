#include "Dpr/Battle/Logic/AICmd.hpp"
#include "Dpr/Battle/Logic/BtlAiBasic.hpp"
#include "Dpr/Battle/Logic/BtlAiExpert.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::AICmd;
using namespace System;

// WazaIDs
constexpr int64_t PROTECT = 182;
constexpr int64_t DETECT = 197;
constexpr int64_t ENDURE = 203;
constexpr int64_t WIDE_GUARD = 469;
constexpr int64_t QUICK_GUARD = 501;
constexpr int64_t MAT_BLOCK = 561;
constexpr int64_t KINGS_SHIELD = 588;
constexpr int64_t SPIKY_SHIELD = 596;

// TokuseiID
constexpr int64_t PRANKSTER = 158;

// Misc IDs
constexpr int64_t DEFENDER = 0;
constexpr int64_t ATTACKER = 1;
constexpr int64_t DEFENDER_ALLY = 2;
constexpr int64_t ATTACKER_ALLY = 3;
constexpr int64_t BENCH = 4;

constexpr int64_t ATTACKER_HIGHER = 0;
constexpr int64_t DEFENDER_HIGHER = 1;
constexpr int64_t EQUAL = 2;

int64_t Call(void *ai, uint8_t cmd, System_Int64_array *args) {
    return ((BtlAIBaseScript_o *)ai)->Call(cmd, args, nullptr);
}
int64_t Call(void *ai, uint8_t cmd) {
    System_Int64_array *args = NewInt64Array(0);
    return ((BtlAIBaseScript_o *)ai)->Call(cmd, args, nullptr);
}
int64_t Call(void *ai, uint8_t cmd, int64_t arg0) {
    System_Int64_array *args = NewInt64Array(1);
    args->m_Items[0] = arg0;
    return ((BtlAIBaseScript_o *)ai)->Call(cmd, args, nullptr);
}
int64_t Call(void *ai, uint8_t cmd, int64_t arg0, int64_t arg1) {
    System_Int64_array *args = NewInt64Array(2);
    args->m_Items[0] = arg0;
    args->m_Items[1] = arg1;
    return ((BtlAIBaseScript_o *)ai)->Call(cmd, args, nullptr);
}
void Score(void *ai, int32_t value) {
    ((BtlAIBaseScript_o *)ai)->ScoreCtrl(value, nullptr);
}
bool Chance(void *ai, int32_t chance) {
    return Call(ai, CMD_IF_RND_UNDER, chance);
}

// Fake out
void Dpr_Battle_Logic_BtlAiBasic_BaciAI_Seq_158(BtlAiBasic_o *ai, MethodInfo *method) {
    if (Call(ai, CMD_CHECK_NEKODAMASI, ATTACKER))
        Score(ai, -13);
}
// Pain split
void Dpr_Battle_Logic_BtlAiExpert_ExpertAI_Seq_091(BtlAiExpert_o *ai, MethodInfo *method) {
    if (Call(ai, CMD_IF_LEVEL, DEFENDER_HIGHER)) {
        int64_t wazaID = Call(ai, CMD_CHECK_LAST_WAZA, ATTACKER);
        if (wazaID == PROTECT || wazaID == DETECT || wazaID == ENDURE || wazaID == WIDE_GUARD ||
            wazaID == QUICK_GUARD || wazaID == MAT_BLOCK || wazaID == KINGS_SHIELD || wazaID == SPIKY_SHIELD)
            if (Call(ai, CMD_IF_COMMONRND_UNDER, 240))
                Score(ai, 2);
    }
    if (Call(ai, CMD_IF_COMMONRND_UNDER, 180)) {
        Score(ai, 2);
        return;
    }
    if (Call(ai, CMD_IF_HP_UNDER, DEFENDER, 50))
        if (Chance(ai, 230))
            Score(ai, -2);
    if (Call(ai, CMD_CHECK_TOKUSEI, ATTACKER) == PRANKSTER ||
        Call(ai, CMD_IF_FIRST, ATTACKER_HIGHER)) {
        if (!Call(ai, CMD_IF_HP_OVER, ATTACKER, 50)) {
            if (Call(ai, CMD_IF_HP_UNDER, ATTACKER, 30) &&
            Call(ai, CMD_IF_HP_OVER, DEFENDER, 80))
                if (Chance(ai, 200))
                    Score(ai, 3);
            return;
        }
    }
    else {
        if (!Call(ai, CMD_IF_HP_OVER, ATTACKER, 70)) {
            if (Call(ai, CMD_IF_HP_UNDER, ATTACKER, 50) &&
            Call(ai, CMD_IF_HP_OVER, DEFENDER, 80))
                if (Chance(ai, 200))
                    Score(ai, 1);
            return;
        }
    }
    if (Chance(ai, 230))
        Score(ai, -1);
}