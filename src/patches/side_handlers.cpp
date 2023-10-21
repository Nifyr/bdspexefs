#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;

// WorkIdx
constexpr uint8_t A = 0;
constexpr uint8_t B = 1;
constexpr uint8_t C = 2;
[[maybe_unused]] constexpr uint8_t D = 3;
constexpr uint8_t E = 4;
constexpr uint8_t WORKIDX_SICKCONT_LOW = 5;
constexpr uint8_t WORKIDX_SICKCONT_HIGH = 6;

// Remember to update when adding handlers
constexpr uint32_t NEW_SIDE_EFFECT_COUNT = 0;

// --- EventHandler delegates ---
void Dpr_Battle_Logic_Handler_Side_handler_side_Omajinai(EventFactor_EventHandlerArgs_o **args, uint8_t mySide, MethodInfo *method) {
    uint8_t pokeID = Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr);
    if (Common::PokeIDtoSide(args, &pokeID, nullptr) != mySide) return;
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
}