#include "util.hpp"
#include "il2cpp-api.h"
#include "PlayerWork.hpp"
#include "logger.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/DamageCause.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/RankEffectCause.hpp"
#include "Dpr/Battle/Logic/SickCause.hpp"
#include "Pml/WazaData/WazaSick.hpp"
#include "Dpr/Battle/Logic/SICKCONT.hpp"

using namespace Dpr::Battle::Logic;
using namespace Pml::WazaData;

// ItemIDs
constexpr uint32_t FLAME_PLATE = 298;
constexpr uint32_t SPLASH_PLATE = 299;
constexpr uint32_t ZAP_PLATE = 300;
constexpr uint32_t MEADOW_PLATE = 301;
constexpr uint32_t ICICLE_PLATE = 302;
constexpr uint32_t FIST_PLATE = 303;
constexpr uint32_t TOXIC_PLATE = 304;
constexpr uint32_t EARTH_PLATE = 305;
constexpr uint32_t SKY_PLATE = 306;
constexpr uint32_t MIND_PLATE = 307;
constexpr uint32_t INSECT_PLATE = 308;
constexpr uint32_t STONE_PLATE = 309;
constexpr uint32_t SPOOKY_PLATE = 310;
constexpr uint32_t DRACO_PLATE = 311;
constexpr uint32_t DREAD_PLATE = 312;
constexpr uint32_t IRON_PLATE = 313;
constexpr uint32_t PIXIE_PLATE = 644;
constexpr uint32_t FIRIUM_Z = 777;
constexpr uint32_t WATERIUM_Z = 778;
constexpr uint32_t ELECTRIUM_Z = 779;
constexpr uint32_t GRASSIUM_Z = 780;
constexpr uint32_t ICIUM_Z = 781;
constexpr uint32_t FIGHTINIUM_Z = 782;
constexpr uint32_t POISONIUM_Z = 783;
constexpr uint32_t GROUNDIUM_Z = 784;
constexpr uint32_t FLYINIUM_Z = 785;
constexpr uint32_t PSYCHIUM_Z = 786;
constexpr uint32_t BUGINIUM_Z = 787;
constexpr uint32_t ROCKIUM_Z = 788;
constexpr uint32_t GHOSTIUM_Z = 789;
constexpr uint32_t DRAGONIUM_Z = 790;
constexpr uint32_t DARKINIUM_Z = 791;
constexpr uint32_t STEELIUM_Z = 792;
constexpr uint32_t FAIRIUM_Z = 793;
constexpr uint32_t FIGHTING_MEMORY = 904;
constexpr uint32_t FLYING_MEMORY = 905;
constexpr uint32_t POISON_MEMORY = 906;
constexpr uint32_t GROUND_MEMORY = 907;
constexpr uint32_t ROCK_MEMORY = 908;
constexpr uint32_t BUG_MEMORY = 909;
constexpr uint32_t GHOST_MEMORY = 910;
constexpr uint32_t STEEL_MEMORY = 911;
constexpr uint32_t FIRE_MEMORY = 912;
constexpr uint32_t WATER_MEMORY = 913;
constexpr uint32_t GRASS_MEMORY = 914;
constexpr uint32_t ELECTRIC_MEMORY = 915;
constexpr uint32_t PSYCHIC_MEMORY = 916;
constexpr uint32_t ICE_MEMORY = 917;
constexpr uint32_t DRAGON_MEMORY = 918;
constexpr uint32_t DARK_MEMORY = 919;
constexpr uint32_t FAIRY_MEMORY = 920;

// TypeIDs
constexpr uint32_t NORMAL = 0;
constexpr uint32_t FIGHTING = 1;
constexpr uint32_t FLYING = 2;
constexpr uint32_t POISON = 3;
constexpr uint32_t GROUND = 4;
constexpr uint32_t ROCK = 5;
constexpr uint32_t BUG = 6;
constexpr uint32_t GHOST = 7;
constexpr uint32_t STEEL = 8;
constexpr uint32_t FIRE = 9;
constexpr uint32_t WATER = 10;
constexpr uint32_t GRASS = 11;
constexpr uint32_t ELECTRIC = 12;
constexpr uint32_t PSYCHIC = 13;
constexpr uint32_t ICE = 14;
constexpr uint32_t DRAGON = 15;
constexpr uint32_t DARK = 16;
constexpr uint32_t FAIRY = 17;

void system_load_typeinfo(void * typeInfo)
{
  _system_load_typeinfo(typeInfo);
}

void system_array_init(void *array) {
    _system_array_init(array);
}

void * system_array_new(void * typeInfo, uint32_t len)
{
  void * array = _system_array_new(typeInfo, len);
  _system_array_init(array);
  return array;
}

void EnsureTypeInfoLoaded(bool *datBool, uint64_t datPtr) {
    if (*datBool) return;
    system_load_typeinfo((void *)datPtr);
    *datBool = true;
}

void EnsureClassInit(void *typeInfo) {
    auto *c = (Il2CppClass *)typeInfo;
    if ((c->_2.bitflags2 >> 1 & 1) != 0 && c->_2.cctor_finished == 0)
        il2cpp_runtime_class_init(typeInfo);
}

MethodInfo * copyMethodInfo(MethodInfo * src, Il2CppMethodPointer methodPointer)
{
  auto * dst = (MethodInfo *) malloc(sizeof(MethodInfo));
  memcpy(dst, src, sizeof(MethodInfo));

  if (methodPointer != nullptr)
  {
    dst->methodPointer = methodPointer;
  }

  return dst;
}


uint32_t GetBadgeCount()
{
  bool bVar1 = PlayerWork::GetSytemFlag(0x81, (MethodInfo *)nullptr);
  bool bVar2 = PlayerWork::GetSytemFlag(0x7c, (MethodInfo *)nullptr);
  bool bVar3 = PlayerWork::GetSytemFlag(0x7d, (MethodInfo *)nullptr);
  bool bVar4 = PlayerWork::GetSytemFlag(0x80, (MethodInfo *)nullptr);
  bool bVar5 = PlayerWork::GetSytemFlag(0x7f, (MethodInfo *)nullptr);
  bool bVar6 = PlayerWork::GetSytemFlag(0x7e, (MethodInfo *)nullptr);
  bool bVar7 = PlayerWork::GetSytemFlag(0x83, (MethodInfo *)nullptr);
  bool bVar8 = PlayerWork::GetSytemFlag(0x82, (MethodInfo *)nullptr);
  return (bVar2 & 1) + (bVar1 & 1) + (bVar3 & 1) + (bVar4 & 1) + (bVar5 & 1) + (bVar6 & 1) +
         (bVar7 & 1) + (bVar8 & 1);
}

uint8_t MultitypeType(uint32_t itemNo) {
    switch (itemNo) {
        case FIST_PLATE:
        case FIGHTINIUM_Z:
            return FIGHTING;
        case SKY_PLATE:
        case FLYINIUM_Z:
            return FLYING;
        case TOXIC_PLATE:
        case POISONIUM_Z:
            return POISON;
        case EARTH_PLATE:
        case GROUNDIUM_Z:
            return GROUND;
        case STONE_PLATE:
        case ROCKIUM_Z:
            return ROCK;
        case INSECT_PLATE:
        case BUGINIUM_Z:
            return BUG;
        case SPOOKY_PLATE:
        case GHOSTIUM_Z:
            return GHOST;
        case IRON_PLATE:
        case STEELIUM_Z:
            return STEEL;
        case FLAME_PLATE:
        case FIRIUM_Z:
            return FIRE;
        case SPLASH_PLATE:
        case WATERIUM_Z:
            return WATER;
        case MEADOW_PLATE:
        case GRASSIUM_Z:
            return GRASS;
        case ZAP_PLATE:
        case ELECTRIUM_Z:
            return ELECTRIC;
        case MIND_PLATE:
        case PSYCHIUM_Z:
            return PSYCHIC;
        case ICICLE_PLATE:
        case ICIUM_Z:
            return ICE;
        case DRACO_PLATE:
        case DRAGONIUM_Z:
            return DRAGON;
        case DREAD_PLATE:
        case DARKINIUM_Z:
            return DARK;
        case PIXIE_PLATE:
        case FAIRIUM_Z:
            return FAIRY;
        default:
            return NORMAL;
    }
}
uint8_t RKSSystemType(uint32_t itemNo) {
    switch (itemNo) {
        case FIGHTING_MEMORY: return FIGHTING;
        case FLYING_MEMORY: return FLYING;
        case POISON_MEMORY: return POISON;
        case GROUND_MEMORY: return GROUND;
        case ROCK_MEMORY: return ROCK;
        case BUG_MEMORY: return BUG;
        case GHOST_MEMORY: return GHOST;
        case STEEL_MEMORY: return STEEL;
        case FIRE_MEMORY: return FIRE;
        case WATER_MEMORY: return WATER;
        case GRASS_MEMORY: return GRASS;
        case ELECTRIC_MEMORY: return ELECTRIC;
        case PSYCHIC_MEMORY: return PSYCHIC;
        case ICE_MEMORY: return ICE;
        case DRAGON_MEMORY: return DRAGON;
        case DARK_MEMORY: return DARK;
        case FAIRY_MEMORY: return FAIRY;
        default: return NORMAL;
    }
}

System::Array<EventFactor_EventHandlerTable_o *> * CreateEventHandlerTable(uint32_t size) {
    auto *array = (System::Array<EventFactor_EventHandlerTable_o *> *) malloc(32 + 8 * size);
    array->max_length = size;
    for (int i = 0; i < size; ++i)
        array->m_Items[i] = nullptr;
    return array;
}
Dpr::Battle::Logic::EventFactor_EventHandlerTable_o * CreateEventHandler(uint16_t eventID, MethodInfo * src, Il2CppMethodPointer methodPointer)
{
    MethodInfo * method = copyMethodInfo(src, methodPointer);
    auto * evtHandlerTable = (Dpr::Battle::Logic::EventFactor_EventHandlerTable_o *) malloc(sizeof(Dpr::Battle::Logic::EventFactor_EventHandlerTable_o));
    auto * evtHandler = (Dpr::Battle::Logic::EventFactor_EventHandler_o *) malloc(sizeof(Dpr::Battle::Logic::EventFactor_EventHandler_o));
    evtHandler->ctor((intptr_t) methodPointer, method);
    evtHandler->fields.super.delegates = nullptr;
    evtHandlerTable->fields.eventID = eventID;
    evtHandlerTable->fields.eventHandler = evtHandler;
    return evtHandlerTable;
}
uint8_t HighestMultiple(uint8_t max, uint8_t factor) {
    uint8_t factor2 = max / factor;
    return factor * factor2;
}
bool HandlerAddFieldEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t effect, uint8_t turns) {
    auto *desc = (Section_FieldEffect_Add_Description_o *)
            il2cpp_object_new(Section_FieldEffect_Add_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.effect = effect;
    desc->fields.cont = SICKCONT::MakeTurn(pokeID, turns, nullptr);
    return Common::AddFieldEffect(args, &desc, nullptr);
}
void HandlerAddPosEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    system_load_typeinfo((void *)0xa909);
    auto *desc = (Section_FromEvent_PosEffect_Add_Description_o *)
            il2cpp_object_new(Section_FromEvent_PosEffect_Add_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.userPokeID = pokeID;
    desc->fields.pos = Common::PokeIDtoPokePos(args, &pokeID, nullptr);
    desc->fields.effect = 5;
    Common::AddPosEffect(args, &desc, nullptr);
}
void HandlerAddSick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t targetPokeID, int32_t sickID,
                    int64_t sickCont) {
    system_load_typeinfo((void *)0xa9aa);
    auto *addSickDesc = (Section_AddSick_Description_o *)
            il2cpp_object_new(Section_AddSick_Description_TypeInfo);
    addSickDesc->ctor(nullptr);
    addSickDesc->fields.pokeID = pokeID;
    addSickDesc->fields.targetPokeID = targetPokeID;
    addSickDesc->fields.sickID = sickID;
    addSickDesc->fields.sickCont.fields.raw = sickCont;
    addSickDesc->fields.sickCause = SickCause::OTHER;
    addSickDesc->fields.isDisplayTokuseiWindow = false;
    addSickDesc->fields.isFailResultDisplay = false;
    Common::AddSick(args, &addSickDesc, nullptr);
}
bool HandlerAddSideEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t effect, int32_t side, BTL_SICKCONT_o cont) {
    system_load_typeinfo((void *)0xa8ef);
    auto *desc = (Section_SideEffect_Add_Description_o *)
            il2cpp_object_new(Section_SideEffect_Add_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.effect = effect;
    desc->fields.side = side;
    desc->fields.cont = cont;
    desc->fields.isReplaceSuccessMessageArgs0ByExpandSide = true;
    return Common::AddSideEffect(args, &desc, nullptr);
}
void HandlerCureSick(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, int32_t sickID, uint8_t targetPokeID) {
    system_load_typeinfo((void *)0x893f);
    auto desc = (Section_CureSick_Description_o *)
            il2cpp_object_new(Section_CureSick_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = causePokeID;
    desc->fields.sick = sickID;
    desc->fields.targetPokeID->m_Items[0] = targetPokeID;
    desc->fields.targetPokeCount = 1;
    desc->fields.isDisplayTokuseiWindow = false;
    desc->fields.isStandardMessageDisable = false;
    Common::CureSick(args,&desc,nullptr);
}
void HandlerDamage(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID, uint16_t damage,
                   bool disableDeadProcess, bool displayAbility) {
    system_load_typeinfo((void *)0x8a36);
    auto *desc = (Section_FromEvent_Damage_Description_o *)
            il2cpp_object_new(Section_FromEvent_Damage_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = causePokeID;
    desc->fields.targetPokeID = targetPokeID;
    desc->fields.damage = damage;
    desc->fields.damageCause = DamageCause::OTHER;
    desc->fields.damageCausePokeID = causePokeID;
    desc->fields.disableDeadProcess = disableDeadProcess;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    Common::Damage(args, &desc, nullptr);
}
void HandlerFormChange(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t nextForm, bool persistOnSwitch,
                       bool displayAbility, bool animationEnabled) {
    system_load_typeinfo((void *)0x88fe);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    if (bpp->fields.m_formNo == nextForm) return;
    auto * desc = (Section_FromEvent_FormChange_Description_o *)
            il2cpp_object_new(Section_FromEvent_FormChange_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.formNo = nextForm;
    desc->fields.isDontResetFormByOut = persistOnSwitch;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    desc->fields.isDisplayChangeEffect = animationEnabled;
    //desc->fields.successMessage->Setup(BtlStrType::BTL_STRTYPE_SET, 304, nullptr);
    //desc->fields.successMessage->AddArg(pokeID, nullptr);
    Common::FormChange(args, &desc, nullptr);
}
void HandlerMessage(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool displayAbility) {
    system_load_typeinfo((void *)0x58d8);
    auto *desc = (Section_FromEvent_Message::Description_o *)
            il2cpp_object_new(Section_FromEvent_Message::Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    Common::Message(args, &desc, nullptr);
}
void HandlerRankEffect(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID,
                       int32_t rankType, int8_t rankVolume, bool displayAbility, bool ignoreSubstitute,
                       bool messageOnFail, bool byWazaEffect) {
    system_load_typeinfo((void *)0x89b2);
    auto *rankEffectDesc = (Section_FromEvent_RankEffect_Description_o *)
            il2cpp_object_new(Section_FromEvent_RankEffect_Description_TypeInfo);
    rankEffectDesc->ctor(nullptr);
    rankEffectDesc->fields.pokeID = causePokeID;
    rankEffectDesc->fields.targetPokeCount = 1;
    rankEffectDesc->fields.targetPokeID->m_Items[0] = targetPokeID;
    rankEffectDesc->fields.rankType = rankType;
    rankEffectDesc->fields.rankVolume = rankVolume;
    rankEffectDesc->fields.cause = RankEffectCause::OTHER;
    rankEffectDesc->fields.isDisplayTokuseiWindow = displayAbility;
    rankEffectDesc->fields.isMigawariThrew = ignoreSubstitute;
    rankEffectDesc->fields.isSpFailMessageDisplay = messageOnFail;
    rankEffectDesc->fields.byWazaEffect = byWazaEffect;
    Common::RankEffect(args,&rankEffectDesc, nullptr);
}
void HandlerRankReset(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    system_load_typeinfo((void *)0xa911);
    auto *desc = (Section_FromEvent_RankReset_Description_o *)
            il2cpp_object_new(Section_FromEvent_RankReset_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeCount = 1;
    desc->fields.pokeID->m_Items[0] = pokeID;
    Common::RankReset(args, &desc, nullptr);
}
void HandlerRankResetAll(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    system_load_typeinfo((void *)0xa9b3);
    auto *desc = (Section_FromEvent_RankReset_Description_o *)
            il2cpp_object_new(Section_FromEvent_RankReset_Description_TypeInfo);
    desc->ctor(nullptr);
    auto *exPos = (ExPokePos_o *)il2cpp_object_new(ExPokePos_TypeInfo);
    exPos->ctor(ExPosType::FULL_ALL, Common::GetExistFrontPokePos(args, pokeID, nullptr), nullptr);
    desc->fields.pokeCount = Common::ExpandExistPokeID(args, &exPos, desc->fields.pokeID, nullptr);
    Common::RankReset(args, &desc, nullptr);
}
void HandlerShrink(EventFactor_EventHandlerArgs_o **args, uint8_t targetPokeID, uint8_t percentage) {
    system_load_typeinfo((void *)0x58b8);
    auto *desc = (Section_FromEvent_Shrink_Description_o *)
            il2cpp_object_new(Section_FromEvent_Shrink_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = targetPokeID;
    desc->fields.percentage = percentage;
    Common::Shrink(args, &desc, nullptr);
}
System_Int64_array *NewInt64Array(uint32_t len) {
    system_load_typeinfo((void *)0x270d);
    return (System_Int64_array *)system_array_new(System_Int64_array_TypeInfo, len);
}