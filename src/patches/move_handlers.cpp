#include "Dpr/Battle/Logic/ActionDesc.hpp"
#include "Dpr/Battle/Logic/ActPri.hpp"
#include "Dpr/Battle/Logic/BTL_CLIENT.hpp"
#include "Dpr/Battle/Logic/BtlEscapeMode.hpp"
#include "Dpr/Battle/Logic/BtlGround.hpp"
#include "Dpr/Battle/Logic/BTLV_STRPARAM.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/ContFlag.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/FieldStatus.hpp"
#include "Dpr/Battle/Logic/GRightsManager.hpp"
#include "Dpr/Battle/Logic/GShock.hpp"
#include "Dpr/Battle/Logic/GWaza.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Handler/Field.hpp"
#include "Dpr/Battle/Logic/Handler/Waza.hpp"
#include "Dpr/Battle/Logic/InterruptCode.hpp"
#include "Dpr/Battle/Logic/PokeActionCategory.hpp"
#include "Dpr/Battle/Logic/PokeID.hpp"
#include "Dpr/Battle/Logic/PokeSet.hpp"
#include "Dpr/Battle/Logic/Section_CalcActionPriority.hpp"
#include "Dpr/Battle/Logic/Section_CalcDamage.hpp"
#include "Dpr/Battle/Logic/Section_FreeFall_Release.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_AddViewEffect.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_ChangePokeType.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_CheckSpecialWazaAdditionalEffectOccur.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_ConsumeItem.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_DecrementPP.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_FieldEffect_Remove.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_FreeFallStart.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_SetItem.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_SwapItem.hpp"
#include "Dpr/Battle/Logic/Section_GShockWave.hpp"
#include "Dpr/Battle/Logic/Section_InterruptAction.hpp"
#include "Dpr/Battle/Logic/Section_ProcessActionCore.hpp"
#include "Dpr/Battle/Logic/Section_RecoverHP.hpp"
#include "Dpr/Battle/Logic/SICKCONT.hpp"
#include "Dpr/Battle/Logic/Tables.hpp"
#include "Dpr/Battle/Logic/WAZADATA.hpp"
#include "Dpr/Battle/Logic/WazaFailCause.hpp"
#include "Pml/Item/ItemData.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "Pml/PokePara/Sick.hpp"
#include "Pml/WazaData/WazaDamageType.hpp"
#include "Pml/WazaData/WazaDataSystem.hpp"
#include "Pml/WazaData/WazaFlag.hpp"
#include "Pml/WazaData/WazaRankEffect.hpp"
#include "Pml/WazaData/WazaSick.hpp"
#include "Pml/WazaData/WazaTarget.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"
#include "logger.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;
using namespace Pml::Item;
using namespace Pml::Personal;
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
constexpr int32_t STRUGGLE = 165;
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
constexpr int32_t SKY_DROP = 507;
constexpr int32_t BESTOW = 516;
constexpr int32_t VOLT_SWITCH = 521;
constexpr int32_t BELCH = 562;
constexpr int32_t ROTOTILLER = 563;
constexpr int32_t ION_DELUGE = 569;
constexpr int32_t PARTING_SHOT = 575;
constexpr int32_t SPOTLIGHT = 671;
constexpr int32_t GUARDIAN_OF_ALOLA = 698;
constexpr int32_t GENESIS_SUPERNOVA = 703;
constexpr int32_t LIGHT_THAT_BURNS_THE_SKY = 723;
constexpr int32_t SEARING_SUNRAZE_SMASH = 724;
constexpr int32_t MENACING_MOONRAZE_MAELSTROM = 725;
constexpr int32_t SPLINTERED_STORMSHARDS = 727;
constexpr int32_t PIKA_PAPOW = 732;
constexpr int32_t GLITZY_GLOW = 736;
constexpr int32_t BADDY_BAD = 737;
constexpr int32_t FREEZY_FROST = 739;
constexpr int32_t SPARKLY_SWIRL = 740;
constexpr int32_t VEEVEE_VOLLEY = 741;
constexpr int32_t STUFF_CHEEKS = 747;
constexpr int32_t MAX_FLARE = 757;
constexpr int32_t MAX_FLUTTERBY = 758;
constexpr int32_t MAX_LIGHTNING = 759;
constexpr int32_t MAX_STRIKE = 760;
constexpr int32_t MAX_KNUCKLE = 761;
constexpr int32_t MAX_PHANTASM = 762;
constexpr int32_t MAX_HAILSTORM = 763;
constexpr int32_t MAX_OOZE = 764;
constexpr int32_t MAX_GEYSER = 765;
constexpr int32_t MAX_AIRSTREAM = 766;
constexpr int32_t MAX_STARFALL = 767;
constexpr int32_t MAX_WYRMWIND = 768;
constexpr int32_t MAX_MINDSTORM = 769;
constexpr int32_t MAX_ROCKFALL = 770;
constexpr int32_t MAX_QUAKE = 771;
constexpr int32_t MAX_DARKNESS = 772;
constexpr int32_t MAX_OVERGROWTH = 773;
constexpr int32_t MAX_STEELSPIKE = 774;
constexpr int32_t EXPANDING_FORCE = 797;
constexpr int32_t STEEL_ROLLER = 798;
constexpr int32_t METEOR_BEAM = 800;
constexpr int32_t SHELL_SIDE_ARM = 801;
constexpr int32_t MISTY_EXPLOSION = 802;
constexpr int32_t GRASSY_GLIDE = 803;
constexpr int32_t RISING_VOLTAGE = 804;
constexpr int32_t TERRAIN_PULSE = 805;
constexpr int32_t BURNING_JEALOUSY = 807;
constexpr int32_t LASH_OUT = 808;
constexpr int32_t POLTERGEIST = 809;
constexpr int32_t CORROSIVE_GAS = 810;
constexpr int32_t FLIP_TURN = 812;
constexpr int32_t TRIPLE_AXEL = 813;
constexpr int32_t JUNGLE_HEALING = 816;
constexpr int32_t DRAGON_ENERGY = 820;
constexpr int32_t EERIE_SPELL = 826;
constexpr int32_t GIGATON_HAMMER = 893;

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
constexpr int32_t ION_DELUGE_FIELD = 6;
constexpr int32_t TERRAIN = 8;
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
constexpr uint16_t HEAT_ROCK = 284;
constexpr uint16_t ROSELI_BERRY = 686;
constexpr uint16_t KEE_BERRY = 687;
constexpr uint16_t MARANGA_BERRY = 688;

// WazaIdx
constexpr uint8_t NULL_WAZA_IDX = 4;

// SideEffectIDs
constexpr int32_t REFLECT_SIDE = 0;
constexpr int32_t LIGHT_SCREEN_SIDE = 1;
constexpr int32_t LUCKY_CHANT_SIDE = 5;
constexpr int32_t SPOTLIGHT_SIDE = 18;
constexpr int32_t G_MAX_CANNONADE_SIDE = 22;
constexpr int32_t G_MAX_VINE_LASH_SIDE = 23;

// DexIDs
constexpr uint16_t VENUSAUR = 3;
constexpr uint16_t CHARIZARD = 6;
constexpr uint16_t BLASTOISE = 9;
constexpr uint16_t BUTTERFREE = 12;
constexpr uint16_t PIKACHU = 25;
constexpr uint16_t MEOWTH = 52;
constexpr uint16_t MACHAMP = 68;
constexpr uint16_t GENGAR = 94;
constexpr uint16_t KINGLER = 99;
constexpr uint16_t LAPRAS = 131;
constexpr uint16_t EEVEE = 133;
constexpr uint16_t SNORLAX = 143;
constexpr uint16_t GARBODOR = 569;
constexpr uint16_t MELOETTA = 648;
constexpr uint16_t MELMETAL = 809;
constexpr uint16_t RILLABOOM = 812;
constexpr uint16_t CINDERACE = 815;
constexpr uint16_t INTELEON = 818;
constexpr uint16_t CORVIKNIGHT = 823;
constexpr uint16_t ORBEETLE = 826;
constexpr uint16_t DREDNAW = 834;
constexpr uint16_t COALOSSAL = 839;
constexpr uint16_t FLAPPLE = 841;
constexpr uint16_t APPLETUN = 842;
constexpr uint16_t SANDACONDA = 844;
constexpr uint16_t TOXTRICITY = 849;
constexpr uint16_t CENTISKORCH = 851;
constexpr uint16_t HATTERENE = 858;
constexpr uint16_t GRIMMSNARL = 861;
constexpr uint16_t ALCREMIE = 869;
constexpr uint16_t MORPEKO = 877;
constexpr uint16_t COPPERAJAH = 879;
constexpr uint16_t DURALUDON = 884;
constexpr uint16_t URSHIFU = 892;

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
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSkyDrop;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBestow;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableRototiller;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableIonDeluge;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSpotlight;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGuardianOfAlola;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGenesisSupernova;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSplinteredStormshards;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGlitzyGlow;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBaddyBad;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableFreezyFrost;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSparklySwirl;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMaxMove;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableExpandingForce;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSteelRoller;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMeteorBeam;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableShellSideArm;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMistyExplosion;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGrassyGlide;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableRisingVoltage;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableTerrainPulse;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBurningJealousy;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableLashOut;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePoltergeist;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableCorrosiveGas;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableTripleAxel;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableJungleHealing;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableEerieSpell;

// --- EventHandler delegates ---
uint8_t GetEnvironmentType(EventFactor_EventHandlerArgs_o **args) {
    switch (Common::GetGround(args, nullptr)) {
        case BtlGround::BTL_GROUND_GRASS: return GRASS;
        case BtlGround::BTL_GROUND_MIST: return FAIRY;
        case BtlGround::BTL_GROUND_ELEKI: return ELECTRIC;
        case BtlGround::BTL_GROUND_PHYCHO: return PSYCHIC;
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
                      false, false, true, true);
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
    auto power = (int32_t)(Common::GetPokeParam(args, pokeID, nullptr)->GetFriendship(nullptr) / 2.5);
    if (power < 1)
        power = 1;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}
// Frustration
void HandlerFrustrationWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    auto power = (int32_t)((255 - Common::GetPokeParam(args, pokeID, nullptr)->GetFriendship(nullptr)) /
            2.5);
    if (power < 1)
        power = 1;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
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
                      false, true);
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
    if (!HandlerAddFieldEffect(args, pokeID, MUD_SPORT_FIELD, 5)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Water Sport
void HandlerWaterSportFieldEffectCall(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!HandlerAddFieldEffect(args, pokeID, WATER_SPORT_FIELD, 5)) return;
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
TypePowerPair HandlerNaturalGiftTypePower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    switch (Common::GetPokeParam(args, pokeID, nullptr)->GetItem(nullptr)) {
        case CHERI_BERRY: return { FIRE, 80};
        case CHESTO_BERRY: return { WATER, 80};
        case PECHA_BERRY: return { ELECTRIC, 80};
        case RAWST_BERRY: return { GRASS, 80};
        case ASPEAR_BERRY: return { ICE, 80};
        case LEPPA_BERRY: return { FIGHTING, 80};
        case ORAN_BERRY: return { POISON, 80};
        case PERSIM_BERRY: return { GROUND, 80};
        case LUM_BERRY: return { FLYING, 80};
        case SITRUS_BERRY: return { PSYCHIC, 80};
        case FIGY_BERRY: return { BUG, 80};
        case WIKI_BERRY: return { ROCK, 80};
        case MAGO_BERRY: return { GHOST, 80};
        case AGUAV_BERRY: return { DRAGON, 80};
        case IAPAPA_BERRY: return { DARK, 80};
        case RAZZ_BERRY: return { STEEL, 80};
        case BLUK_BERRY: return { FIRE, 90};
        case NANAB_BERRY: return { WATER, 90};
        case WEPEAR_BERRY: return { ELECTRIC, 90};
        case PINAP_BERRY: return { GRASS, 90};
        case POMEG_BERRY: return { ICE, 90};
        case KELPSY_BERRY: return { FIGHTING, 90};
        case QUALOT_BERRY: return { POISON, 90};
        case HONDEW_BERRY: return { GROUND, 90};
        case GREPA_BERRY: return { FLYING, 90};
        case TAMATO_BERRY: return { PSYCHIC, 90};
        case CORNN_BERRY: return { BUG, 90};
        case MAGOST_BERRY: return { ROCK, 90};
        case RABUTA_BERRY: return { GHOST, 90};
        case NOMEL_BERRY: return { DRAGON, 90};
        case SPELON_BERRY: return { DARK, 90};
        case PAMTRE_BERRY: return { STEEL, 90};
        case WATMEL_BERRY: return { FIRE, 100};
        case DURIN_BERRY: return { WATER, 100};
        case BELUE_BERRY: return { ELECTRIC, 100};
        case OCCA_BERRY: return { FIRE, 80};
        case PASSHO_BERRY: return { WATER, 80};
        case WACAN_BERRY: return { ELECTRIC, 80};
        case RINDO_BERRY: return { GRASS, 80};
        case YACHE_BERRY: return { ICE, 80};
        case CHOPLE_BERRY: return { FIGHTING, 80};
        case KEBIA_BERRY: return { POISON, 80};
        case SHUCA_BERRY: return { GROUND, 80};
        case COBA_BERRY: return { FLYING, 80};
        case PAYAPA_BERRY: return { PSYCHIC, 80};
        case TANGA_BERRY: return { BUG, 80};
        case CHARTI_BERRY: return { ROCK, 80};
        case KASIB_BERRY: return { GHOST, 80};
        case HABAN_BERRY: return { DRAGON, 80};
        case COLBUR_BERRY: return { DARK, 80};
        case BABIRI_BERRY: return { STEEL, 80};
        case CHILAN_BERRY: return { NORMAL, 80};
        case LIECHI_BERRY: return { GRASS, 100};
        case GANLON_BERRY: return { ICE, 100};
        case SALAC_BERRY: return { FIGHTING, 100};
        case PETAYA_BERRY: return { POISON, 100};
        case APICOT_BERRY: return { GROUND, 100};
        case LANSAT_BERRY: return { FLYING, 100};
        case STARF_BERRY: return { PSYCHIC, 100};
        case ENIGMA_BERRY: return { BUG, 100};
        case MICLE_BERRY: return { ROCK, 100};
        case CUSTAP_BERRY: return { GHOST, 100};
        case JABOCA_BERRY: return { DRAGON, 100};
        case ROWAP_BERRY: return { DARK, 100};
        case ROSELI_BERRY: return { FAIRY, 80};
        case KEE_BERRY: return { FAIRY, 100};
        case MARANGA_BERRY: return { DARK, 100};
        default: return { NULL_TYPE, 0};
    }
}
void HandlerNaturalGiftWazaExecuteCheck3rd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (HandlerNaturalGiftTypePower(args, pokeID).type == NULL_TYPE ||
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
    uint16_t type = HandlerNaturalGiftTypePower(args, pokeID).type;
    if (type == NULL_TYPE) return;
    Common::RewriteEventVar(args, EventVar::WAZA_TYPE, type, nullptr);
}
void HandlerNaturalGiftWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, HandlerNaturalGiftTypePower(args, pokeID).power, nullptr);
}
// Trump Card
void HandlerTrumpCardWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint8_t wazaIdx = bpp->WAZA_SearchIdx(bpp->fields.m_prevSelectWazaID, nullptr);
    if (wazaIdx == NULL_WAZA_IDX) return;
    int32_t power = 40;
    switch (bpp->WAZA_GetPP(wazaIdx, nullptr)) {
        case 0: power = 200; break;
        case 1: power = 80; break;
        case 2: power = 60; break;
        case 3: power = 50; break;
    }
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}
// Lucky Chant
void HandlerLuckyChantUncategorizeWazaNoTarget(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!HandlerAddSideEffect(args, pokeID, LUCKY_CHANT_SIDE, Common::PokeIDtoSide(args, &pokeID, nullptr), SICKCONT::MakeTurn(pokeID, 5, nullptr))) return;
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
// Dark Void
void Dpr_Battle_Logic_Handler_Waza_handler_DarkHole(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) { }
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
// Sky Drop
void HandlerSkyDropCheckTameturnFail(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    auto *desc = (Section_FromEvent_FreeFallStart_Description_o *)
            malloc(sizeof(Section_FromEvent_FreeFallStart_Description_o));
    desc->ctor(nullptr);
    desc->fields.attackerID = pokeID;
    desc->fields.targetID = Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr);
    auto *wp = (WazaParam_o *) il2cpp_object_new(WazaParam_TypeInfo);
    wp->ctor(nullptr);
    int32_t wazaID = Common::GetSubID(args, nullptr);
    (*args)->fields.pSectionContainer->fields.m_section_FromEvent_FreeFallStart->fields.super.m_pEventLauncher->
    Event_GetWazaParam(wazaID, wazaID, wazaID, 0,
                       Common::GetPokeParam(args, pokeID, nullptr), wp, nullptr);
    desc->fields.wazaParam = wp;
    if (!Common::FreeFallStart(args, &desc, nullptr))
        Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
    free(desc);
}
void HandlerSkyDropNoeffectCheckL2(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!Common::GetPokeParam(args, Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr),
                              nullptr)->IsMatchType(FLYING, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::NOEFFECT_FLAG, true, nullptr);
}
void HandlerSkyDropWazaExeStart(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    auto *desc = (Section_FreeFall_Release_Description_o *) malloc(sizeof(Section_FreeFall_Release_Description_o));
    desc->ctor(nullptr);
    desc->fields.attacker = Common::GetPokeParam(args, pokeID, nullptr);
    desc->fields.canAppearSelf = true;
    desc->fields.canAppearTarget = true;
    Common::FreeFallRelease(args, &desc, nullptr);
    free(desc);
}
// Bestow
void HandlerBestowUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint16_t itemID = bpp->GetItem(nullptr);
    if (itemID == NULL_ITEM) return;
    uint8_t targetPokeID = Common::GetEventVar(args, EventVar::POKEID_TARGET1, nullptr);
    BTL_POKEPARAM_o *targetBPP = Common::GetPokeParam(args, targetPokeID, nullptr);
    if (targetBPP->GetItem(nullptr) != NULL_ITEM) return;
    if (Calc::ITEM_IsMail(itemID, nullptr)) return;
    if (Common::CheckUnbreakablePokeItem(targetBPP->GetMonsNo(nullptr), itemID, nullptr)) return;
    if (Common::CheckUnbreakablePokeItem(bpp->GetMonsNo(nullptr), itemID, nullptr)) return;
    system_load_typeinfo((void *)0xaa76);
    auto *desc = (Section_FromEvent_SwapItem_Description_o *)
            il2cpp_object_new(Section_FromEvent_SwapItem_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.userPokeID = pokeID;
    desc->fields.targetPokeID = targetPokeID;
    if (!Common::SwapItem(args, &desc, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Relic Song
uint8_t HandlerRelicSongGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void Dpr_Battle_Logic_Handler_Waza_handler_InisieNoUta(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint16_t dexID = bpp->GetMonsNo(nullptr);
    if (dexID != MELOETTA) return;
    uint8_t formNo = bpp->fields.m_formNo;
    uint8_t form0 = HandlerRelicSongGetFormID(formNo, 0);
    uint8_t nextForm = (formNo == form0) ? HandlerRelicSongGetFormID(formNo, 1) : form0;
    if (nextForm >= PersonalSystem::GetPersonalData(dexID, 0, nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, false, true);
}
// Rototiller
void HandlerRototillerNoeffectCheckL2(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint8_t targetPokeID = Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr);
    if (Field::common_isGroundEffective(args, targetPokeID, nullptr) &&
    Common::GetPokeParam(args, targetPokeID, nullptr)->IsMatchType(GRASS, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::NOEFFECT_FLAG, true, nullptr);
}
// Ion Deluge
void HandlerIonDelugeFieldEffectCall(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!HandlerAddFieldEffect(args, pokeID, ION_DELUGE_FIELD, 1)) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Hyperspace Fury
void Dpr_Battle_Logic_Handler_Waza_handler_IjigenRush(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {}
// Spotlight
void HandlerSpotlightUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint8_t targetPokeID = Common::GetEventVar(args, EventVar::POKEID_TARGET1, nullptr);
    if (!HandlerAddSideEffect(args, pokeID, SPOTLIGHT_SIDE,
                              Common::PokeIDtoOpponentSide(args, &targetPokeID, nullptr),
                              SICKCONT::MakePokeTurn(pokeID, targetPokeID, 1,
                                                     nullptr))) return;
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Guardian of Alola
void HandlerGuardianOfAlolaWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    auto damage = (int32_t)(Common::GetPokeParam(args, Common::GetEventVar(args, EventVar::POKEID_DEF,
                                                                            nullptr),
                                                  nullptr)->GetValue(BTL_POKEPARAM_ValueID::BPP_HP,
                                                                     nullptr) * 0.75);
    if (damage < 1)
        damage = 1;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE, damage, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
}
// Genesis Supernova
void HandlerGenesisSupernovaDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Waza::handler_common_GroundSet(args, pokeID, BtlGround::BTL_GROUND_PHYCHO, nullptr);
}
// Splintered Stormshards
void HandlerSplinteredStormshardsDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t effType = TERRAIN;
    if (!Common::CheckFieldEffect(args, &effType, nullptr)) return;
    system_load_typeinfo((void *)0x89b9);
    auto *desc = (Section_FromEvent_FieldEffect_Remove_Description_o *)
            il2cpp_object_new(Section_FromEvent_FieldEffect_Remove_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.effect = effType;
    Common::RemoveFieldEffect(args, &desc, nullptr);
}
// Glitzy Glow
void HandlerGlitzyGlowDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    HandlerAddSideEffect(args, pokeID, LIGHT_SCREEN_SIDE,
                         Common::PokeIDtoSide(args, &pokeID, nullptr),
                         SICKCONT::MakeTurn(pokeID, 5, nullptr));
}
// Baddy Bad
void HandlerBaddyBadDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    HandlerAddSideEffect(args, pokeID, REFLECT_SIDE, Common::PokeIDtoSide(args, &pokeID, nullptr),
                         SICKCONT::MakeTurn(pokeID, 5, nullptr));
}
// Freezy Frost
void HandlerFreezyFrostDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    HandlerRankResetAll(args, pokeID);
}
// Sparkly Swirl
void HandlerSparklySwirlDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Waza::common_CureFriendPokeSick(args, pokeID, true, false, nullptr);
}
// Max Guard
bool HandlerMaxMoveIsMaxGuardBypass(BTL_POKEPARAM_o *bpp, uint8_t type) {
    return (bpp->GetMonsNo(nullptr) == URSHIFU && bpp->fields.m_formNo == 2 && type == DARK) ||
           (bpp->GetMonsNo(nullptr) == URSHIFU && bpp->fields.m_formNo == 3 && type == WATER);
}
void Dpr_Battle_Logic_Handler_Waza_handler_DaiWall_NoEffectCheck(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    system_load_typeinfo((void *)0xa91e);
    uint8_t atkPokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr);
    if (atkPokeID == pokeID) return;
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Tables::IsDaiWallGuardDisable(Common::GetEventVar(args, EventVar::WAZAID, nullptr),
                                      nullptr)) return;
    if (HandlerMaxMoveIsMaxGuardBypass(Common::GetPokeParam(args, atkPokeID, nullptr),
                                       Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr)))
        return;
    Common::RewriteEventVar(args, EventVar::NOEFFECT_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::GEN_FLAG, true, nullptr);
    auto *desc = (Section_FromEvent_AddViewEffect_Description_o *)
            il2cpp_object_new(Section_FromEvent_AddViewEffect_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.effectNo = 0xba;
    desc->fields.pos_from = Common::PokeIDtoPokePos(args, &pokeID, nullptr);
    desc->fields.pos_to = 5;
    desc->fields.isMessageWindowVanish = true;
    Common::AddViewEffect(args, &desc, nullptr);
    auto *sp = (StrParam_o *)Common::GetEventVarAddress(args, EventVar::WORK_ADRS, nullptr);
    sp->Setup(2, 0x2c2, nullptr);
    sp->AddArg(pokeID, nullptr);
}
// Max Moves
uint8_t Pml_WazaData_WazaDataSystem_GetGPower(int32_t id,MethodInfo *method) {
    return WazaDataSystem::GetPower(id, nullptr);
}
bool HandlerMaxMoveIsPowerEffect(BTL_POKEPARAM_o *bpp, uint8_t type) {
    return (bpp->GetMonsNo(nullptr) == RILLABOOM && bpp->fields.m_formNo == 1 && type == GRASS) ||
           (bpp->GetMonsNo(nullptr) == CINDERACE && bpp->fields.m_formNo == 1 && type == FIRE) ||
           (bpp->GetMonsNo(nullptr) == INTELEON && bpp->fields.m_formNo == 1 && type == WATER);
}
void HandlerMaxMoveDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint16_t dexID = bpp->GetMonsNo(nullptr);
    uint16_t formID = bpp->fields.m_formNo;
    uint8_t gShockEffect = GShock_Effect::NONE;
    uint8_t type = Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr);
    if (HandlerMaxMoveIsPowerEffect(bpp, type)) return;
    if (HandlerMaxMoveIsMaxGuardBypass(bpp, type)) return;
    switch (type) {
        case FIRE:
            gShockEffect = GShock_Effect::WEATHER_SHINE;
            if (dexID == CHARIZARD && formID == 3)
                gShockEffect = GShock_Effect::SIDE_HONOO;
            if (dexID == CENTISKORCH && formID == 1)
                gShockEffect = GShock_Effect::HONOONOUZU;
            break;
        case BUG:
            gShockEffect = GShock_Effect::RANKDOWN_SPATK;
            if (dexID == BUTTERFREE && formID == 1)
                gShockEffect = GShock_Effect::SICK_DOKU_MAHI_NEMURI;
            break;
        case ELECTRIC:
            gShockEffect = GShock_Effect::FIELD_ELEC;
            if (dexID == PIKACHU && formID == 16)
                gShockEffect = GShock_Effect::SICK_MAHI;
            if (dexID == TOXTRICITY && (formID == 2 || formID == 3))
                gShockEffect = GShock_Effect::SICK_DOKU_MAHI;
            break;
        case NORMAL:
            gShockEffect = GShock_Effect::RANKDOWN_AGI;
            if (dexID == EEVEE && formID == 2)
                gShockEffect = GShock_Effect::SICK_MEROMERO;
            if (dexID == MEOWTH && formID == 3)
                gShockEffect = GShock_Effect::NEKONIKOBAN;
            if (dexID == SNORLAX && formID == 1)
                gShockEffect = GShock_Effect::SYUUKAKU;
            break;
        case FIGHTING:
            gShockEffect = GShock_Effect::RANKUP_ATK;
            if (dexID == MACHAMP && formID == 1)
                gShockEffect = GShock_Effect::RANKUP_CRITICAL;
            break;
        case GHOST:
            gShockEffect = GShock_Effect::RANKDOWN_DEF;
            if (dexID == GENGAR && formID == 2)
                gShockEffect = GShock_Effect::TOOSENBOU;
            break;
        case ICE:
            gShockEffect = GShock_Effect::WEATHER_SNOW;
            if (dexID == LAPRAS && formID == 1)
                gShockEffect = GShock_Effect::AURORAVEIL;
            break;
        case POISON:
            gShockEffect = GShock_Effect::RANKUP_SPATK;
            if (dexID == GARBODOR && formID == 1)
                gShockEffect = GShock_Effect::SICK_DOKU;
            break;
        case WATER:
            gShockEffect = GShock_Effect::WEATHER_RAIN;
            if (dexID == KINGLER && formID == 1)
                gShockEffect = GShock_Effect::RANKDOWN_AGI2;
            if (dexID == DREDNAW && formID == 1)
                gShockEffect = GShock_Effect::STEALTHROCK;
            if (dexID == BLASTOISE && formID == 2) {
                uint8_t targetPokeID = Common::GetEventVar(args, EventVar::POKEID_TARGET1, nullptr);
                HandlerAddSideEffect(args, pokeID, G_MAX_CANNONADE_SIDE,
                                     Common::PokeIDtoSide(args, &targetPokeID, nullptr),
                                     SICKCONT::MakeTurn(pokeID, 4, nullptr));
                return;
            }
            break;
        case FLYING:
            gShockEffect = GShock_Effect::RANKUP_AGI;
            if (dexID == CORVIKNIGHT && formID == 1)
                gShockEffect = GShock_Effect::KIRIBARAI;
            break;
        case FAIRY:
            gShockEffect = GShock_Effect::FIELD_MIST;
            if (dexID == HATTERENE && formID == 1)
                gShockEffect = GShock_Effect::SICK_KONRAN;
            if (dexID == ALCREMIE && formID == 63)
                gShockEffect = GShock_Effect::RECOVER_HP;
            break;
        case DRAGON:
            gShockEffect = GShock_Effect::RANKDOWN_ATK;
            if (dexID == DURALUDON && formID == 1)
                gShockEffect = GShock_Effect::DECREMENT_PP;
            break;
        case PSYCHIC:
            gShockEffect = GShock_Effect::FIELD_PSYCO;
            if (dexID == ORBEETLE && formID == 1)
                gShockEffect = GShock_Effect::JURYOKU;
            break;
        case ROCK:
            gShockEffect = GShock_Effect::WEATHER_SAND;
            if (dexID == COALOSSAL && formID == 1)
                gShockEffect = GShock_Effect::SIDE_IWA;
            break;
        case GROUND:
            gShockEffect = GShock_Effect::RANKUP_SPDEF;
            if (dexID == SANDACONDA && formID == 1)
                gShockEffect = GShock_Effect::SUNAZIGOKU;
            break;
        case DARK:
            gShockEffect = GShock_Effect::RANKDOWN_SPDEF;
            if (dexID == GRIMMSNARL && formID == 1)
                gShockEffect = GShock_Effect::AKUBI;
            break;
        case GRASS:
            gShockEffect = GShock_Effect::FIELD_GRASS;
            if (dexID == FLAPPLE && formID == 1)
                gShockEffect = GShock_Effect::RANKDOWN_AVOID;
            if (dexID == APPLETUN && formID == 1)
                gShockEffect = GShock_Effect::CURE_SICK;
            if (dexID == VENUSAUR && formID == 2) {
                uint8_t targetPokeID = Common::GetEventVar(args, EventVar::POKEID_TARGET1, nullptr);
                HandlerAddSideEffect(args, pokeID, G_MAX_VINE_LASH_SIDE,
                                     Common::PokeIDtoSide(args, &targetPokeID, nullptr),
                                     SICKCONT::MakeTurn(pokeID, 4, nullptr));
                return;
            }
            break;
        case STEEL:
            gShockEffect = GShock_Effect::RANKUP_DEF;
            if (dexID == MELMETAL && formID == 1)
                gShockEffect = GShock_Effect::ICHAMON;
            if (dexID == COPPERAJAH && formID == 1)
                gShockEffect = GShock_Effect::STEALTHROCK_HAGANE;
            break;
        default:
            return;
    }
    system_load_typeinfo((void *)0x7823);
    auto *param = (GShockEffectParam_SetupParam_o *) il2cpp_object_new(GShockEffectParam_SetupParam_TypeInfo);
    param->ctor(nullptr);
    param->fields.pMainModule = (*args)->fields.pMainModule;
    param->fields.pBattleEnv = (*args)->fields.pBattleEnv;
    param->fields.pActionDesc = Common::SearchByPokeID(args, pokeID, true, true, nullptr)->
            fields.actionDesc;
    param->fields.pAttaker = Common::GetPokeParam(args, pokeID, nullptr);
    param->fields.pDefender =
            Common::GetPokeParam(args, Common::GetEventVar(args, EventVar::POKEID_TARGET1, nullptr),
                                 nullptr);
    param->fields.gShockEffect = gShockEffect;
    auto *pEffectParam = (GShockEffectParam_o *) il2cpp_object_new(GShockEffectParam_TypeInfo);
    pEffectParam->ctor(&param, nullptr);
    (*args)->fields.pSectionContainer->fields.m_section_GShockWave->applyEffect(pEffectParam, nullptr);
}
void HandlerMaxMoveWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (!HandlerMaxMoveIsPowerEffect(bpp, Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr)))
        return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, 160, nullptr);
}
void HandlerMaxMoveWazaseqStart(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (!HandlerMaxMoveIsPowerEffect(bpp, WAZADATA::GetType(Common::GetEventVar(args, EventVar::WAZAID,
                                                                                nullptr), nullptr)))
        return;
    Waza::handler_MeteorDrive_WazaSeqStart(args, pokeID, nullptr);
}
void HandlerMaxMoveWazaseqEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (!HandlerMaxMoveIsPowerEffect(bpp, WAZADATA::GetType(Common::GetEventVar(args, EventVar::WAZAID,
                                                                                nullptr), nullptr)))
        return;
    Waza::handler_MeteorDrive_WazaSeqEnd(args, pokeID, nullptr);
}
// Aura Wheel
uint8_t HandlerAuraWheelGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void Dpr_Battle_Logic_Handler_Waza_handler_AuraGuruma(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {}
void Dpr_Battle_Logic_Handler_Waza_handler_AuraGuruma_Waza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->GetMonsNo(nullptr) != MORPEKO) return;
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo == HandlerAuraWheelGetFormID(formNo, 0))
        Common::RewriteEventVar(args, EventVar::WAZA_TYPE, ELECTRIC, nullptr);
    else
        Common::RewriteEventVar(args, EventVar::WAZA_TYPE, DARK, nullptr);
}
// Expanding Force
void HandlerExpandingForceWazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetGround(args, nullptr) != BtlGround::BTL_GROUND_PHYCHO) return;
    if (!Field::common_isGroundEffective(args, pokeID, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::TARGET_TYPE, WazaTarget::TARGET_ENEMY_ALL, nullptr);
}
void HandlerExpandingForceWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetGround(args, nullptr) != BtlGround::BTL_GROUND_PHYCHO) return;
    if (!Field::common_isGroundEffective(args, pokeID, nullptr)) return;
    Common::MulEventVar(args, EventVar::WAZA_POWER_RATIO, 0x1800, nullptr);
}
// Steel Roller
void HandlerSteelRollerWazaExecuteCheck3rd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    int32_t effType = TERRAIN;
    if (Common::CheckFieldEffect(args, &effType, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::FAIL_CAUSE, WazaFailCause::OTHER, nullptr);
}
// Meteor Beam
void HandlerMeteorBeamTameStartFixed(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    HandlerRankEffect(args, pokeID, pokeID, WazaRankEffect::SP_ATTACK, 1,
                      false, false, true, true);
}
// Shell Side Arm
uint32_t HandlerShellSideArmCalcDamageBase(EventLauncher_o *el, BTL_POKEPARAM_o *attacker, BTL_POKEPARAM_o *defender, WazaParam_o *wp) {
    bool isBurnDisabled = true;
    return Calc::DamageBase(el->Event_getWazaPower(attacker, defender, wp, nullptr),
                            el->Event_getAttackPower(attacker, defender, wp, false,
                                                     &isBurnDisabled, nullptr),
                            attacker->GetValue(BTL_POKEPARAM_ValueID::BPP_LEVEL, nullptr),
                            el->Event_getDefenderGuard(attacker, defender, wp, false,
                                                       nullptr),
                            nullptr);
}
void HandlerShellSideArmWazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    EventLauncher_o *el = (*args)->fields.pSectionContainer->fields.m_section_CalcDamage->fields.super.m_pEventLauncher;
    BTL_POKEPARAM_o *attacker = Common::GetPokeParam(args, pokeID, nullptr);
    PokeAction_o *pa = Common::SearchByPokeID(args, pokeID, true, true, nullptr);
    if (pa == nullptr) return;
    BTL_POKEPARAM_o *defender = Common::GetPokeParam(args, pa->fields.actionParam_Fight->fields.aimTargetID,
                                                     nullptr);
    auto *wp = (WazaParam_o *) il2cpp_object_new(WazaParam_TypeInfo);
    wp->ctor(nullptr);
    uint16_t wazaID = Common::GetSubID(args, nullptr);
    wp->fields.wazaID = wazaID;
    wp->fields.orgWazaID = wazaID;
    wp->fields.gSrcWazaID = wazaID;
    wp->fields.userType = attacker->GetPokeType(nullptr);
    wp->fields.wazaType = WAZADATA::GetType(wazaID, nullptr);
    wp->fields.damageType = WazaDamageType::PHYSIC;
    wp->fields.touchFlag = true;
    wp->fields.targetType = WAZADATA::GetWazaTarget(wazaID, nullptr);
    wp->fields.wazaPri = 0;
    wp->fields.wazaPower = WAZADATA::GetPower(wazaID, nullptr);
    uint32_t physicalDamage = HandlerShellSideArmCalcDamageBase(el, attacker, defender, wp);
    wp->fields.damageType = WazaDamageType::SPECIAL;
    wp->fields.touchFlag = false;
    uint32_t specialDamage = HandlerShellSideArmCalcDamageBase(el, attacker, defender, wp);
    if (physicalDamage > specialDamage || (physicalDamage == specialDamage && Calc::GetRand(2, nullptr))) {
        Common::RewriteEventVar(args, EventVar::DAMAGE_TYPE, WazaDamageType::PHYSIC, nullptr);
        Common::RewriteEventVar(args, EventVar::WAZA_TOUCH_FLAG, true, nullptr);
    }
    else {
        Common::RewriteEventVar(args, EventVar::DAMAGE_TYPE, WazaDamageType::SPECIAL, nullptr);
        Common::RewriteEventVar(args, EventVar::WAZA_TOUCH_FLAG, false, nullptr);
    }
}
// Misty Explosion
void HandlerMistyExplosionWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetGround(args, nullptr) != BtlGround::BTL_GROUND_MIST) return;
    if (!Field::common_isGroundEffective(args, pokeID, nullptr)) return;
    Common::MulEventVar(args, EventVar::WAZA_POWER_RATIO, 0x1800, nullptr);
}
// Grassy Glide
void HandlerGrassyGlideGetWazaPri(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetGround(args, nullptr) != BtlGround::BTL_GROUND_GRASS) return;
    if (!Field::common_isGroundEffective(args, pokeID, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::WAZA_PRI, Common::GetEventVar(args, EventVar::WAZA_PRI,
                                                                          nullptr) + 1, nullptr);
}
// Rising Voltage
void HandlerRisingVoltageWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetGround(args, nullptr) != BtlGround::BTL_GROUND_ELEKI) return;
    if (!Field::common_isGroundEffective(args, Common::GetEventVar(args, EventVar::POKEID_DEF,
                                                                   nullptr), nullptr)) return;
    Common::MulEventVar(args, EventVar::WAZA_POWER_RATIO, 0x2000, nullptr);
}
// Terrain Pulse
void HandlerTerrainPulseWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetGround(args, nullptr) == BtlGround::BTL_GROUND_NONE) return;
    if (!Field::common_isGroundEffective(args, pokeID, nullptr)) return;
    Common::MulEventVar(args, EventVar::WAZA_POWER_RATIO, 0x2000, nullptr);
}
void HandlerTerrainPulseWazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    uint8_t type = NORMAL;
    switch (Common::GetGround(args, nullptr)) {
        case BtlGround::BTL_GROUND_GRASS: type = GRASS; break;
        case BtlGround::BTL_GROUND_MIST: type = FAIRY; break;
        case BtlGround::BTL_GROUND_ELEKI: type = ELECTRIC; break;
        case BtlGround::BTL_GROUND_PHYCHO: type = PSYCHIC; break;
    }
    Common::RewriteEventVar(args, EventVar::WAZA_TYPE, type, nullptr);
}
// Burning Jealousy
void HandlerBurningJealousyAddSick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetPokeParam(args, Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr), nullptr)->TURNFLAG_Get(
            BTL_POKEPARAM_TurnFlag::TURNFLG_RANK_UP, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::ADD_PER, 0, nullptr);
}
// Lash Out
void HandlerLashOutWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (!Common::GetPokeParam(args, pokeID, nullptr)->TURNFLAG_Get(
            BTL_POKEPARAM_TurnFlag::TURNFLG_RANK_DOWN, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER_RATIO, 0x2000, nullptr);
}
// Poltergeist
void HandlerPoltergeistWazaExecuteCheck3rd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetPokeParam(args, Common::GetEventVar(args, EventVar::POKEID_TARGET1, nullptr),
                             nullptr)->GetItem(nullptr) != NULL_ITEM) return;
    Common::RewriteEventVar_FAIL_CAUSE(args, WazaFailCause::OTHER, nullptr);
}
// Corrosive Gas
void HandlerCorrosiveGasUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    bool success = false;
    system_load_typeinfo((void *)0xa965);
    for (int32_t i = 0; i < targetCount; ++i) {
        uint8_t targetPokeID = Common::GetEventVar(args, 6 + i, nullptr);
        if (Common::CheckCantStealPoke(args, pokeID, targetPokeID, nullptr)) continue;
        if (Common::GetPokeParam(args, targetPokeID, nullptr)->GetItem(nullptr) == NULL_ITEM)
            continue;
        auto *desc = (Section_FromEvent_SetItem_Description_o *)
                il2cpp_object_new(Section_FromEvent_SetItem_Description_TypeInfo);
        desc->ctor(nullptr);
        desc->fields.userPokeID = pokeID;
        desc->fields.targetPokeID = targetPokeID;
        desc->fields.itemID = 0;
        if (Common::SetItem(args, &desc, nullptr))
            success = true;
    }
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, success, nullptr);
}
// Triple Axel
void HandlerTripleAxelWazaPowerBase(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t hitCounter = Common::GetWorkValue(args, A, nullptr) + 1;
    Common::SetWorkValue(args, A, hitCounter, nullptr);
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, hitCounter * 20, nullptr);
}
// Jungle Healing
void HandlerJungleHealingUncategorizeWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    system_load_typeinfo((void *)0x4b47);
    for (int32_t i = 0; i < targetCount; ++i) {
        uint8_t targetPokeID = Common::GetEventVar(args, 6 + i, nullptr);
        auto *desc = (Section_RecoverHP_Description_o *)
                il2cpp_object_new(Section_RecoverHP_Description_TypeInfo);
        desc->ctor(nullptr);
        desc->fields.userPokeID = pokeID;
        desc->fields.targetPokeID = targetPokeID;
        desc->fields.recoverHP = Calc::QuotMaxHP(Common::GetPokeParam(args, targetPokeID, nullptr),
                                                 4, true, nullptr);
        desc->fields.isSkipFailCheckSP = false;
        Common::RecoverHP(args, &desc, nullptr);
        uint32_t sickID = Common::CheckPokeSick(args, targetPokeID, nullptr);
        if (sickID != Sick::NONE)
            HandlerCureSick(args, pokeID, (int32_t)sickID, targetPokeID);
    }
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
// Eerie Spell
void HandlerEerieSpellDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t targetCount = Common::GetEventVar(args, EventVar::TARGET_POKECNT, nullptr);
    system_load_typeinfo((void *)0xaa7b);
    for (int32_t i = 0; i < targetCount; ++i) {
        uint8_t targetPokeID = Common::GetEventVar(args, 6 + i, nullptr);
        BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, targetPokeID, nullptr);
        uint8_t wazaIdx = bpp->WAZA_SearchIdx(bpp->fields.m_prevSelectWazaID, nullptr);
        if (wazaIdx == NULL_WAZA_IDX) continue;
        uint16_t ppCount = bpp->WAZA_GetPP(wazaIdx, nullptr);
        uint8_t volume = 3;
        if (volume > ppCount)
            volume = ppCount;
        if (volume == 0) continue;
        auto *desc = (Section_FromEvent_DecrementPP_Description_o *)
                il2cpp_object_new(Section_FromEvent_DecrementPP_Description_TypeInfo);
        desc->ctor(nullptr);
        desc->fields.pokeID = targetPokeID;
        desc->fields.wazaIdx = wazaIdx;
        desc->fields.volume = volume;
        Common::DecrementPP(args, &desc, nullptr);
    }
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
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SkyDrop(MethodInfo *method) {
    if (sHandlerTableSkyDrop == nullptr) {
        sHandlerTableSkyDrop = CreateEventHandlerTable(3);
        sHandlerTableSkyDrop->m_Items[0] = CreateMoveEventHandler(EventID::CHECK_TAMETURN_FAIL, (Il2CppMethodPointer) &HandlerSkyDropCheckTameturnFail);
        sHandlerTableSkyDrop->m_Items[1] = CreateMoveEventHandler(EventID::NOEFFECT_CHECK_L2, (Il2CppMethodPointer) &HandlerSkyDropNoeffectCheckL2);
        sHandlerTableSkyDrop->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_EXE_START, (Il2CppMethodPointer) &HandlerSkyDropWazaExeStart);
    }
    return sHandlerTableSkyDrop;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Bestow(MethodInfo *method) {
    if (sHandlerTableBestow == nullptr) {
        sHandlerTableBestow = CreateEventHandlerTable(1);
        sHandlerTableBestow->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerBestowUncategorizeWaza);
    }
    return sHandlerTableBestow;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Rototiller(MethodInfo *method) {
    if (sHandlerTableRototiller == nullptr) {
        sHandlerTableRototiller = CreateEventHandlerTable(2);
        sHandlerTableRototiller->m_Items[0] = CreateMoveEventHandler(EventID::NOEFFECT_CHECK_L2, (Il2CppMethodPointer) &HandlerRototillerNoeffectCheckL2);
        sHandlerTableRototiller->m_Items[1] = CreateMoveEventHandler(EventID::CHECK_POKE_HIDE, (Il2CppMethodPointer) &Waza::handler_Tagayasu_CheckHide);
    }
    return sHandlerTableRototiller;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_IonDeluge(MethodInfo *method) {
    if (sHandlerTableIonDeluge == nullptr) {
        sHandlerTableIonDeluge = CreateEventHandlerTable(1);
        sHandlerTableIonDeluge->m_Items[0] = CreateMoveEventHandler(EventID::FIELD_EFFECT_CALL, (Il2CppMethodPointer) &HandlerIonDelugeFieldEffectCall);
    }
    return sHandlerTableIonDeluge;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Spotlight(MethodInfo *method) {
    if (sHandlerTableSpotlight == nullptr) {
        sHandlerTableSpotlight = CreateEventHandlerTable(1);
        sHandlerTableSpotlight->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerSpotlightUncategorizeWaza);
    }
    return sHandlerTableSpotlight;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GuardianOfAlola(MethodInfo *method) {
    if (sHandlerTableGuardianOfAlola == nullptr) {
        sHandlerTableGuardianOfAlola = CreateEventHandlerTable(1);
        sHandlerTableGuardianOfAlola->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerGuardianOfAlolaWazaDmgProc1);
    }
    return sHandlerTableGuardianOfAlola;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GenesisSupernova(MethodInfo *method) {
    if (sHandlerTableGenesisSupernova == nullptr) {
        sHandlerTableGenesisSupernova = CreateEventHandlerTable(1);
        sHandlerTableGenesisSupernova->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerGenesisSupernovaDamageprocEndHitReal);
    }
    return sHandlerTableGenesisSupernova;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SpliteredStormshards(MethodInfo *method) {
    if (sHandlerTableSplinteredStormshards == nullptr) {
        sHandlerTableSplinteredStormshards = CreateEventHandlerTable(1);
        sHandlerTableSplinteredStormshards->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerSplinteredStormshardsDamageprocEndHitReal);
    }
    return sHandlerTableSplinteredStormshards;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GlitzyGlow(MethodInfo *method) {
    if (sHandlerTableGlitzyGlow == nullptr) {
        sHandlerTableGlitzyGlow = CreateEventHandlerTable(1);
        sHandlerTableGlitzyGlow->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerGlitzyGlowDamageprocEndHitReal);
    }
    return sHandlerTableGlitzyGlow;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_BaddyBad(MethodInfo *method) {
    if (sHandlerTableBaddyBad == nullptr) {
        sHandlerTableBaddyBad = CreateEventHandlerTable(1);
        sHandlerTableBaddyBad->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerBaddyBadDamageprocEndHitReal);
    }
    return sHandlerTableBaddyBad;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_FreezyFrost(MethodInfo *method) {
    if (sHandlerTableFreezyFrost == nullptr) {
        sHandlerTableFreezyFrost = CreateEventHandlerTable(1);
        sHandlerTableFreezyFrost->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerFreezyFrostDamageprocEndHitReal);
    }
    return sHandlerTableFreezyFrost;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SparklySwirl(MethodInfo *method) {
    if (sHandlerTableSparklySwirl == nullptr) {
        sHandlerTableSparklySwirl = CreateEventHandlerTable(1);
        sHandlerTableSparklySwirl->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerSparklySwirlDamageprocEndHitReal);
    }
    return sHandlerTableSparklySwirl;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MaxMove(MethodInfo *method) {
    if (sHandlerTableMaxMove == nullptr) {
        sHandlerTableMaxMove = CreateEventHandlerTable(4);
        sHandlerTableMaxMove->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerMaxMoveDamageprocEndHitReal);
        sHandlerTableMaxMove->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_POWER_BASE, (Il2CppMethodPointer) &HandlerMaxMoveWazaPowerBase);
        sHandlerTableMaxMove->m_Items[2] = CreateMoveEventHandler(EventID::WAZASEQ_START, (Il2CppMethodPointer) &HandlerMaxMoveWazaseqStart);
        sHandlerTableMaxMove->m_Items[3] = CreateMoveEventHandler(EventID::WAZASEQ_END, (Il2CppMethodPointer) &HandlerMaxMoveWazaseqEnd);
    }
    return sHandlerTableMaxMove;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_ExpandingForce(MethodInfo *method) {
    if (sHandlerTableExpandingForce == nullptr) {
        sHandlerTableExpandingForce = CreateEventHandlerTable(2);
        sHandlerTableExpandingForce->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_PARAM, (Il2CppMethodPointer) &HandlerExpandingForceWazaParam);
        sHandlerTableExpandingForce->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerExpandingForceWazaPower);
    }
    return sHandlerTableExpandingForce;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SteelRoller(MethodInfo *method) {
    if (sHandlerTableSteelRoller == nullptr) {
        sHandlerTableSteelRoller = CreateEventHandlerTable(2);
        sHandlerTableSteelRoller->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_CHECK_3RD, (Il2CppMethodPointer) &HandlerSteelRollerWazaExecuteCheck3rd);
        sHandlerTableSteelRoller->m_Items[1] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerSplinteredStormshardsDamageprocEndHitReal);
    }
    return sHandlerTableSteelRoller;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MeteorBeam(MethodInfo *method) {
    if (sHandlerTableMeteorBeam == nullptr) {
        sHandlerTableMeteorBeam = CreateEventHandlerTable(1);
        sHandlerTableMeteorBeam->m_Items[0] = CreateMoveEventHandler(EventID::TAME_START_FIXED, (Il2CppMethodPointer) &HandlerMeteorBeamTameStartFixed);
    }
    return sHandlerTableMeteorBeam;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_ShellSideArm(MethodInfo *method) {
    if (sHandlerTableShellSideArm == nullptr) {
        sHandlerTableShellSideArm = CreateEventHandlerTable(1);
        sHandlerTableShellSideArm->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_PARAM, (Il2CppMethodPointer) &HandlerShellSideArmWazaParam);
    }
    return sHandlerTableShellSideArm;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MistyExplosion(MethodInfo *method) {
    if (sHandlerTableMistyExplosion == nullptr) {
        sHandlerTableMistyExplosion = CreateEventHandlerTable(4);
        sHandlerTableMistyExplosion->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerMistyExplosionWazaPower);
        sHandlerTableMistyExplosion->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_DMG_DETERMINE, (Il2CppMethodPointer) &Waza::handler_Daibakuhatsu_DmgDetermine);
        sHandlerTableMistyExplosion->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_DONE, (Il2CppMethodPointer) &Waza::handler_Daibakuhatsu_ExeFix);
        sHandlerTableMistyExplosion->m_Items[3] = CreateMoveEventHandler(EventID::WAZA_EXE_START, (Il2CppMethodPointer) &Waza::handler_Daibakuhatsu_ExeStart);
    }
    return sHandlerTableMistyExplosion;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GrassyGlide(MethodInfo *method) {
    if (sHandlerTableGrassyGlide == nullptr) {
        sHandlerTableGrassyGlide = CreateEventHandlerTable(1);
        sHandlerTableGrassyGlide->m_Items[0] = CreateMoveEventHandler(EventID::GET_WAZA_PRI, (Il2CppMethodPointer) &HandlerGrassyGlideGetWazaPri);
    }
    return sHandlerTableGrassyGlide;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_RisingVoltage(MethodInfo *method) {
    if (sHandlerTableRisingVoltage == nullptr) {
        sHandlerTableRisingVoltage = CreateEventHandlerTable(1);
        sHandlerTableRisingVoltage->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerRisingVoltageWazaPower);
    }
    return sHandlerTableRisingVoltage;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_TerrainPulse(MethodInfo *method) {
    if (sHandlerTableTerrainPulse == nullptr) {
        sHandlerTableTerrainPulse = CreateEventHandlerTable(2);
        sHandlerTableTerrainPulse->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_PARAM, (Il2CppMethodPointer) &HandlerTerrainPulseWazaParam);
        sHandlerTableTerrainPulse->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerTerrainPulseWazaPower);
    }
    return sHandlerTableTerrainPulse;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_BurningJealousy(MethodInfo *method) {
    if (sHandlerTableBurningJealousy == nullptr) {
        sHandlerTableBurningJealousy = CreateEventHandlerTable(1);
        sHandlerTableBurningJealousy->m_Items[0] = CreateMoveEventHandler(EventID::ADD_SICK, (Il2CppMethodPointer) &HandlerBurningJealousyAddSick);
    }
    return sHandlerTableBurningJealousy;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_LashOut(MethodInfo *method) {
    if (sHandlerTableLashOut == nullptr) {
        sHandlerTableLashOut = CreateEventHandlerTable(1);
        sHandlerTableLashOut->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerLashOutWazaPower);
    }
    return sHandlerTableLashOut;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Poltergeist(MethodInfo *method) {
    if (sHandlerTablePoltergeist == nullptr) {
        sHandlerTablePoltergeist = CreateEventHandlerTable(1);
        sHandlerTablePoltergeist->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_CHECK_3RD, (Il2CppMethodPointer) &HandlerPoltergeistWazaExecuteCheck3rd);
    }
    return sHandlerTablePoltergeist;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_CorrosiveGas(MethodInfo *method) {
    if (sHandlerTableCorrosiveGas == nullptr) {
        sHandlerTableCorrosiveGas = CreateEventHandlerTable(1);
        sHandlerTableCorrosiveGas->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerCorrosiveGasUncategorizeWaza);
    }
    return sHandlerTableCorrosiveGas;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_TripleAxel(MethodInfo *method) {
    if (sHandlerTableTripleAxel == nullptr) {
        sHandlerTableTripleAxel = CreateEventHandlerTable(2);
        sHandlerTableTripleAxel->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER_BASE, (Il2CppMethodPointer) &HandlerTripleAxelWazaPowerBase);
        sHandlerTableTripleAxel->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_HIT_COUNT, (Il2CppMethodPointer) &Waza::handler_TripleKick_HitCount);
    }
    return sHandlerTableTripleAxel;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_JungleHealing(MethodInfo *method) {
    if (sHandlerTableJungleHealing == nullptr) {
        sHandlerTableJungleHealing = CreateEventHandlerTable(1);
        sHandlerTableJungleHealing->m_Items[0] = CreateMoveEventHandler(EventID::UNCATEGORIZE_WAZA, (Il2CppMethodPointer) &HandlerJungleHealingUncategorizeWaza);
    }
    return sHandlerTableJungleHealing;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_EerieSpell(MethodInfo *method) {
    if (sHandlerTableEerieSpell == nullptr) {
        sHandlerTableEerieSpell = CreateEventHandlerTable(1);
        sHandlerTableEerieSpell->m_Items[0] = CreateMoveEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerEerieSpellDamageprocEndHitReal);
    }
    return sHandlerTableEerieSpell;
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
constexpr uint32_t NEW_MOVES_COUNT = 88;

// Entry point. Replaces system_array_new.
void * Waza_system_array_new(void * typeInfo, uint32_t len) {
    auto * getFuncTable = (System::Array<Waza_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_MOVES_COUNT);
    uint32_t idx = len;

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
    SetMoveFunctionTable(getFuncTable, &idx, CHIP_AWAY, (Il2CppMethodPointer) &Waza::ADD_NasiKuzusi);
    SetMoveFunctionTable(getFuncTable, &idx, SKY_DROP, (Il2CppMethodPointer) &ADD_SkyDrop);
    SetMoveFunctionTable(getFuncTable, &idx, BESTOW, (Il2CppMethodPointer) &ADD_Bestow);
    SetMoveFunctionTable(getFuncTable, &idx, ROTOTILLER, (Il2CppMethodPointer) &ADD_Rototiller);
    SetMoveFunctionTable(getFuncTable, &idx, ION_DELUGE, (Il2CppMethodPointer) &ADD_IonDeluge);
    //40
    SetMoveFunctionTable(getFuncTable, &idx, SPOTLIGHT, (Il2CppMethodPointer) &ADD_Spotlight);
    SetMoveFunctionTable(getFuncTable, &idx, GUARDIAN_OF_ALOLA, (Il2CppMethodPointer) &ADD_GuardianOfAlola);
    SetMoveFunctionTable(getFuncTable, &idx, GENESIS_SUPERNOVA, (Il2CppMethodPointer) &ADD_GenesisSupernova);
    SetMoveFunctionTable(getFuncTable, &idx, LIGHT_THAT_BURNS_THE_SKY, (Il2CppMethodPointer) &Waza::ADD_PhotonGeyser);
    SetMoveFunctionTable(getFuncTable, &idx, SEARING_SUNRAZE_SMASH, (Il2CppMethodPointer) &Waza::ADD_MeteorDrive);
    SetMoveFunctionTable(getFuncTable, &idx, MENACING_MOONRAZE_MAELSTROM, (Il2CppMethodPointer) &Waza::ADD_MeteorDrive);
    SetMoveFunctionTable(getFuncTable, &idx, SPLINTERED_STORMSHARDS, (Il2CppMethodPointer) &ADD_SpliteredStormshards);
    SetMoveFunctionTable(getFuncTable, &idx, PIKA_PAPOW, (Il2CppMethodPointer) &ADD_Return);
    SetMoveFunctionTable(getFuncTable, &idx, GLITZY_GLOW, (Il2CppMethodPointer) &ADD_GlitzyGlow);
    SetMoveFunctionTable(getFuncTable, &idx, BADDY_BAD, (Il2CppMethodPointer) &ADD_BaddyBad);
    //50
    SetMoveFunctionTable(getFuncTable, &idx, FREEZY_FROST, (Il2CppMethodPointer) &ADD_FreezyFrost);
    SetMoveFunctionTable(getFuncTable, &idx, SPARKLY_SWIRL, (Il2CppMethodPointer) &ADD_SparklySwirl);
    SetMoveFunctionTable(getFuncTable, &idx, VEEVEE_VOLLEY, (Il2CppMethodPointer) &ADD_Return);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_FLARE, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_FLUTTERBY, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_LIGHTNING, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_STRIKE, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_KNUCKLE, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_PHANTASM, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_HAILSTORM, (Il2CppMethodPointer) &ADD_MaxMove);
    //60
    SetMoveFunctionTable(getFuncTable, &idx, MAX_OOZE, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_GEYSER, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_AIRSTREAM, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_STARFALL, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_WYRMWIND, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_MINDSTORM, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_ROCKFALL, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_QUAKE, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_DARKNESS, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, MAX_OVERGROWTH, (Il2CppMethodPointer) &ADD_MaxMove);
    //70
    SetMoveFunctionTable(getFuncTable, &idx, MAX_STEELSPIKE, (Il2CppMethodPointer) &ADD_MaxMove);
    SetMoveFunctionTable(getFuncTable, &idx, EXPANDING_FORCE, (Il2CppMethodPointer) &ADD_ExpandingForce);
    SetMoveFunctionTable(getFuncTable, &idx, STEEL_ROLLER, (Il2CppMethodPointer) &ADD_SteelRoller);
    SetMoveFunctionTable(getFuncTable, &idx, METEOR_BEAM, (Il2CppMethodPointer) &ADD_MeteorBeam);
    SetMoveFunctionTable(getFuncTable, &idx, SHELL_SIDE_ARM, (Il2CppMethodPointer) &ADD_ShellSideArm);
    SetMoveFunctionTable(getFuncTable, &idx, MISTY_EXPLOSION, (Il2CppMethodPointer) &ADD_MistyExplosion);
    SetMoveFunctionTable(getFuncTable, &idx, GRASSY_GLIDE, (Il2CppMethodPointer) &ADD_GrassyGlide);
    SetMoveFunctionTable(getFuncTable, &idx, RISING_VOLTAGE, (Il2CppMethodPointer) &ADD_RisingVoltage);
    SetMoveFunctionTable(getFuncTable, &idx, TERRAIN_PULSE, (Il2CppMethodPointer) &ADD_TerrainPulse);
    SetMoveFunctionTable(getFuncTable, &idx, BURNING_JEALOUSY, (Il2CppMethodPointer) &ADD_BurningJealousy);
    //80
    SetMoveFunctionTable(getFuncTable, &idx, LASH_OUT, (Il2CppMethodPointer) &ADD_LashOut);
    SetMoveFunctionTable(getFuncTable, &idx, POLTERGEIST, (Il2CppMethodPointer) &ADD_Poltergeist);
    SetMoveFunctionTable(getFuncTable, &idx, CORROSIVE_GAS, (Il2CppMethodPointer) &ADD_CorrosiveGas);
    SetMoveFunctionTable(getFuncTable, &idx, FLIP_TURN, (Il2CppMethodPointer) &Waza::ADD_TonboGaeri);
    SetMoveFunctionTable(getFuncTable, &idx, TRIPLE_AXEL, (Il2CppMethodPointer) &ADD_TripleAxel);
    SetMoveFunctionTable(getFuncTable, &idx, JUNGLE_HEALING, (Il2CppMethodPointer) &ADD_JungleHealing);
    SetMoveFunctionTable(getFuncTable, &idx, DRAGON_ENERGY, (Il2CppMethodPointer) &Waza::ADD_Funka);
    SetMoveFunctionTable(getFuncTable, &idx, EERIE_SPELL, (Il2CppMethodPointer) &ADD_EerieSpell);

    socket_log_initialize();
    socket_log_fmt("%i/%i move HandlerGetFunc delegates added", NEW_MOVES_COUNT, idx - len);

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
        isPursuitTarget = wazaID == U_TURN || wazaID == VOLT_SWITCH || wazaID == PARTING_SHOT || wazaID == FLIP_TURN;
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
        if (bpp->COUNTER_Get(BTL_POKEPARAM_Counter::COUNTER_MAMORU, nullptr) != 0)
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
// Grassy Glide
uint8_t Dpr_Battle_Logic_Section_CalcActionPriority_calcWazaPriority(Section_CalcActionPriority_o *__this, PokeAction_o **pokeAction, MethodInfo *method) {
    PokeAction_o *pa = *pokeAction;
    int32_t category = pa->fields.actionCategory;
    if (category == 7) {
        uint8_t clientID = pa->fields.clientID;
        return __this->fields.super.m_pBattleEnv->fields.m_gRightsManager->GetGRights(__this->
        fields.super.m_pMainModule->GetClientSide(clientID, nullptr), nullptr)->
        GetClientOrder(clientID, nullptr);
    }
    if (category == 5)
        return 7;
    if (category == 1) {
        ServerCommandPutter_o *scp = __this->fields.super.m_pServerCmdPutter;
        BTL_POKEPARAM_o *bpp = pa->fields.bpp;
        uint8_t pokeID = bpp->GetID(nullptr);
        uint16_t wazaID = pa->fields.actionParam_Fight->fields.waza;
        scp->AddWazaHandler(pokeID, wazaID, ActPri::ToHandlerPri(pa->
        fields.priority, nullptr), nullptr);
        uint8_t priority = __this->fields.super.m_pEventLauncher->Event_GetWazaPriority(PokeAction::GetWazaID(
                pa, nullptr), bpp, nullptr);
        scp->RemoveWazaHandler(pokeID, wazaID, nullptr);
        return priority;
    }
    return 0;
}
int8_t * GetRankType(BTL_POKEPARAM_o *bpp, int32_t rankType) {
    BTL_POKEPARAM_VARIABLE_PARAM_o *bppvp = bpp->fields.m_varyParam;
    switch(rankType) {
        case 1: return &bppvp->fields.attack;
        case 2: return &bppvp->fields.defence;
        case 3: return &bppvp->fields.sp_attack;
        case 4: return &bppvp->fields.sp_defence;
        case 5: return &bppvp->fields.agility;
        case 6: return &bppvp->fields.hit;
        case 7: return &bppvp->fields.avoid;
        default: return nullptr;
    }
}
// Burning Jealousy
uint8_t Dpr_Battle_Logic_BTL_POKEPARAM_RankUp(BTL_POKEPARAM_o *__this, int32_t rankType, uint8_t volume, MethodInfo *method) {
    int8_t *rank = GetRankType(__this, rankType);
    if (rank == nullptr) return 0;
    if (*rank >= 12) return 0;
    if (*rank + volume > 12)
        volume = 12 - *rank;
    *rank = (int8_t)(*rank + volume);
    __this->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_RANK_UP, nullptr);
    return volume;
}
// Lash Out
uint8_t Dpr_Battle_Logic_BTL_POKEPARAM_RankDown(BTL_POKEPARAM_o *__this, int32_t rankType, uint8_t volume, MethodInfo *method) {
    int8_t *rank = GetRankType(__this, rankType);
    if (rank == nullptr) return 0;
    if (*rank <= 0) return 0;
    if (*rank < volume)
        volume = *rank;
    *rank = (int8_t)(*rank - volume);
    __this->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_RANK_DOWN, nullptr);
    return volume;
}
// Gigaton Hammer
bool SetupBTLV_STRPARAM(BTLV_STRPARAM_o *strParam, uint16_t strID, uint8_t strType, const int32_t args[], uint64_t argCnt) {
    if (strParam == nullptr) return true;
    strParam->fields.strType = strType;
    strParam->fields.strID = strID;
    strParam->fields.wait = 0;
    System_Int32_array *oldArgs = strParam->fields.args;
    for (uint64_t i = 0; i < oldArgs->max_length; ++i)
        oldArgs->m_Items[i] = 0;
    if (oldArgs->max_length < argCnt)
        argCnt = oldArgs->max_length;
    strParam->fields.argCnt = argCnt;
    for (uint64_t i = 0; i < argCnt; ++i)
        oldArgs->m_Items[i] = args[i];
    return true;
}
bool Dpr_Battle_Logic_BTL_CLIENT_is_unselectable_waza(BTL_CLIENT_o *bc, BTL_POKEPARAM_o *bpp, int32_t waza, BTLV_STRPARAM_o *strParam, MethodInfo *method) {
    system_load_typeinfo((void *) 0x1ebc);
    if (waza == STRUGGLE) return false;
    if (!WAZADATA::IsValid(waza, nullptr)) {
        int32_t args[] = {};
        return SetupBTLV_STRPARAM(strParam, 0x1fc, 1, args, sizeof(args) / sizeof(*args));
    }
    FieldStatus_o **fldSim = &bc->fields.m_fldSim;
    uint16_t effItem = bpp->GetItemEffective(fldSim, nullptr);
    if (effItem != NULL_ITEM) {
        if (bpp->CheckSick(0x1c, nullptr) && !bpp->IsGMode(nullptr) &&
        !GWaza::IsGWaza(waza, nullptr) && Tables::IsKodawariItem(effItem, nullptr)) {
            BTL_SICKCONT_o cont = bpp->GetSickCont(0x1c, nullptr);
            uint16_t lockMove = SICKCONT::GetParam(&cont, nullptr);
            if (lockMove != waza && bpp->WAZA_IsUsable(lockMove, nullptr)) {
                int32_t args[] = {effItem, lockMove };
                return SetupBTLV_STRPARAM(strParam, 0x71, 1, args, sizeof(args) / sizeof(*args));
            }
        }
        if (effItem == 0x280 && !WAZADATA::IsDamage(waza, nullptr)) {
            int32_t args[] = { 0x280 };
            return SetupBTLV_STRPARAM(strParam, 0x72, 1, args, sizeof(args) / sizeof(*args));
        }
    }
    if (bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_TOKUSEI_EFFECTIVE, nullptr) == 0xff &&
    bpp->CheckSick(0x1c, nullptr) && !bpp->IsGMode(nullptr) &&
    !GWaza::IsGWaza(waza, nullptr)) {
        BTL_SICKCONT_o cont = bpp->GetSickCont(0x1c, nullptr);
        uint16_t lockMove = SICKCONT::GetParam(&cont, nullptr);
        if (lockMove != waza && bpp->WAZA_IsUsable(lockMove, nullptr)) {
            int32_t args[] = { bpp->GetID(nullptr), lockMove };
            return SetupBTLV_STRPARAM(strParam, 0x73, 1, args, sizeof(args) / sizeof(*args));
        }
    }
    if (bpp->CheckSick(0x17, nullptr)) {
        BTL_SICKCONT_o cont = bpp->GetSickCont(0x17, nullptr);
        uint16_t lockMove = SICKCONT::GetParam(&cont, nullptr);
        if (lockMove != waza && !GWaza::IsGWaza(waza, nullptr)) {
            int32_t args[] = { bpp->GetID(nullptr), lockMove };
            return SetupBTLV_STRPARAM(strParam, 0x73, 1, args, sizeof(args) / sizeof(*args));
        }
    }
    if (bpp->CheckSick(0xb, nullptr) && !WAZADATA::IsDamage(waza, nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr), waza };
        return SetupBTLV_STRPARAM(strParam, 0x302, 2, args, sizeof(args) / sizeof(*args));
    }
    if (bpp->CheckSick(0xc, nullptr) && bpp->fields.m_prevSelectWazaID == waza &&
    !bpp->IsGMode(nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr), waza };
        return SetupBTLV_STRPARAM(strParam, 0x30e, 2, args, sizeof(args) / sizeof(*args));
    }
    if (bpp->CheckSick(0xd, nullptr) && bpp->GetSickParam(0xd, nullptr) == waza  &&
         !GWaza::IsGWaza(waza, nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr), waza };
        return SetupBTLV_STRPARAM(strParam, 0x322, 2, args, sizeof(args) / sizeof(*args));
    }
    if (bpp->CheckSick(0xf, nullptr) && WAZADATA::GetFlag(waza, 0xc, nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr), waza };
        return SetupBTLV_STRPARAM(strParam, 0x4b4, 2, args, sizeof(args) / sizeof(*args));
    }
    if ((*fldSim)->CheckEffect(3, nullptr) && !bpp->IsGMode(nullptr) &&
        bc->fields.m_fldSim->CheckFuin(&bc->fields.m_mainModule,
                                       bc->fields.m_pBattleEnv->fields.m_pokecon, bpp, waza,
                                       nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr), waza };
        return SetupBTLV_STRPARAM(strParam, 0x31a, 2, args, sizeof(args) / sizeof(*args));
    }
    if ((*fldSim)->CheckEffect(2, nullptr) && !bpp->IsGMode(nullptr) &&
        WAZADATA::GetFlag(waza, 9, nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr), waza };
        return SetupBTLV_STRPARAM(strParam, 0x5c0, 2, args, sizeof(args) / sizeof(*args));
    }
    if (waza == STUFF_CHEEKS && !ItemData::IsNuts(bpp->GetItem(nullptr), nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr) };
        return SetupBTLV_STRPARAM(strParam, 0x199, 1, args, sizeof(args) / sizeof(*args));
    }
    if (waza == BELCH && !bpp->PERMFLAG_Get(0, nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr) };
        return SetupBTLV_STRPARAM(strParam, 0x648, 2, args, sizeof(args) / sizeof(*args));
    }
    if (bc->fields.m_mainModule->IsSkyBattle(nullptr) && WAZADATA::GetFlag(waza, 0xe, nullptr)) {
        int32_t args[] = {};
        return SetupBTLV_STRPARAM(strParam, 0x110, 1, args, sizeof(args) / sizeof(*args));
    }
    if (bpp->CheckSick(0x18, nullptr) && !bpp->IsGMode(nullptr) &&
    WAZADATA::GetFlag(waza, 8, nullptr)) {
        int32_t args[] = { bpp->GetID(nullptr) };
        return SetupBTLV_STRPARAM(strParam, 0x744, 2, args, sizeof(args) / sizeof(*args));
    }
    if (waza == GIGATON_HAMMER && bpp->fields.m_prevSelectWazaID == waza)
        return true;
    return false;
}
