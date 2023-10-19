#include "Dpr/Battle/Logic/ActionDesc.hpp"
#include "Dpr/Battle/Logic/BtlEscapeMode.hpp"
#include "Dpr/Battle/Logic/BtlGround.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/ContFlag.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Handler/Waza.hpp"
#include "Dpr/Battle/Logic/InterruptCode.hpp"
#include "Dpr/Battle/Logic/PokeActionCategory.hpp"
#include "Dpr/Battle/Logic/PokeID.hpp"
#include "Dpr/Battle/Logic/PokeSet.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_ChangePokeType.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_CheckSpecialWazaAdditionalEffectOccur.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_ConsumeItem.hpp"
#include "Dpr/Battle/Logic/Section_InterruptAction.hpp"
#include "Dpr/Battle/Logic/Section_ProcessActionCore.hpp"
#include "Dpr/Battle/Logic/Section_SideEffect_Add.hpp"
#include "Dpr/Battle/Logic/SICKCONT.hpp"
#include "Dpr/Battle/Logic/Tables.hpp"
#include "Dpr/Battle/Logic/WAZADATA.hpp"
#include "Dpr/Battle/Logic/WazaFailCause.hpp"
#include "Pml/PokePara/Sick.hpp"
#include "Pml/WazaData/WazaFlag.hpp"
#include "Pml/WazaData/WazaRankEffect.hpp"
#include "Pml/WazaData/WazaSick.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"
#include "logger.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;
using namespace Pml::PokePara;
using namespace Pml::WazaData;

// Template MethodInfo
extern MethodInfo * Handler_Karagenki_WazaPowMethodInfo;

// WorkIdx
constexpr uint8_t A = 0;
constexpr uint8_t B = 1;
constexpr uint8_t C = 2;
constexpr uint8_t D = 3;
constexpr uint8_t E = 4;
constexpr uint8_t F = 5;
constexpr uint8_t PERSIST = 6;

// MoveIDs
constexpr int32_t NULL_WAZA = 0;
constexpr int32_t JUMP_KICK = 26;
constexpr int32_t SONIC_BOOM = 49;
constexpr int32_t DRAGON_RAGE = 82;
constexpr int32_t RAGE = 99;
constexpr int32_t BIDE = 117;
constexpr int32_t MIRROR_MOVE = 119;
constexpr int32_t PSYWAVE = 149;
constexpr int32_t SPIDER_WEB = 169;
constexpr int32_t NIGHTMARE = 171;
constexpr int32_t RETURN = 216;
constexpr int32_t FRUSTRATION = 218;
constexpr int32_t MAGNITUDE = 222;
constexpr int32_t PURSUIT = 228;
constexpr int32_t SMELLING_SALTS = 265;
constexpr int32_t ASSIST = 274;
constexpr int32_t REFRESH = 287;
constexpr int32_t SNATCH = 289;
constexpr int32_t SECRET_POWER = 290;
constexpr int32_t CAMOUFLAGE = 293;
constexpr int32_t MUD_SPORT = 300;
constexpr int32_t ICE_BALL = 301;
constexpr int32_t SILVER_WIND = 318;
constexpr int32_t SKY_UPPERCUT = 327;
constexpr int32_t WATER_SPORT = 346;
constexpr int32_t WAKE_UP_SLAP = 358;
constexpr int32_t NATURAL_GIFT = 363;
constexpr int32_t U_TURN = 369;
constexpr int32_t TRUMP_CARD = 376;
constexpr int32_t WRING_OUT = 378;
constexpr int32_t LUCKY_CHANT = 381;
constexpr int32_t ME_FIRST = 382;
constexpr int32_t PUNISHMENT = 386;
constexpr int32_t CAPTIVATE = 445;
constexpr int32_t OMINOUS_WIND = 466;
constexpr int32_t FLAME_BURST = 481;
constexpr int32_t SYNCHRONOISE = 485;
constexpr int32_t CHIP_AWAY = 498;
constexpr int32_t VOLT_SWITCH = 521;
constexpr int32_t PARTING_SHOT = 575;

// TypeIDs
constexpr uint8_t NORMAL = 0;
constexpr uint8_t FIGHTING = 1;
constexpr uint8_t FLYING = 2;
constexpr uint8_t POISON = 3;
constexpr uint8_t GROUND = 4;
constexpr uint8_t ROCK = 5;
constexpr uint8_t BUG = 6;
constexpr uint8_t GHOST = 7;
constexpr uint8_t STEEL = 8;
constexpr uint8_t FIRE = 9;
constexpr uint8_t WATER = 10;
constexpr uint8_t GRASS = 11;
constexpr uint8_t ELECTRIC = 12;
constexpr uint8_t PSYCHIC = 13;
constexpr uint8_t ICE = 14;
constexpr uint8_t DRAGON = 15;
constexpr uint8_t DARK = 16;
constexpr uint8_t FAIRY = 17;
constexpr uint8_t NULL_TYPE = 18;

// FieldEffectIDs
constexpr int32_t MUD_SPORT_FIELD = 10;
constexpr int32_t WATER_SPORT_FIELD = 11;

// ItemIDs
constexpr uint16_t NULL_ITEM = 0;
constexpr uint16_t CHERI_BERRY = 149;
constexpr uint16_t CHESTO_BERRY = 150;
constexpr uint16_t PECHA_BERRY = 151;
constexpr uint16_t RAWST_BERRY = 152;
constexpr uint16_t ASPEAR_BERRY = 153;
constexpr uint16_t LEPPA_BERRY = 154;
constexpr uint16_t ORAN_BERRY = 155;
constexpr uint16_t PERSIM_BERRY = 156;
constexpr uint16_t LUM_BERRY = 157;
constexpr uint16_t SITRUS_BERRY = 158;
constexpr uint16_t FIGY_BERRY = 159;
constexpr uint16_t WIKI_BERRY = 160;
constexpr uint16_t MAGO_BERRY = 161;
constexpr uint16_t AGUAV_BERRY = 162;
constexpr uint16_t IAPAPA_BERRY = 163;
constexpr uint16_t RAZZ_BERRY = 164;
constexpr uint16_t BLUK_BERRY = 165;
constexpr uint16_t NANAB_BERRY = 166;
constexpr uint16_t WEPEAR_BERRY = 167;
constexpr uint16_t PINAP_BERRY = 168;
constexpr uint16_t POMEG_BERRY = 169;
constexpr uint16_t KELPSY_BERRY = 170;
constexpr uint16_t QUALOT_BERRY = 171;
constexpr uint16_t HONDEW_BERRY = 172;
constexpr uint16_t GREPA_BERRY = 173;
constexpr uint16_t TAMATO_BERRY = 174;
constexpr uint16_t CORNN_BERRY = 175;
constexpr uint16_t MAGOST_BERRY = 176;
constexpr uint16_t RABUTA_BERRY = 177;
constexpr uint16_t NOMEL_BERRY = 178;
constexpr uint16_t SPELON_BERRY = 179;
constexpr uint16_t PAMTRE_BERRY = 180;
constexpr uint16_t WATMEL_BERRY = 181;
constexpr uint16_t DURIN_BERRY = 182;
constexpr uint16_t BELUE_BERRY = 183;
constexpr uint16_t OCCA_BERRY = 184;
constexpr uint16_t PASSHO_BERRY = 185;
constexpr uint16_t WACAN_BERRY = 186;
constexpr uint16_t RINDO_BERRY = 187;
constexpr uint16_t YACHE_BERRY = 188;
constexpr uint16_t CHOPLE_BERRY = 189;
constexpr uint16_t KEBIA_BERRY = 190;
constexpr uint16_t SHUCA_BERRY = 191;
constexpr uint16_t COBA_BERRY = 192;
constexpr uint16_t PAYAPA_BERRY = 193;
constexpr uint16_t TANGA_BERRY = 194;
constexpr uint16_t CHARTI_BERRY = 195;
constexpr uint16_t KASIB_BERRY = 196;
constexpr uint16_t HABAN_BERRY = 197;
constexpr uint16_t COLBUR_BERRY = 198;
constexpr uint16_t BABIRI_BERRY = 199;
constexpr uint16_t CHILAN_BERRY = 200;
constexpr uint16_t LIECHI_BERRY = 201;
constexpr uint16_t GANLON_BERRY = 202;
constexpr uint16_t SALAC_BERRY = 203;
constexpr uint16_t PETAYA_BERRY = 204;
constexpr uint16_t APICOT_BERRY = 205;
constexpr uint16_t LANSAT_BERRY = 206;
constexpr uint16_t STARF_BERRY = 207;
constexpr uint16_t ENIGMA_BERRY = 208;
constexpr uint16_t MICLE_BERRY = 209;
constexpr uint16_t CUSTAP_BERRY = 210;
constexpr uint16_t JABOCA_BERRY = 211;
constexpr uint16_t ROWAP_BERRY = 212;
constexpr uint16_t ROSELI_BERRY = 686;
constexpr uint16_t KEE_BERRY = 687;
constexpr uint16_t MARANGA_BERRY = 688;

// WazaIdx
constexpr uint8_t NULL_WAZA_IDX = 4;

// SideEffectIDs
constexpr int32_t LUCKY_CHANT_SIDE = 5;

// HanderTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableJumpKick;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSonicBoom;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableDragonRage;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableRage;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBide;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMirrorMove;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePsywave;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableNightmare;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableReturn;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableFrustration;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMagnitude;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePursuit;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSmellingSalts;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableAssist;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableRefresh;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSnatch;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSecretPower;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableCamouflage;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMudSport;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSkyUppercut;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableWaterSport;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableWakeUpSlap;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableNaturalGift;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableTrumpCard;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableLuckyChant;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMeFirst;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePunishment;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableFlameBurst;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSynchronoise;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableChipAway;

// --- EventHandler delegates ---
uint8_t GetEnvironmentType(EventFactor_EventHandlerArgs_o **args) {
    switch (Common::GetGround(args, nullptr)) {
        case BtlGround::BTL_GROUND_GRASS:
            return GRASS;
        case BtlGround::BTL_GROUND_MIST:
            return FAIRY;
        case BtlGround::BTL_GROUND_ELEKI:
            return ELECTRIC;
        case BtlGround::BTL_GROUND_PHYCHO:
            return PSYCHIC;
    }
    return WAZADATA::GetType(Common::GetFieldSituation(args, nullptr)->
    fields.bgComponent->fields.sizennotikaraWazaNo, nullptr);
}
// Sonic Boom
void HandlerSonicBoomWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE, 20, nullptr);
}
// Dragon Rage
void HandlerDragonRageWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE, 40, nullptr);
}
// Rage
void HandlerRageWazaCallDecide(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::SetWorkValue(args, PERSIST, false, nullptr);
}
void HandlerRageWazaExecuteEffective(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZAID, nullptr) != RAGE) return;
    Common::SetWorkValue(args, PERSIST, true, nullptr);
}
void HandlerRageWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    HandlerRankEffect(args, pokeID, pokeID, WazaRankEffect::ATTACK, 1,
                      false, false, true);
}
void HandlerRageMemberOutFixed(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    Common::SetWorkValue(args, PERSIST, false, nullptr);
}
// Bide
void HandlerBideCheckDelayWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetWorkValue(args, A, nullptr) >= 2) return;
    Common::RewriteEventVar(args, EventVar::GEN_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
void HandlerBideWazaExecuteCheck3rd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetWorkValue(args, A, nullptr) < 2) return;
    if (Common::GetWorkValue(args, B, nullptr) > 0) return;
    Common::RewriteEventVar(args,EventVar::FAIL_CAUSE,WazaFailCause::OTHER, nullptr);
}
void HandlerBideWazaCallDecide(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->CheckSick(WazaSick::WAZASICK_WAZALOCK, nullptr)) return;
    if (bpp->CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr)) return;
    if (Common::GetWorkValue(args, 6, nullptr)) return;
    HandlerAddSick(args, pokeID, pokeID, WazaSick::WAZASICK_WAZALOCK,
                   SICKCONT::MakeTurnParam(pokeID,
                                           3,
                                           Common::GetSubID(args, nullptr),
                                           nullptr).fields.raw);
    Common::SetWorkValue(args, PERSIST, true, nullptr);//Active flag
    Common::SetWorkValue(args, A, 0, nullptr);//Turn counter
    Common::SetWorkValue(args, B, 0, nullptr);//Damage taken
    Common::SetWorkValue(args, C, PokeID::INVALID, nullptr);//Target
}
void HandlerBideDecideTarget(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::POKEID_DEF,
                            Common::GetWorkValue(args, C, nullptr),
                            nullptr);
}
void HandlerBideWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE,
                            Common::GetWorkValue(args, B, nullptr) * 2,
                            nullptr);
    Waza::common_Korogaru_Unlock(args, pokeID, nullptr);
}
void HandlerBideWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    Common::SetWorkValue(args, B,
                         Common::GetWorkValue(args, B, nullptr) +
                         Common::GetEventVar(args, EventVar::DAMAGE, nullptr),
                         nullptr);
    Common::SetWorkValue(args, C,
                         Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr),
                         nullptr);
}
void HandlerBideTurncheckEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    int32_t turnCounter = Common::GetWorkValue(args, A, nullptr) + 1;
    Common::SetWorkValue(args, A, turnCounter, nullptr);
    if (turnCounter < 3 && !Common::GetPokeParam(args, pokeID, nullptr)->
            CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr)) return;
    Common::SetWorkValue(args, A, 0, nullptr);
    Common::SetWorkValue(args, B, 0, nullptr);
    Waza::common_Korogaru_Unlock(args, pokeID, nullptr);
}
// Mirror Move
void HandlerMirrorMoveReqwazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    uint8_t targetPokePos = Common::GetEventVar(args, EventVar::POKEPOS_ORG, nullptr);
    uint8_t targetPokeID = Common::GetFrontPokeID(args,&targetPokePos,nullptr);
    if (targetPokeID == PokeID::INVALID) return;
    int32_t targetWazaID = Common::GetPokeParam(args, targetPokeID, nullptr)->fields.m_prevActWazaID;
    if (targetWazaID == NULL_WAZA) return;
    if (!WAZADATA::GetFlag(targetWazaID, WazaFlag::OUMU, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::WAZAID, targetWazaID, nullptr);
    Common::RewriteEventVar(args, EventVar::POKEPOS, targetPokePos, nullptr);
}
// Psywave
void HandlerPsywaveWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE,
                            (int32_t)Calc::RandRange(50, 150, nullptr) *
                            Common::GetPokeParam(args, pokeID, nullptr)->
                            GetValue(BTL_POKEPARAM_ValueID::BPP_LEVEL, nullptr) / 100,
                            nullptr);
}
// Nightmare
void HandlerNightmareAddsickCheckfail(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::SICKID, nullptr) != WazaSick::WAZASICK_AKUMU) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,
                                                 Common::GetEventVar(args,
                                                                     EventVar::POKEID_DEF,
                                                                     nullptr),
                                                 nullptr);
    if (bpp->CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr) &&
            !bpp->CheckSick(WazaSick::WAZASICK_AKUMU, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
}
// Return
void HandlerReturnWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            Common::GetPokeParam(args, pokeID, nullptr)->GetFriendship(nullptr) *
                            2 / 5,
                            nullptr);
}
// Frustration
void HandlerFrustrationWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            (255 - Common::GetPokeParam(args, pokeID, nullptr)->
                            GetFriendship(nullptr)) * 2 / 5,
                            nullptr);
}
// Magnitude
void HandlerMagnitudeWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint32_t r = Calc::GetRand(20, nullptr);
    int32_t power;
    if (r < 1) power = 10;
    else if (r < 3) power = 30;
    else if (r < 7) power = 50;
    else if (r < 13) power = 70;
    else if (r < 17) power = 90;
    else if (r < 19) power = 110;
    else power = 150;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}
// Pursuit
void HandlerPursuitWazaExeStart(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (!Common::GetEventVar(args, EventVar::OIUTI_INTERRUPT_FLAG, nullptr)) return;
    Common::SetWorkValue(args, A, true, nullptr);
}
void HandlerPursuitCalcHitCancel(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::GEN_FLAG, true, nullptr);
}
void HandlerPursuitWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            Common::GetEventVar(args, EventVar::WAZA_POWER, nullptr) * 2,
                            nullptr);
}
// Smelling Salts
void HandlerSmellingSaltsWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!Common::GetPokeParam(args,
                              Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr),
                              nullptr)->CheckSick(WazaSick::WAZASICK_MAHI, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            Common::GetEventVar(args, EventVar::WAZA_POWER, nullptr) * 2,
                            nullptr);
    Common::SetWorkValue(args, A, true, nullptr);
}
void HandlerSmellingSaltsDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    uint8_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    for (int i = 0; i < targetCount; ++i)
        HandlerCureSick(args, pokeID, WazaSick::WAZASICK_MAHI,
                        Common::GetEventVar(args, 6 + i, nullptr));
}
// Assist
void HandlerAssistReqwazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    const int32_t maxCandidateWazaIDCount = 20;
    int32_t candidateWazaIDs[maxCandidateWazaIDCount] = {};
    int32_t candidateWazaIDCount = 0;
    BTL_PARTY_o *party = Common::GetPartyData(args, pokeID, nullptr);
    uint8_t memberCount = party->fields.m_memberCount;
    for (int partyIdx = 0; partyIdx < memberCount; ++partyIdx) {
        BTL_POKEPARAM_o *memberBPP = party->GetMemberDataConst(partyIdx, nullptr);
        if (memberBPP->GetID(nullptr) == pokeID) continue;
        uint8_t wazaCount = memberBPP->fields.m_wazaCnt;
        for (int wazaIdx = 0; wazaIdx < wazaCount; ++wazaIdx) {
            int32_t candidateWazaID = memberBPP->WAZA_GetID(wazaIdx, nullptr);
            if (WAZADATA::GetFlag(candidateWazaID, WazaFlag::YUBIWOHURU_PERMIT, nullptr) &&
                    candidateWazaIDCount < maxCandidateWazaIDCount) {
                candidateWazaIDs[candidateWazaIDCount] = candidateWazaID;
                candidateWazaIDCount++;
            }
        }
    }
    if (candidateWazaIDCount == 0) return;
    int32_t targetWazaID = candidateWazaIDs[Calc::GetRand(candidateWazaIDCount, nullptr)];
    Common::RewriteEventVar(args, EventVar::WAZAID, targetWazaID, nullptr);
    Common::RewriteEventVar(args, EventVar::POKEPOS,
                            Common::DecideWazaTargetAuto(args, pokeID, targetWazaID, nullptr),
                            nullptr);
}
// Refresh
void HandlerRefreshUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint32_t sickID = Common::CheckPokeSick(args, pokeID, nullptr);
    if (sickID == Sick::MAHI || sickID == Sick::YAKEDO || sickID == Sick::DOKU) {
        HandlerCureSick(args, pokeID, WazaSick::WAZASICK_MAX, pokeID);
        Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
    } else Common::RewriteEventVar(args, EventVar::GEN_FLAG, true, nullptr);
}
// Snatch
void HandlerSnatchCheckWazaRob(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) == pokeID) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != PokeID::INVALID) return;
    if (!WAZADATA::GetFlag(Common::GetEventVar(args, EventVar::WAZAID, nullptr),
                           WazaFlag::YOKODORI, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::POKEID, pokeID, nullptr);
    Common::RewriteEventVar(args, EventVar::POKEID_DEF, pokeID, nullptr);
    Common::SetWorkValue(args, PERSIST, false, nullptr);
    Waza::removeHandlerForce((*args)->fields.pEventSystem, pokeID,
                             Common::GetSubID(args, nullptr),
                             nullptr);
}
void HandlerSnatchTurncheckEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    Common::SetWorkValue(args, PERSIST, false, nullptr);
    Waza::removeHandlerForce((*args)->fields.pEventSystem, pokeID,
                             Common::GetSubID(args, nullptr),
                             nullptr);
}
void HandlerSnatchUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::SetWorkValue(args, PERSIST, true, nullptr);
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Secret Power
int32_t HandlerSecretPowerGetPer(EventFactor_EventHandlerArgs_o **args) {
    return WAZADATA::GetSickPer(Common::GetSubID(args, nullptr), nullptr);
}
bool HandlerSecretPowerIsOccur(EventFactor_EventHandlerArgs_o **args, uint8_t defender) {
    return Calc::GetRand(100, nullptr) < (*args)->fields.pSectionContainer->
            fields.m_section_FromEvent_CheckSpecialWazaAdditionalEffectOccur->fields.super.m_pEventLauncher->
            Event_CheckSpecialWazaAdditionalPer(
                    Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr), defender,
                    HandlerSecretPowerGetPer(args), nullptr);
}
void HandlerSecretPowerAddSick(EventFactor_EventHandlerArgs_o **args, uint8_t defender, int32_t sickID) {
    if (!HandlerSecretPowerIsOccur(args, defender)) return;
    uint8_t causePokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr);
    HandlerAddSick(args, causePokeID, defender, sickID,
                   Calc::MakeDefaultPokeSickCont(sickID, causePokeID, false, nullptr).
                   fields.raw);
}
void HandlerSecretPowerRankEffect(EventFactor_EventHandlerArgs_o **args, uint8_t defender, int32_t rankType) {
    if (!HandlerSecretPowerIsOccur(args, defender)) return;
    HandlerRankEffect(args, Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr),
                      defender, rankType, -1, false, false,
                      false);
}
void HandlerSecretPowerShrink(EventFactor_EventHandlerArgs_o **args, uint8_t defender, int32_t arg) {
    HandlerShrink(args, defender, HandlerSecretPowerGetPer(args));
}
void HandlerSecretPowerDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint8_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    void (*additionalEffect) (EventFactor_EventHandlerArgs_o**, uint8_t, int32_t) = nullptr;
    int32_t arg = 0;
    switch (GetEnvironmentType(args)) {
        case GROUND:
            additionalEffect = HandlerSecretPowerRankEffect;
            arg = WazaRankEffect::HIT;
            break;
        case ROCK:
            additionalEffect = HandlerSecretPowerShrink;
            break;
        case FIRE:
            additionalEffect = HandlerSecretPowerAddSick;
            arg = Sick::YAKEDO;
            break;
        case WATER:
            additionalEffect = HandlerSecretPowerRankEffect;
            arg = WazaRankEffect::ATTACK;
            break;
        case GRASS:
            additionalEffect = HandlerSecretPowerAddSick;
            arg = Sick::NEMURI;
            break;
        case PSYCHIC:
            additionalEffect = HandlerSecretPowerRankEffect;
            arg = WazaRankEffect::AGILITY;
            break;
        case ICE:
            additionalEffect = HandlerSecretPowerAddSick;
            arg = Sick::KOORI;
            break;
        case FAIRY:
            additionalEffect = HandlerSecretPowerRankEffect;
            arg = WazaRankEffect::SP_ATTACK;
            break;
        default:
            additionalEffect = HandlerSecretPowerAddSick;
            arg = Sick::MAHI;
            break;
    }
    for (int i = 0; i < targetCount; ++i)
        additionalEffect(args, Common::GetEventVar(args, 6 + i, nullptr), arg);
}
// Camouflage
void HandlerCamouflageUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint8_t type = GetEnvironmentType(args);
    if (Common::GetPokeParam(args, pokeID, nullptr)->IsMatchType(type, nullptr)) return;
    system_load_typeinfo((void *)0xaa5e);
    auto *desc = (Section_FromEvent_ChangePokeType_Description_o *)
            il2cpp_object_new(Section_FromEvent_ChangePokeType_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.nextType = PokeTypePair::MakePure(type, nullptr);
    desc->fields.exTypeCause = BTL_POKEPARAM_ExTypeCause::EXTYPE_CAUSE_NONE;
    if (!Common::ChangeType(args, &desc, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Mud Sport
void HandlerMudSportFieldEffectCall(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!HandlerAddFieldEffect(args, pokeID, MUD_SPORT_FIELD)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Water Sport
void HandlerWaterSportFieldEffectCall(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!HandlerAddFieldEffect(args, pokeID, WATER_SPORT_FIELD)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Wake-Up Slap
void HandlerWakeUpSlapWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!Common::GetPokeParam(args,
                              Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr),
                              nullptr)->
                              CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_INCLUDE_ZETTAINEMURI,
                                          nullptr)) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            Common::GetEventVar(args, EventVar::WAZA_POWER, nullptr) * 2,
                            nullptr);
    Common::SetWorkValue(args, A, true, nullptr);
}
void HandlerWakeUpSlapDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    uint8_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    for (int i = 0; i < targetCount; ++i)
        HandlerCureSick(args, pokeID, WazaSick::WAZASICK_NEMURI,
                        Common::GetEventVar(args, 6 + i, nullptr));
}
// Natural Gift
struct TypePowerPair {
    int32_t type;
    int32_t power;
};
TypePowerPair NaturalGiftTypePower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    switch (Common::GetPokeParam(args, pokeID, nullptr)->GetItem(nullptr)) {
        case CHERI_BERRY:
            return { FIRE, 80};
        case CHESTO_BERRY:
            return { WATER, 80};
        case PECHA_BERRY:
            return { ELECTRIC, 80};
        case RAWST_BERRY:
            return { GRASS, 80};
        case ASPEAR_BERRY:
            return { ICE, 80};
        case LEPPA_BERRY:
            return { FIGHTING, 80};
        case ORAN_BERRY:
            return { POISON, 80};
        case PERSIM_BERRY:
            return { GROUND, 80};
        case LUM_BERRY:
            return { FLYING, 80};
        case SITRUS_BERRY:
            return { PSYCHIC, 80};
        case FIGY_BERRY:
            return { BUG, 80};
        case WIKI_BERRY:
            return { ROCK, 80};
        case MAGO_BERRY:
            return { GHOST, 80};
        case AGUAV_BERRY:
            return { DRAGON, 80};
        case IAPAPA_BERRY:
            return { DARK, 80};
        case RAZZ_BERRY:
            return { STEEL, 80};
        case BLUK_BERRY:
            return { FIRE, 90};
        case NANAB_BERRY:
            return { WATER, 90};
        case WEPEAR_BERRY:
            return { ELECTRIC, 90};
        case PINAP_BERRY:
            return { GRASS, 90};
        case POMEG_BERRY:
            return { ICE, 90};
        case KELPSY_BERRY:
            return { FIGHTING, 90};
        case QUALOT_BERRY:
            return { POISON, 90};
        case HONDEW_BERRY:
            return { GROUND, 90};
        case GREPA_BERRY:
            return { FLYING, 90};
        case TAMATO_BERRY:
            return { PSYCHIC, 90};
        case CORNN_BERRY:
            return { BUG, 90};
        case MAGOST_BERRY:
            return { ROCK, 90};
        case RABUTA_BERRY:
            return { GHOST, 90};
        case NOMEL_BERRY:
            return { DRAGON, 90};
        case SPELON_BERRY:
            return { DARK, 90};
        case PAMTRE_BERRY:
            return { STEEL, 90};
        case WATMEL_BERRY:
            return { FIRE, 100};
        case DURIN_BERRY:
            return { WATER, 100};
        case BELUE_BERRY:
            return { ELECTRIC, 100};
        case OCCA_BERRY:
            return { FIRE, 80};
        case PASSHO_BERRY:
            return { WATER, 80};
        case WACAN_BERRY:
            return { ELECTRIC, 80};
        case RINDO_BERRY:
            return { GRASS, 80};
        case YACHE_BERRY:
            return { ICE, 80};
        case CHOPLE_BERRY:
            return { FIGHTING, 80};
        case KEBIA_BERRY:
            return { POISON, 80};
        case SHUCA_BERRY:
            return { GROUND, 80};
        case COBA_BERRY:
            return { FLYING, 80};
        case PAYAPA_BERRY:
            return { PSYCHIC, 80};
        case TANGA_BERRY:
            return { BUG, 80};
        case CHARTI_BERRY:
            return { ROCK, 80};
        case KASIB_BERRY:
            return { GHOST, 80};
        case HABAN_BERRY:
            return { DRAGON, 80};
        case COLBUR_BERRY:
            return { DARK, 80};
        case BABIRI_BERRY:
            return { STEEL, 80};
        case CHILAN_BERRY:
            return { NORMAL, 80};
        case LIECHI_BERRY:
            return { GRASS, 100};
        case GANLON_BERRY:
            return { ICE, 100};
        case SALAC_BERRY:
            return { FIGHTING, 100};
        case PETAYA_BERRY:
            return { POISON, 100};
        case APICOT_BERRY:
            return { GROUND, 100};
        case LANSAT_BERRY:
            return { FLYING, 100};
        case STARF_BERRY:
            return { PSYCHIC, 100};
        case ENIGMA_BERRY:
            return { BUG, 100};
        case MICLE_BERRY:
            return { ROCK, 100};
        case CUSTAP_BERRY:
            return { GHOST, 100};
        case JABOCA_BERRY:
            return { DRAGON, 100};
        case ROWAP_BERRY:
            return { DARK, 100};
        case ROSELI_BERRY:
            return { FAIRY, 80};
        case KEE_BERRY:
            return { FAIRY, 100};
        case MARANGA_BERRY:
            return { DARK, 100};
        default:
            return { NULL_TYPE, 0};
    }
}
void HandlerNaturalGiftWazaExecuteCheck3rd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (NaturalGiftTypePower(args, pokeID).type == NULL_TYPE ||
    !Common::CheckItemUsable(args, pokeID, nullptr))
        Common::RewriteEventVar_FAIL_CAUSE(args, WazaFailCause::OTHER, nullptr);
}
void HandlerNaturalGiftWazaExecuteDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetPokeParam(args, pokeID, nullptr)->GetItem(nullptr) == NULL_ITEM) return;
    system_load_typeinfo((void *)0xa9ee);
    auto *desc = (Section_FromEvent_ConsumeItem_Description_o *)
            il2cpp_object_new(Section_FromEvent_ConsumeItem_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.userPokeID = pokeID;
    desc->fields.isUseActionDisable = true;
    desc->fields.isKinomiCheckDisable = true;
    Common::ConsumeItem(args, &desc, nullptr);
}
void HandlerNaturalGiftWazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (!Common::CheckItemUsable(args, pokeID, nullptr)) return;
    uint16_t type = NaturalGiftTypePower(args, pokeID).type;
    if (type == NULL_TYPE) return;
    Common::RewriteEventVar(args, EventVar::WAZA_TYPE, type, nullptr);
}
void HandlerNaturalGiftWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, NaturalGiftTypePower(args, pokeID).power, nullptr);
}
// Trump Card
void HandlerTrumpCardWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint8_t wazaIdx = bpp->WAZA_SearchIdx(bpp->fields.m_prevSelectWazaID, nullptr);
    if (wazaIdx == NULL_WAZA_IDX) return;
    int32_t power = 40;
    switch (bpp->WAZA_GetPP(wazaIdx, nullptr)) {
        case 0:
            power = 200;
            break;
        case 1:
            power = 80;
            break;
        case 2:
            power = 60;
            break;
        case 3:
            power = 50;
            break;
    }
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}
// Lucky Chant
void HandlerLuckyChantUncategorizeWazaNoTarget(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    system_load_typeinfo((void *)0xa8ef);
    auto *desc = (Section_SideEffect_Add_Description_o *)
            il2cpp_object_new(Section_SideEffect_Add_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.effect = LUCKY_CHANT_SIDE;
    desc->fields.side = Common::PokeIDtoSide(args, &pokeID, nullptr);
    desc->fields.cont = SICKCONT::MakeTurn(pokeID, 5, nullptr);
    desc->fields.isReplaceSuccessMessageArgs0ByExpandSide = true;
    if (!Common::AddSideEffect(args, &desc, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Me First
void HandlerMeFirstReqwazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    uint8_t targetPokePos = Common::GetEventVar(args, EventVar::POKEPOS_ORG, nullptr);
    uint8_t targetPokeID = Common::GetFrontPokeID(args,&targetPokePos,nullptr);
    if (targetPokeID != PokeID::INVALID && !Common::GetPokeParam(args, targetPokeID, nullptr)->
            TURNFLAG_Get(BTL_POKEPARAM_TurnFlag::TURNFLG_WAZAPROC_DONE, nullptr)) {
        PokeAction_o *action = Common::SearchByPokeID(args, targetPokeID, true, true, nullptr);
        if (action != nullptr) {
            int32_t targetWazaID = PokeAction::GetWazaID(action, nullptr);
            if (targetWazaID != NULL_WAZA && WAZADATA::IsDamage(targetWazaID, nullptr) &&
            !Tables::IsSakidoriFailWaza(targetWazaID, nullptr)) {
                Common::RewriteEventVar(args, EventVar::WAZAID, targetWazaID, nullptr);
                Common::RewriteEventVar(args, EventVar::POKEPOS, targetPokePos, nullptr);
                return;
            }
        }
    }
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
}
void HandlerMeFirstWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            (int32_t)(Common::GetEventVar(args, EventVar::WAZA_POWER, nullptr) * 1.5),
                            nullptr);
}
// Punishment
void HandlerPunishmentWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    int32_t ranks = 0;
    for (int i = 1; i <= 7; ++i) {
        int32_t rank = bpp->GetValue(i, nullptr) - 6;
        if (rank > 0)
            ranks += rank;
    }
    int32_t power = 60 + ranks * 20;
    if (power > 200)
        power = 200;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}
// Flame Burst
void HandlerFlameBurstDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    for (int i = 0; i < targetCount; ++i) {
        auto *opponents = (System_Byte_array *) system_array_new(System_Byte_array_TypeInfo, 5);
        uint8_t opponentCount = Common::GetAllOpponentFrontPokeID(args, pokeID, opponents, nullptr);
        uint8_t targetPokeID = Common::GetEventVar(args, 6 + i, nullptr);
        for (int32_t j = 0; j < opponentCount; ++j) {
            uint8_t opponentPokeID = opponents->m_Items[j];
            if (targetPokeID != opponentPokeID)
                HandlerDamage(args, pokeID, opponentPokeID,
                              Calc::QuotMaxHP(
                                      Common::GetPokeParam(args, opponentPokeID, nullptr),
                                      16, true, nullptr),
                              false, false);
        }
    }
}
// Synchronoise
void HandlerSynchronoiseNoeffectCheckL2(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint8_t typing[3] = { NULL_TYPE, NULL_TYPE, NULL_TYPE };
    PokeTypePair::Split(Common::GetPokeParam(args, pokeID, nullptr)->GetPokeType(nullptr),
                        &typing[0], &typing[1], &typing[2], nullptr);
    BTL_POKEPARAM_o * defBPP = Common::GetPokeParam(
            args,Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr),nullptr);
    for (uint8_t type : typing)
        if (type != NULL_TYPE && defBPP->IsMatchType(type, nullptr))
            return;
    Common::RewriteEventVar(args, EventVar::NOEFFECT_FLAG, true, nullptr);
}
// Chip Away
void HandlerChipAwayWazaHitRank(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::AVOID_RANK, 6, nullptr);
}
void HandlerChipAwayDefenderGuardPrev(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::GEN_FLAG, true, nullptr);
}

EventFactor_EventHandlerTable_o * CreateMoveEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, Handler_Karagenki_WazaPowMethodInfo, methodPointer);
}

// --- HandlerGetFunc delegates ---
System::Array<EventFactor_EventHandlerTable_o *> * ADD_JumpKick(MethodInfo *method) {
    if (sHandlerTableJumpKick == nullptr) {
        sHandlerTableJumpKick = CreateEventHandlerTable(1);
        sHandlerTableJumpKick->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_NO_EFFECT, (Il2CppMethodPointer) &Waza::handler_Tobigeri_NoEffect);
    }
    return sHandlerTableJumpKick;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SonicBoom(MethodInfo *method) {
    if (sHandlerTableSonicBoom == nullptr) {
        sHandlerTableSonicBoom = CreateEventHandlerTable(1);
        sHandlerTableSonicBoom->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerSonicBoomWazaDmgProc1);
    }
    return sHandlerTableSonicBoom;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_DragonRage(MethodInfo *method) {
    if (sHandlerTableDragonRage == nullptr) {
        sHandlerTableDragonRage = CreateEventHandlerTable(1);
        sHandlerTableDragonRage->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerDragonRageWazaDmgProc1);
    }
    return sHandlerTableDragonRage;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Rage(MethodInfo *method) {
    if (sHandlerTableRage == nullptr) {
        sHandlerTableRage = CreateEventHandlerTable(4);
        sHandlerTableRage->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_CALL_DECIDE, (Il2CppMethodPointer) &HandlerRageWazaCallDecide);
        sHandlerTableRage->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_EFFECTIVE, (Il2CppMethodPointer) &HandlerRageWazaExecuteEffective);
        sHandlerTableRage->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerRageWazaDmgReaction);
        sHandlerTableRage->m_Items[3] = CreateMoveEventHandler(EventID::MEMBER_OUT_FIXED, (Il2CppMethodPointer) &HandlerRageMemberOutFixed);
    }
    return sHandlerTableRage;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Bide(MethodInfo *method) {
    if (sHandlerTableBide == nullptr) {
        sHandlerTableBide = CreateEventHandlerTable(7);
        sHandlerTableBide->m_Items[0] = CreateMoveEventHandler(EventID::CHECK_DELAY_WAZA, (Il2CppMethodPointer) &HandlerBideCheckDelayWaza);
        sHandlerTableBide->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_CHECK_3RD, (Il2CppMethodPointer) &HandlerBideWazaExecuteCheck3rd);
        sHandlerTableBide->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_CALL_DECIDE, (Il2CppMethodPointer) &HandlerBideWazaCallDecide);
        sHandlerTableBide->m_Items[3] = CreateMoveEventHandler(EventID::DECIDE_TARGET, (Il2CppMethodPointer) &HandlerBideDecideTarget);
        sHandlerTableBide->m_Items[4] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerBideWazaDmgProc1);
        sHandlerTableBide->m_Items[5] = CreateMoveEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerBideWazaDmgReaction);
        sHandlerTableBide->m_Items[6] = CreateMoveEventHandler(EventID::TURNCHECK_END, (Il2CppMethodPointer) &HandlerBideTurncheckEnd);
    }
    return sHandlerTableBide;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MirrorMove(MethodInfo *method) {
    if (sHandlerTableMirrorMove == nullptr) {
        sHandlerTableMirrorMove = CreateEventHandlerTable(1);
        sHandlerTableMirrorMove->m_Items[0] = CreateMoveEventHandler(EventID::REQWAZA_PARAM, (Il2CppMethodPointer) &HandlerMirrorMoveReqwazaParam);
    }
    return sHandlerTableMirrorMove;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Psywave(MethodInfo *method) {
    if (sHandlerTablePsywave == nullptr) {
        sHandlerTablePsywave = CreateEventHandlerTable(1);
        sHandlerTablePsywave->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerPsywaveWazaDmgProc1);
    }
    return sHandlerTablePsywave;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Nightmare(MethodInfo *method) {
    if (sHandlerTableNightmare == nullptr) {
        sHandlerTableNightmare = CreateEventHandlerTable(1);
        sHandlerTableNightmare->m_Items[0] = CreateMoveEventHandler(EventID::ADDSICK_CHECKFAIL, (Il2CppMethodPointer) &HandlerNightmareAddsickCheckfail);
    }
    return sHandlerTableNightmare;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Return(MethodInfo *method) {
    if (sHandlerTableReturn == nullptr) {
        sHandlerTableReturn = CreateEventHandlerTable(1);
        sHandlerTableReturn->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerReturnWazaPower);
    }
    return sHandlerTableReturn;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Frustration(MethodInfo *method) {
    if (sHandlerTableFrustration == nullptr) {
        sHandlerTableFrustration = CreateEventHandlerTable(1);
        sHandlerTableFrustration->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerFrustrationWazaPower);
    }
    return sHandlerTableFrustration;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Magnitude(MethodInfo *method) {
    if (sHandlerTableMagnitude == nullptr) {
        sHandlerTableMagnitude = CreateEventHandlerTable(3);
        sHandlerTableMagnitude->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerMagnitudeWazaPower);
        sHandlerTableMagnitude->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC3, (Il2CppMethodPointer) &Waza::handler_Jisin_damage);
        sHandlerTableMagnitude->m_Items[2] = CreateMoveEventHandler(EventID::CHECK_POKE_HIDE, (Il2CppMethodPointer) &Waza::handler_Jisin_checkHide);
    }
    return sHandlerTableMagnitude;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Pursuit(MethodInfo *method) {
    if (sHandlerTablePursuit == nullptr) {
        sHandlerTablePursuit = CreateEventHandlerTable(3);
        sHandlerTablePursuit->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_EXE_START, (Il2CppMethodPointer) &HandlerPursuitWazaExeStart);
        sHandlerTablePursuit->m_Items[1] = CreateMoveEventHandler(EventID::CALC_HIT_CANCEL, (Il2CppMethodPointer) &HandlerPursuitCalcHitCancel);
        sHandlerTablePursuit->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerPursuitWazaPower);
    }
    return sHandlerTablePursuit;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SmellingSalts(MethodInfo *method) {
    if (sHandlerTableSmellingSalts == nullptr) {
        sHandlerTableSmellingSalts = CreateEventHandlerTable(2);
        sHandlerTableSmellingSalts->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerSmellingSaltsWazaPower);
        sHandlerTableSmellingSalts->m_Items[1] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerSmellingSaltsDamageprocEndHitReal);
    }
    return sHandlerTableSmellingSalts;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Assist(MethodInfo *method) {
    if (sHandlerTableAssist == nullptr) {
        sHandlerTableAssist = CreateEventHandlerTable(1);
        sHandlerTableAssist->m_Items[0] = CreateMoveEventHandler(EventID::REQWAZA_PARAM, (Il2CppMethodPointer) &HandlerAssistReqwazaParam);
    }
    return sHandlerTableAssist;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Refresh(MethodInfo *method) {
    if (sHandlerTableRefresh == nullptr) {
        sHandlerTableRefresh = CreateEventHandlerTable(1);
        sHandlerTableRefresh->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerRefreshUncategorizeWaza);
    }
    return sHandlerTableRefresh;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Snatch(MethodInfo *method) {
    if (sHandlerTableSnatch == nullptr) {
        sHandlerTableSnatch = CreateEventHandlerTable(3);
        sHandlerTableSnatch->m_Items[0] = CreateMoveEventHandler(EventID::CHECK_WAZA_ROB, (Il2CppMethodPointer) &HandlerSnatchCheckWazaRob);
        sHandlerTableSnatch->m_Items[1] = CreateMoveEventHandler(EventID::TURNCHECK_END, (Il2CppMethodPointer) &HandlerSnatchTurncheckEnd);
        sHandlerTableSnatch->m_Items[2] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerSnatchUncategorizeWaza);
    }
    return sHandlerTableSnatch;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SecretPower(MethodInfo *method) {
    if (sHandlerTableSecretPower == nullptr) {
        sHandlerTableSecretPower = CreateEventHandlerTable(1);
        sHandlerTableSecretPower->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerSecretPowerDamageprocEndHitReal);
    }
    return sHandlerTableSecretPower;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Camouflage(MethodInfo *method) {
    if (sHandlerTableCamouflage == nullptr) {
        sHandlerTableCamouflage = CreateEventHandlerTable(1);
        sHandlerTableCamouflage->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerCamouflageUncategorizeWaza);
    }
    return sHandlerTableCamouflage;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MudSport(MethodInfo *method) {
    if (sHandlerTableMudSport == nullptr) {
        sHandlerTableMudSport = CreateEventHandlerTable(1);
        sHandlerTableMudSport->m_Items[0] = CreateMoveEventHandler(EventID::FIELD_EFFECT_CALL, (Il2CppMethodPointer) &HandlerMudSportFieldEffectCall);
    }
    return sHandlerTableMudSport;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SkyUppercut(MethodInfo *method) {
    if (sHandlerTableSkyUppercut == nullptr) {
        sHandlerTableSkyUppercut = CreateEventHandlerTable(1);
        sHandlerTableSkyUppercut->m_Items[0] = CreateMoveEventHandler(EventID::CHECK_POKE_HIDE, (Il2CppMethodPointer) &Waza::handler_Tatumaki_checkHide);
    }
    return sHandlerTableSkyUppercut;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_WaterSport(MethodInfo *method) {
    if (sHandlerTableWaterSport == nullptr) {
        sHandlerTableWaterSport = CreateEventHandlerTable(1);
        sHandlerTableWaterSport->m_Items[0] = CreateMoveEventHandler(EventID::FIELD_EFFECT_CALL, (Il2CppMethodPointer) &HandlerWaterSportFieldEffectCall);
    }
    return sHandlerTableWaterSport;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_WakeUpSlap(MethodInfo *method) {
    if (sHandlerTableWakeUpSlap == nullptr) {
        sHandlerTableWakeUpSlap = CreateEventHandlerTable(2);
        sHandlerTableWakeUpSlap->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerWakeUpSlapWazaPower);
        sHandlerTableWakeUpSlap->m_Items[1] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerWakeUpSlapDamageprocEndHitReal);
    }
    return sHandlerTableWakeUpSlap;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_NaturalGift(MethodInfo *method) {
    if (sHandlerTableNaturalGift == nullptr) {
        sHandlerTableNaturalGift = CreateEventHandlerTable(4);
        sHandlerTableNaturalGift->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_CHECK_3RD, (Il2CppMethodPointer) &HandlerNaturalGiftWazaExecuteCheck3rd);
        sHandlerTableNaturalGift->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_DONE, (Il2CppMethodPointer) &HandlerNaturalGiftWazaExecuteDone);
        sHandlerTableNaturalGift->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_PARAM, (Il2CppMethodPointer) &HandlerNaturalGiftWazaParam);
        sHandlerTableNaturalGift->m_Items[3] = CreateMoveEventHandler(EventID::WAZA_POWER_BASE, (Il2CppMethodPointer) &HandlerNaturalGiftWazaPowerBase);
    }
    return sHandlerTableNaturalGift;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_TrumpCard(MethodInfo *method) {
    if (sHandlerTableTrumpCard == nullptr) {
        sHandlerTableTrumpCard = CreateEventHandlerTable(1);
        sHandlerTableTrumpCard->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER_BASE, (Il2CppMethodPointer) &HandlerTrumpCardWazaPowerBase);
    }
    return sHandlerTableTrumpCard;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_LuckyChant(MethodInfo *method) {
    if (sHandlerTableLuckyChant == nullptr) {
        sHandlerTableLuckyChant = CreateEventHandlerTable(1);
        sHandlerTableLuckyChant->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA_NO_TARGET, (Il2CppMethodPointer) &HandlerLuckyChantUncategorizeWazaNoTarget);
    }
    return sHandlerTableLuckyChant;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MeFirst(MethodInfo *method) {
    if (sHandlerTableMeFirst == nullptr) {
        sHandlerTableMeFirst = CreateEventHandlerTable(2);
        sHandlerTableMeFirst->m_Items[0] = CreateMoveEventHandler(EventID::REQWAZA_PARAM, (Il2CppMethodPointer) &HandlerMeFirstReqwazaParam);
        sHandlerTableMeFirst->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerMeFirstWazaPower);
    }
    return sHandlerTableMeFirst;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Punishment(MethodInfo *method) {
    if (sHandlerTablePunishment == nullptr) {
        sHandlerTablePunishment = CreateEventHandlerTable(1);
        sHandlerTablePunishment->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER_BASE, (Il2CppMethodPointer) &HandlerPunishmentWazaPowerBase);
    }
    return sHandlerTablePunishment;
}
void PrintEventHandler(EventFactor_EventHandler_o *eh) {
    socket_log_fmt("eh->fields.super.super.method_ptr: %08X", eh->fields.super.super.method_ptr);
    socket_log_fmt("eh->fields.super.super.invoke_impl: %08X", eh->fields.super.super.invoke_impl);
    socket_log_fmt("eh->fields.super.super.m_target: %08X", eh->fields.super.super.m_target);
    socket_log_fmt("eh->fields.super.super.method: %08X", eh->fields.super.super.method);
    socket_log_fmt("eh->fields.super.super.delegate_trampoline: %08X", eh->fields.super.super.delegate_trampoline);
    socket_log_fmt("eh->fields.super.super.extra_arg: %08X", eh->fields.super.super.extra_arg);
    socket_log_fmt("eh->fields.super.super.method_code: %08X", eh->fields.super.super.method_code);
    socket_log_fmt("eh->fields.super.super.method_info: %08X", eh->fields.super.super.method_info);
    socket_log_fmt("eh->fields.super.super.original_method_info: %08X", eh->fields.super.super.original_method_info);
    socket_log_fmt("eh->fields.super.super.data: %08X", eh->fields.super.super.data);
    socket_log_fmt("eh->fields.super.super.method_is_virtual: %08X", eh->fields.super.super.method_is_virtual);
    socket_log_fmt("eh->fields.super.delegates: %08X", eh->fields.super.delegates);
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_FlameBurst(MethodInfo *method) {
    if (sHandlerTableFlameBurst == nullptr) {
        sHandlerTableFlameBurst = CreateEventHandlerTable(1);
        sHandlerTableFlameBurst->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerFlameBurstDamageprocEndHitReal);
    }
    return sHandlerTableFlameBurst;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Synchronoise(MethodInfo *method) {
    if (sHandlerTableSynchronoise == nullptr) {
        sHandlerTableSynchronoise = CreateEventHandlerTable(1);
        sHandlerTableSynchronoise->m_Items[0] = CreateMoveEventHandler(EventID::NOEFFECT_CHECK_L2, (Il2CppMethodPointer) &HandlerSynchronoiseNoeffectCheckL2);
    }
    return sHandlerTableSynchronoise;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_ChipAway(MethodInfo *method) {
    if (sHandlerTableChipAway == nullptr) {
        sHandlerTableChipAway = CreateEventHandlerTable(2);
        sHandlerTableChipAway->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_HIT_RANK, (Il2CppMethodPointer) &HandlerChipAwayWazaHitRank);
        sHandlerTableChipAway->m_Items[1] = CreateMoveEventHandler(EventID::DEFENDER_GUARD_PREV, (Il2CppMethodPointer) &HandlerChipAwayDefenderGuardPrev);
    }
    return sHandlerTableChipAway;
}

// Adds an entry to GET_FUNC_TABLE
void SetMoveFunctionTable(System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t wazaNo, Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Method_ADD_Karagenki, methodPointer);
    Waza_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    auto * func = (Waza_HandlerGetFunc_o *) il2cpp_object_new(Waza_HandlerGetFunc_TypeInfo);
    func->ctor((intptr_t)methodPointer, method);
    elem->fields.waza = wazaNo;
    elem->fields.func = func;
    *idx += 1;
}

// Remember to update when adding handlers
constexpr uint32_t NEW_MOVES_COUNT = 36;

// Entry point. Replaces system_array_new.
void * Waza_system_array_new(void * typeInfo, uint32_t len) {
    auto * getFuncTable = (System::Array<Waza_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_MOVES_COUNT);
    uint32_t idx = len;

    socket_log_initialize();

    //0
    SetMoveFunctionTable(getFuncTable, &idx, JUMP_KICK, (Il2CppMethodPointer) &ADD_JumpKick);
    SetMoveFunctionTable(getFuncTable, &idx, SONIC_BOOM, (Il2CppMethodPointer) &ADD_SonicBoom);
    SetMoveFunctionTable(getFuncTable, &idx, DRAGON_RAGE, (Il2CppMethodPointer) &ADD_DragonRage);
    SetMoveFunctionTable(getFuncTable, &idx, RAGE, (Il2CppMethodPointer) &ADD_Rage);
    SetMoveFunctionTable(getFuncTable, &idx, BIDE, (Il2CppMethodPointer) &ADD_Bide);
    SetMoveFunctionTable(getFuncTable, &idx, MIRROR_MOVE, (Il2CppMethodPointer) &ADD_MirrorMove);
    SetMoveFunctionTable(getFuncTable, &idx, PSYWAVE, (Il2CppMethodPointer) &ADD_Psywave);
    SetMoveFunctionTable(getFuncTable, &idx, SPIDER_WEB, (Il2CppMethodPointer) &Waza::ADD_KumoNoSu);
    SetMoveFunctionTable(getFuncTable, &idx, NIGHTMARE, (Il2CppMethodPointer) &ADD_Nightmare);
    SetMoveFunctionTable(getFuncTable, &idx, RETURN, (Il2CppMethodPointer) &ADD_Return);
    //10
    SetMoveFunctionTable(getFuncTable, &idx, FRUSTRATION, (Il2CppMethodPointer) &ADD_Frustration);
    SetMoveFunctionTable(getFuncTable, &idx, MAGNITUDE, (Il2CppMethodPointer) &ADD_Magnitude);
    SetMoveFunctionTable(getFuncTable, &idx, PURSUIT, (Il2CppMethodPointer) &ADD_Pursuit);
    SetMoveFunctionTable(getFuncTable, &idx, SMELLING_SALTS, (Il2CppMethodPointer) &ADD_SmellingSalts);
    SetMoveFunctionTable(getFuncTable, &idx, ASSIST, (Il2CppMethodPointer) &ADD_Assist);
    SetMoveFunctionTable(getFuncTable, &idx, REFRESH, (Il2CppMethodPointer) &ADD_Refresh);
    SetMoveFunctionTable(getFuncTable, &idx, SNATCH, (Il2CppMethodPointer) &ADD_Snatch);
    SetMoveFunctionTable(getFuncTable, &idx, SECRET_POWER, (Il2CppMethodPointer) &ADD_SecretPower);
    SetMoveFunctionTable(getFuncTable, &idx, CAMOUFLAGE, (Il2CppMethodPointer) &ADD_Camouflage);
    SetMoveFunctionTable(getFuncTable, &idx, MUD_SPORT, (Il2CppMethodPointer) &ADD_MudSport);
    //20
    SetMoveFunctionTable(getFuncTable, &idx, ICE_BALL, (Il2CppMethodPointer) &Waza::ADD_Korogaru);
    SetMoveFunctionTable(getFuncTable, &idx, SILVER_WIND, (Il2CppMethodPointer) &Waza::ADD_GensiNoTikara);
    SetMoveFunctionTable(getFuncTable, &idx, SKY_UPPERCUT, (Il2CppMethodPointer) &ADD_SkyUppercut);
    SetMoveFunctionTable(getFuncTable, &idx, WATER_SPORT, (Il2CppMethodPointer) &ADD_WaterSport);
    SetMoveFunctionTable(getFuncTable, &idx, WAKE_UP_SLAP, (Il2CppMethodPointer) &ADD_WakeUpSlap);
    SetMoveFunctionTable(getFuncTable, &idx, NATURAL_GIFT, (Il2CppMethodPointer) &ADD_NaturalGift);
    SetMoveFunctionTable(getFuncTable, &idx, TRUMP_CARD, (Il2CppMethodPointer) &ADD_TrumpCard);
    SetMoveFunctionTable(getFuncTable, &idx, WRING_OUT, (Il2CppMethodPointer) &Waza::ADD_Siboritoru);
    SetMoveFunctionTable(getFuncTable, &idx, LUCKY_CHANT, (Il2CppMethodPointer) &ADD_LuckyChant);
    SetMoveFunctionTable(getFuncTable, &idx, ME_FIRST, (Il2CppMethodPointer) &ADD_MeFirst);
    //30
    SetMoveFunctionTable(getFuncTable, &idx, PUNISHMENT, (Il2CppMethodPointer) &ADD_Punishment);
    SetMoveFunctionTable(getFuncTable, &idx, CAPTIVATE, (Il2CppMethodPointer) &Waza::ADD_Meromero);
    SetMoveFunctionTable(getFuncTable, &idx, OMINOUS_WIND, (Il2CppMethodPointer) &Waza::ADD_GensiNoTikara);
    SetMoveFunctionTable(getFuncTable, &idx, FLAME_BURST, (Il2CppMethodPointer) &ADD_FlameBurst);
    SetMoveFunctionTable(getFuncTable, &idx, SYNCHRONOISE, (Il2CppMethodPointer) &ADD_Synchronoise);
    SetMoveFunctionTable(getFuncTable, &idx, CHIP_AWAY, (Il2CppMethodPointer) &ADD_ChipAway);

    return getFuncTable;
}

// --- Other functions ---
// Pursuit
void PursuitInterrupt(Section_ProcessActionCore_o *section, PokeAction_o *action, uint8_t targetPokeID) {
    if (((Section_o *)section)->CheckEncoreWazaChange(action, nullptr) != NULL_WAZA) return;
    action->fields.actionDesc->fields.isOiutiInterruptAction = true;
    action->fields.actionParam_Fight->fields.targetPos =
            ((Section_o *)section)->GetPokePos(targetPokeID, nullptr);
    section->fields.super.m_pSectionContainer->fields.m_section_InterruptAction->processAction(action,
                                                                                               nullptr);
}
void PursuitProcess(Section_ProcessActionCore_o *section, PokeActionContainer_o *pokeActionContainer,
                    PokeAction_o *thisAction) {
    bool isPursuitTarget = thisAction->fields.actionCategory == PokeActionCategory::PokeChange;
    bool isFight = thisAction->fields.actionCategory == PokeActionCategory::Fight;
    if (!isPursuitTarget && isFight) {
        int32_t wazaID = thisAction->fields.actionParam_Fight->fields.waza;
        isPursuitTarget = wazaID == U_TURN || wazaID == VOLT_SWITCH || wazaID == PARTING_SHOT;
    }
    if (!isPursuitTarget) return;
    uint8_t thisPokeID = thisAction->fields.bpp->GetID(nullptr);
    for (int i = 0; i < pokeActionContainer->fields.m_count; i++) {
        PokeAction_o *action = pokeActionContainer->fields.m_actions->m_Items[i];
        if (action->fields.fDone ||
            action->fields.actionCategory != PokeActionCategory::Fight) continue;
        PokeActionParam_Fight_o *papf = action->fields.actionParam_Fight;
        if (papf->fields.waza != PURSUIT) continue;
        uint8_t pokeID = action->fields.bpp->GetID(nullptr);
        if (!isFight && section->fields.super.m_pMainModule->IsFriendPokeID(thisPokeID, pokeID,
                                                                            nullptr)) continue;
        if (isFight && papf->fields.aimTargetID != thisPokeID) continue;
        PursuitInterrupt(section, action, thisPokeID);
    }
}
void Dpr_Battle_Logic_Section_ProcessActionCore_Execute(Section_ProcessActionCore_o *spac,
                                                        Section_ProcessActionCore_Result_o *pResult,
                                                        Section_ProcessActionCore_Description_o **description,
                                                        MethodInfo *method) {
    PokeAction_o *pa = (*description)->fields.pokeAction;
    if (pa->fields.fDone) return;
    pa->fields.fDone = true;
    PursuitProcess(spac, spac->fields.super.m_pPokemonActionContainer, pa);
    int32_t pac = pa->fields.actionCategory;
    if (pac == PokeActionCategory::Cheer) {
        spac->action_Cheer(pa, nullptr);
        return;
    }
    BTL_POKEPARAM_o *bpp = pa->fields.bpp;
    if (bpp == nullptr || bpp->IsDead(nullptr)) return;
    uint8_t pokeID = bpp->GetID(nullptr);
    if (!spac->fields.super.m_pBattleEnv->fields.m_posPoke->IsExist(pokeID, nullptr)) return;
    ServerCommandPutter_o *scp = spac->fields.super.m_pServerCmdPutter;
    EventLauncher_o *el = spac->fields.super.m_pEventLauncher;
    if (bpp->CheckSick(WazaSick::WAZASICK_FREEFALL, nullptr) &&
        (pac != PokeActionCategory::Escape ||
         spac->fields.super.m_pMainModule->GetEscapeMode(nullptr) !=  BtlEscapeMode::BTL_ESCAPE_MODE_CONFIRM)) {
        if (bpp->COUNTER_Get(BTL_POKEPARAM_Counter::COUNTER_MAMORU, nullptr) != '\0')
            scp->SetBppCounter(bpp,BTL_POKEPARAM_Counter::COUNTER_MAMORU, 0, nullptr);
        el->Event_ActProcCanceled(pa, nullptr);
        return;
    }
    spac->reinforceRaidBoss(pa, nullptr);
    ActionDesc_o *ad = pa->fields.actionDesc;
    if (ad->fields.isOdorikoReaction ||
        ad->fields.isSaihaiReaction) {
        InsertActionInfo_o *iaf = (ad->fields).insertInfo;
        scp->InsertWazaInfo(pokeID, iaf->fields.isTokuseiWindowDisplay, &iaf->fields.prevActionMessage, nullptr);
    }
    el->Event_ActProcStart(pa, nullptr);
    bpp->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_ACTION_START, nullptr);
    spac->action(pa, nullptr);
    if (pac < 3) {
        bpp->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_ACTION_DONE, nullptr);
        scp->SetContFlag(bpp,ContFlag::CONTFLG_ACTION_DONE, nullptr);
    }
    if (spac->fields.super.m_pSharedData->fields.m_interruptAccessor->IsRequested(InterruptCode::QUIT_ESCAPE,
                                                                                  nullptr)) return;
    el->Event_ActProcEnd(bpp, pac, nullptr);
}
uint8_t Dpr_Battle_Logic_EventLauncher_Event_WazaExecuteStart(EventLauncher_o *el, ActionDesc_o *actionDesc,
                                                              BTL_POKEPARAM_o *attacker, WazaParam_o *wazaParam,
                                                              PokeSet_o *rec, WazaEffectParams_o *pWazaEffectParams,
                                                              MethodInfo *method) {
    uint8_t pokeCount = rec->fields.m_count;
    EventSystem_o *es = el->fields.m_pEventSystem;
    es->EVENTVAR_Push(nullptr);
    uint8_t pokeID = attacker->GetID(nullptr);
    es->EVENTVAR_SetConstValue(EventVar::POKEID, pokeID, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::POKEID_ATK, pokeID, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::WAZAID, wazaParam->fields.wazaID, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::WAZA_TYPE, wazaParam->fields.wazaType, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::OIUTI_INTERRUPT_FLAG,
                               actionDesc->fields.isOiutiInterruptAction, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::ACTION_DESC_IS_YOKODORI_ROB_ACTION,
                               actionDesc->fields.isYokodoriRobAction, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::ACTION_DESC_IS_ODORIKO_REACTION,
                               actionDesc->fields.isOdorikoReaction, nullptr);
    es->EVENTVAR_SetConstValue(EventVar::TARGET_POKECNT,pokeCount,nullptr);
    for (uint idx = 0; idx < pokeCount; idx++)
        es->EVENTVAR_SetConstValue(idx + 6, rec->Get(idx, nullptr)->GetID(nullptr),
                                   nullptr);
    es->EVENTVAR_SetRewriteOnceValue(EventVar::ENABLE_MODE, 0, nullptr);
    es->EVENTVAR_SetRewriteOnceValue(EventVar::EFFECT_WAZAID, NULL_WAZA, nullptr);
    es->CallEvent(EventID::WAZA_EXE_START, nullptr);
    int32_t enableMode = es->EVENTVAR_GetValue(EventVar::ENABLE_MODE, nullptr);
    int32_t effectWazaID = es->EVENTVAR_GetValue(EventVar::EFFECT_WAZAID, nullptr);
    es->EVENTVAR_Pop(nullptr);
    if (effectWazaID != NULL_WAZA)
        pWazaEffectParams->fields.effectWazaID = effectWazaID;
    return (uint8_t)enableMode;
}