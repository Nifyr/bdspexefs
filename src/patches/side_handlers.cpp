#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/SICKCONT.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"
#include "logger.hpp"

using namespace Dpr::Battle::Logic;

// WorkIdx
constexpr uint8_t A = 0;
constexpr uint8_t B = 1;
constexpr uint8_t C = 2;
constexpr uint8_t D = 3;
constexpr uint8_t E = 4;
constexpr uint8_t WORKIDX_SICKCONT_LOW = 5;
constexpr uint8_t WORKIDX_SICKCONT_HIGH = 6;

// TempTargetPriorityIDs
constexpr uint8_t WAZA_2_TEMPT_TARGET_PRIORITY = 3;

// TempTargetCauseIDs
constexpr uint8_t OTHER_TEMPT_TARGET_CAUSE = 3;

// Remember to update when adding handlers
constexpr uint32_t NEW_SIDE_EFFECT_COUNT = 0;

// --- EventHandler delegates ---
// Lucky Chant
void Dpr_Battle_Logic_Handler_Side_handler_side_Omajinai(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr);
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
}
// Spotlight
void Dpr_Battle_Logic_Handler_Side_handler_SpotLight_TemptTarget(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr);
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    BTL_SICKCONT_o cont = (*args)->fields.pBattleEnv->
            GetSideEffectStatus(mySide, Common::GetSubID(args, nullptr),
                                nullptr)->GetContParam(nullptr);
    Common::RewriteEventVar(args, EventVar::POKEID_DEF, SICKCONT::GetPokeID(&cont, nullptr),
                            nullptr);
    Common::RewriteEventVar(args, EventVar::TEMPT_TARGET_PRIORITY, WAZA_2_TEMPT_TARGET_PRIORITY,
                            nullptr);
    Common::RewriteEventVar(args, EventVar::TEMPT_TARGET_CAUSE, OTHER_TEMPT_TARGET_CAUSE, nullptr);
}