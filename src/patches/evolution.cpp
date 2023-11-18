#include "il2cpp.hpp"
#include "il2cpp-api.h"
#include "logger.hpp"
#include "util.hpp"

#include "Audio/AudioManager.hpp"
#include "BattleConnector.hpp"
#include "Dpr/Battle/Logic/BattleProc.hpp"
#include "Dpr/Message/MessageManager.hpp"
#include "Dpr/Message/MessageWordSetHelper.hpp"
#include "Dpr/MsgWindow/MsgWindowManager.hpp"
#include "EntityManager.hpp"
#include "EvolveDemoTools.hpp"
#include "FieldManager.hpp"
#include "GameManager.hpp"
#include "PlayerWork.hpp"
#include "Pml/Personal/EvolveCond.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "Pml/PokePara/CoreParam.hpp"
#include "Pml/Personal/EvolveTableExtensions.hpp"
#include "ZoneWork.hpp"

using namespace Audio;
using namespace Dpr;
using namespace Dpr::Battle::Logic;
using namespace Dpr::Message;
using namespace Dpr::MsgWindow;
using namespace Dpr::UnderGround;
using namespace Pml::Personal;
using namespace Pml::PokePara;
using namespace poketool;
using namespace poketool::poke_memo;
using namespace SmartPoint::AssetAssistant;
using namespace SmartPoint::Components;
using namespace System;
using namespace UnityEngine;
using namespace XLSXContent;

// ItemIDs
constexpr uint16_t NULL_ITEM = 0;
constexpr uint16_t EVERSTONE = 229;

// DexIDs
constexpr uint16_t RAICHU = 26;
constexpr uint16_t SPEWPA = 665;
constexpr uint16_t VIVILLON = 666;
constexpr uint16_t COSMOEM = 790;
constexpr uint16_t SOLGALEO = 791;
constexpr uint16_t LUNALA = 792;
constexpr uint16_t MILCERY = 868;
constexpr uint16_t ALCREMIE = 869;

extern bool DAT_7104cbbb77;
PokeResult_o * GetPokeResult(PokeParty_o *party, CoreParam_o * cp) {
    EnsureTypeInfoInit(&DAT_7104cbbb77, 0x2243);
    if (BattleProc_TypeInfo->static_fields->setupParam == nullptr) return nullptr;
    if (BattleProc_TypeInfo->static_fields->setupParam->fields.pokeResult == nullptr) return nullptr;
    for (uint32_t i = 0; i < party->fields.m_memberCount; ++i)
        if ((CoreParam_o *)party->fields.m_member->m_Items[i] == cp)
            return BattleProc_TypeInfo->static_fields->setupParam->fields.pokeResult->m_Items[i];
    return nullptr;
}

bool IsSatisfyEvolveConditionEvent(EvolveTable_SheetEvolve_o *etse, PokeParty_o *party, CoreParam_o * cp, EvolveSituation_o *es, uint8_t routeIndex) {
    Accessor_o *a = cp->fields.m_accessor;
    PokeResult_o *pr = GetPokeResult(party, cp);
    uint8_t level;
    if (a->HaveCalcData(nullptr))
        level = a->GetLevel(nullptr);
    else
        level = cp->CalcLevel(nullptr);
    if (EvolveTableExtensions::GetEvolveEnableLevel(etse, routeIndex, nullptr) > level)
        return false;
    uint16_t param = EvolveTableExtensions::GetEvolutionParam(etse, routeIndex, nullptr);
    switch (EvolveTableExtensions::GetEvolutionCondition(etse, routeIndex, nullptr)) {
        case EvolveCond::CRITICAL_HIT:
            if (cp->GetHp(nullptr) > 0 && es->fields.criticalHitCount >= param)
                return true;
            return false;
        case EvolveCond::TOTAL_DAMAGE_RECIEVED:
            if (pr == nullptr) return true;
            if (pr->fields.totalDamageRecieved >= 49 && pr->fields.deadCount == 0 && es->fields.isUltraSpace)
                return true;
            return false;
        default: return false;
    }
}

extern bool DAT_7104cc00ac;
extern bool DAT_7104cc00eb;
bool CanEventEvolve(PokeParty_o *party, PokemonParam_o *pp, EvolveSituation_o *es) {
    EnsureTypeInfoInit(&DAT_7104cc00ac, 0x4721);
    EnsureTypeInfoInit(&DAT_7104cc00eb, 0x4724);
    EnsureClassInit(PersonalSystem_TypeInfo);
    auto *cp = (CoreParam_o *)pp;
    Accessor_o *a = pp->fields.super.m_accessor;
    if (a->IsSpecialGEnable(nullptr) || a->IsTamago(nullptr) || a->IsFuseiTamago(nullptr) || a->GetItemNo(nullptr) == EVERSTONE) return false;
    EvolveTable_SheetEvolve_o *etse = PersonalSystem::GetEvolutionTable(a->GetMonsNo(nullptr), a->GetFormNo(nullptr), nullptr);
    uint8_t routeCount = EvolveTableExtensions::GetEvolutionRouteNum(etse, nullptr);
    for (uint8_t i = 0; i < routeCount; ++i)
        if (IsSatisfyEvolveConditionEvent(etse, party, cp, es, i))
            return true;
    return false;
}

extern bool DAT_7104cbb2cc;
extern bool DAT_7104cc61bd;
void poketool_poketool_evolution_util_SetupEvolveSituation(EvolveSituation_o *pSituation, bool isDeviceTurnedOver,
                                                           int32_t weather, MethodInfo *method) {
    EnsureTypeInfoInit(&DAT_7104cc61bd, 0xad3e);
    EnsureTypeInfoInit(&DAT_7104cbb2cc, 0x6aee);
    EnsureClassInit(PlayerWork_TypeInfo);
    EnsureClassInit(GameManager_TypeInfo);
    if (weather == 0x14)
        weather = PlayerWork_TypeInfo->static_fields->_FieldWeather_k__BackingField;
    pSituation->fields.isMagneticField = false;
    pSituation->fields.isIceField = false;
    pSituation->fields.isMossField = false;
    int32_t zoneID = PlayerWork::get_zoneID(nullptr);
    pSituation->fields.isDeviceTurnedOver = true;
    pSituation->fields.isTurnRoundOnField = false;
    MYSTATUS_o *ms = PlayerWork::get_playerStatus(nullptr);
    OwnerInfo_o *oi = pSituation->fields.owner_info;
    oi->fields.trainerId = ms->fields.id;
    oi->fields.name = ms->fields.name;
    system_array_init(&oi->fields.name);
    oi->fields.sex = !ms->fields.sex;
    oi->fields.langID = ms->fields.region_code;
    poketool_evolution_util::SetupPlace(pSituation, nullptr);
    pSituation->fields.isSnowMountain = zoneID == 206 || zoneID == 207;
    pSituation->fields.isUltraSpace = ZoneWork::IsUnderGround(zoneID, nullptr);
    int32_t periodOfDay = GameManager::get_currentPeriodOfDay(nullptr);
    pSituation->fields.isMorningOrNoon = periodOfDay < 3;
    pSituation->fields.isEvening = periodOfDay == 2;
    pSituation->fields.isNight = periodOfDay == 3 || periodOfDay == 4;
    pSituation->fields.isRain = weather == 2 || weather == 3;
}

extern bool DAT_7104cbbb84;
extern bool DAT_7104cbbbcc;
extern bool DAT_7104cbbbcd;
extern bool DAT_7104cbb2b8;
extern bool DAT_7104cbb2b5;
extern String_o *StringLiteral_7099;
extern String_o *StringLiteral_7098;
extern String_o *StringLiteral_7097;
bool Dpr_Battle_Logic_BattleProc__FinalizeCoroutine_d__34_MoveNext(BattleProc__FinalizeCoroutine_d__34_o *__this,
                                                                   MethodInfo *method) {
    EnsureTypeInfoInit(&DAT_7104cbbb84, 0x9077);
    EnsureTypeInfoInit(&DAT_7104cbbbcc, 0x6b3f);
    EnsureTypeInfoInit(&DAT_7104cbbbcd, 0x6bdd);
    EnsureTypeInfoInit(&DAT_7104cbb2b8, 0x6b01);
    EnsureTypeInfoInit(&DAT_7104cbb2b5, 0x4979);
    EnsureTypeInfoInit(&DAT_7104cbb2cc, 0x6aee);
    EnsureClassInit(PlayerWork_TypeInfo);
    EnsureClassInit(EncountTools_TypeInfo);
    EnsureClassInit(BattleConnector_TypeInfo);
    EnsureClassInit(SingletonMonoBehaviour_AudioManager__TypeInfo);
    EnsureClassInit(FieldManager_TypeInfo);
    EnsureClassInit(UgFieldManager_TypeInfo);
    EnsureClassInit(SingletonMonoBehaviour_MessageManager__TypeInfo);
    EnsureClassInit(MessageWordSetHelper_TypeInfo);
    int32_t *state = &__this->fields.__1__state;
    if (0x6 < *state)
        return false;
    BattleProc_o *bp  = __this->fields.__4__this;
    MainModule_o *mm = bp->fields.mainModule;
    Il2CppObject **current = &__this->fields.__2__current;
    BATTLE_SETUP_PARAM_o *bsp = BattleProc_TypeInfo->static_fields->setupParam;
    auto *am = (AudioManager_o *)SingletonMonoBehaviour_object_::get_Instance(
            SingletonMonoBehaviour_AudioManager__get_Instance);
    switch(*state) {
        case 0x0: {
            *state = -0x1;
            Color_o value = Color::get_black(nullptr);
            Fader::set_fillColor(value, nullptr);
            *current = (Il2CppObject *)mm->LeavenOnErrorCoroutine(nullptr);
            system_array_init(current);
            *state = 0x1;
            return true;
        }
        case 0x1: {
            *state = -0x1;
            IEnumerator_o *outDispError = nullptr;
            EncountTools::OnPostBattle(bsp,
                                       PlayerWork::get_playerParty(nullptr),
                                       &__this->fields._evolveCheckTargetIndices_5__2, &outDispError, nullptr);
            if (outDispError == nullptr) break;
            *current = (Il2CppObject *)outDispError;
            system_array_init(current);
            *state = 2;
            return true;
        }
        case 0x2:
            *state = -0x1;
            break;
        case 0x3: {
            *state = -0x1;
            EncountTools::OnPostRegisterZukan(PlayerWork::get_capturedPokemon(nullptr),
                                              PlayerWork_TypeInfo->static_fields->
                                                      _capturedBallCountTvTopic_k__BackingField, nullptr);
            PlayerWork::set_capturedPokemon(nullptr, nullptr);
            PlayerWork_TypeInfo->static_fields->_capturedBallCountTvTopic_k__BackingField = 0x0;
            Fader::set_valid(true, nullptr);
            Fader::FadeOut(nullptr);
            int32_t nextState = 4;
            if (Fader::get_isBusy(nullptr)) {
                *current = nullptr;
                system_array_init(current);
            } else {
                *current = (Il2CppObject *)mm->FinalizeCoroutine(nullptr);
                system_array_init(current);
                nextState = 0x5;
            }
            *state = nextState;
            return true;
        }
        case 0x4: {
            *state = -0x1;
            int32_t nextState = 4;
            if (Fader::get_isBusy(nullptr)) {
                *current = nullptr;
                system_array_init(current);
            } else {
                *current = (Il2CppObject *)mm->FinalizeCoroutine(nullptr);
                system_array_init(current);
                nextState = 0x5;
            }
            *state = nextState;
            return true;
        }
        case 0x5: {
            *state = -0x1;
            BattleConnector::ReleasePrefetchAssetBundles(nullptr);
            if (!PlayerWork_TypeInfo->static_fields->_IsZenmetuFlag_k__BackingField) {
                BattleProc::StopBGM(nullptr, nullptr);
                bsp->Clear(nullptr);
                bp->fields.isFinalized = true;
                return false;
            }
            am->StopBgm(nullptr);
            if (ZoneWork::IsUnderGround(PlayerWork::get_zoneID(nullptr),nullptr)) {
                UgFieldManager_o *ugfm = UgFieldManager_TypeInfo->static_fields->Instance;
                auto *a = (Action_o *)il2cpp_object_new(Action_TypeInfo);
                a->ctor((Il2CppObject *)ugfm, UgFieldManager_CreateHyouta);
                FieldManager_TypeInfo->static_fields->_Instance_k__BackingField->add_OnZoneChangeEvent(a, nullptr);
                ugfm->CreateReturnPoint(nullptr);
                ugfm->fields.nowBaseModel = PlayerWork::get_ugSaveData(nullptr).fields.ugRecord.fields.myBase;
                system_array_init(&ugfm->fields.nowBaseModel.fields.ugStoneStatue);
            } else {
                auto *bpdc340 = (BattleProc___c__DisplayClass34_0_o *)
                        il2cpp_object_new(BattleProc___c__DisplayClass34_0_TypeInfo);
                __this->fields.__8__1 = bpdc340;
                system_array_init(&__this->fields.__8__1);
                String_o *labelName = StringLiteral_7099;
                if (PlayerWork::get_PlayerSaveData(nullptr).fields.worpPoint.fields.zenmetu.fields.zoneID != 0x1a9)
                    labelName = StringLiteral_7098;
                bpdc340->fields.talking = true;
                auto *mwp = (MsgWindowParam_o *)il2cpp_object_new(MsgWindowParam_TypeInfo);
                mwp->ctor(nullptr);
                auto *messageManager = (MessageManager_o *)SingletonMonoBehaviour_object_::get_Instance(
                        SingletonMonoBehaviour_MessageManager__get_Instance);
                mwp->fields.useMsgFile = messageManager->GetMsgFile(StringLiteral_7097,nullptr);
                system_array_init(&mwp->fields.useMsgFile);
                mwp->fields.labelName = labelName;
                system_array_init(&mwp->fields.labelName);
                auto *onFinishedCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
                onFinishedCloseWindow->ctor((Il2CppObject *)bpdc340,
                                            BattleProc___c__DisplayClass34_0__FinalizeCoroutine_b__0);
                mwp->fields.onFinishedCloseWindow = onFinishedCloseWindow;
                system_array_init(&mwp->fields.onFinishedCloseWindow);
                mwp->fields.sortingOrder = 0x4001;
                mwp->fields.inputCloseEnabled = true;
                MessageWordSetHelper::SetPlayerNickNameWord(0x0, nullptr);
                MsgWindowManager::OpenMsg(mwp, nullptr);
                if (bpdc340->fields.talking) {
                    *current = nullptr;
                    system_array_init(current);
                    *state = 0x6;
                    return true;
                }
                __this->fields.__8__1 = nullptr;
                system_array_init(&__this->fields.__8__1);
            }
            am->SetBgmEvent(0x642ccdc3, false, nullptr);
            BattleProc::StopBGM(nullptr, nullptr);
            bsp->Clear(nullptr);
            bp->fields.isFinalized = true;
            return false;
        }
        case 0x6: {
            *state = -0x1;
            if (__this->fields.__8__1->fields.talking) {
                *current = nullptr;
                system_array_init(current);
                *state = 0x6;
                return true;
            }
            __this->fields.__8__1 = nullptr;
            system_array_init(&__this->fields.__8__1);
            am->SetBgmEvent(0x642ccdc3, false, nullptr);
            BattleProc::StopBGM(nullptr, nullptr);
            bsp->Clear(nullptr);
            bp->fields.isFinalized = true;
            return false;
        }
    }
    List_EvolveDemoTools_Param__o *edtps = PlayerWork::get_evolveRequets(nullptr);
    edtps->Clear(nullptr);
    auto *es = (EvolveSituation_o *)il2cpp_object_new(EvolveSituation_TypeInfo);
    es->ctor(nullptr);
    poketool_poketool_evolution_util_SetupEvolveSituation(es, false, PlayerWork_TypeInfo->static_fields->
            _FieldWeather_k__BackingField, nullptr);
    PokeParty_o *pokeParty = PlayerWork::get_playerParty(nullptr);
    for (uint32_t i = 0; i < pokeParty->fields.m_memberCount; ++i) {
        PokemonParam_o *pokemonParam = pokeParty->GetMemberPointer(i, nullptr);
        uint16_t criticalCount = bsp->fields.pokeResult->m_Items[i]->fields.criticalCount;
        es->fields.criticalHitCount = criticalCount;
        int32_t nextMonsNo = 0;
        uint32_t evolutionRoot = 0;
        if ((((__this->fields._evolveCheckTargetIndices_5__2 & (0x1 << i)) == 0x0) ||
            !EvolveDemoTools::CanEvolve(&nextMonsNo, &evolutionRoot, pokeParty, pokemonParam, es, nullptr, 0x0,
                                        nullptr)) && !CanEventEvolve(pokeParty, pokemonParam, es)) continue;
        EvolveDemoTools_param_o evdtp = { .fields = { .party = pokeParty, .pp = pokemonParam,
                .criticalCount = criticalCount, .situation = es } };
        system_array_init(&evdtp.fields.party);
        system_array_init(&evdtp.fields.situation);
        system_array_init(&evdtp.fields.pp);
        edtps->Add(&evdtp, List_EvolveDemoTools_Param__Add);
    }
    if (edtps->fields._size == 0x0) {
        PokemonParam_o *pokemonParam = PlayerWork::get_capturedPokemon(nullptr);
        if (pokemonParam != nullptr) {
            poketool_poke_memo::SetFromCapture((CoreParam_o *)pokemonParam, PlayerWork::get_playerStatus(nullptr),
                                               PlayerWork::get_zoneID(nullptr), nullptr);
            *current = (Il2CppObject *)EvolveDemoTools::RegisterZukanCoroutine(pokemonParam, nullptr, nullptr);
            system_array_init(current);
            *state = 0x3;
            return true;
        }
    }
    Fader::set_valid(true, nullptr);
    Fader::FadeOut(nullptr);
    int32_t nextState = 4;
    if (Fader::get_isBusy(nullptr)) {
        *current = nullptr;
        system_array_init(current);
    } else {
        *current = (Il2CppObject *)mm->FinalizeCoroutine(nullptr);
        system_array_init(current);
        nextState = 0x5;
    }
    *state = nextState;
    return true;
}

int32_t Pml_PokePara_EvolveManager_GetEvolvedMonsNo_byLevelUp(EvolveManager_o *__this, CoreParam_o *poke,
                                                              PokeParty_o *party, EvolveSituation_o *situation,
                                                              uint32_t *root_num, MethodInfo *method) {
    EnsureTypeInfoInit(&DAT_7104cc00ac, 0x4721);
    EnsureClassInit(PersonalSystem_TypeInfo);
    Accessor_o *a = poke->fields.m_accessor;
    int32_t dexID = a->GetMonsNo(nullptr);
    if (a->IsSpecialGEnable(nullptr)) return dexID;
    if (a->IsTamago(nullptr)) return dexID;
    if (a->IsFuseiTamago(nullptr)) return dexID;
    if (a->GetItemNo(nullptr) == EVERSTONE) return dexID;
    EvolveTable_SheetEvolve_o *self = PersonalSystem::GetEvolutionTable(dexID,a->GetFormNo(nullptr),nullptr);
    uint8_t routeCount = EvolveTableExtensions::GetEvolutionRouteNum(self,nullptr);
    for (uint8_t i = 0; i < routeCount; ++i) {
        if (EvolveManager::IsSatisfyEvolveConditionLevelUp(nullptr, poke, party, situation, self, i, nullptr) ||
                IsSatisfyEvolveConditionEvent(self, party, poke, situation, i)) {
            *root_num = i;
            return EvolveTableExtensions::GetEvolvedMonsNo(self,i,nullptr);
        }
    }
    return dexID;
}

extern bool DAT_7104cc0071;
extern bool DAT_7104cbf462;
void Pml_PokePara_CoreParam_Evolve(CoreParam_o *__this, int32_t nextMonsno, uint32_t routeIndex, MethodInfo *method) {
    EnsureTypeInfoInit(&DAT_7104cc0071, 0x319b);
    EnsureTypeInfoInit(&DAT_7104cc61bd, 0xad3e);
    EnsureTypeInfoInit(&DAT_7104cbb2cc, 0x6aee);
    EnsureTypeInfoInit(&DAT_7104cbf462, 0x3f9a);
    EnsureClassInit(PersonalSystem_TypeInfo);
    EnsureClassInit(PlayerWork_TypeInfo);
    EnsureClassInit(GameManager_TypeInfo);
    Accessor_o *a = __this->fields.m_accessor;
    uint16_t dexID = a->GetMonsNo(nullptr);
    uint16_t formID = a->GetFormNo(nullptr);
    PersonalSystem::LoadEvolutionTable(dexID, formID, nullptr);
    if (PersonalSystem::IsEvolvedFormNoSpecified(routeIndex, nullptr))
        formID = PersonalSystem::GetEvolvedFormNo(routeIndex, nullptr);
    uint32_t trainerID = PlayerWork::get_playerStatus(nullptr)->fields.id;
    if (dexID == SPEWPA && nextMonsno == VIVILLON)
        formID = trainerID % 18;
    if (dexID == COSMOEM && (nextMonsno == SOLGALEO || nextMonsno == LUNALA))
        nextMonsno = (int32_t)(SOLGALEO + (trainerID >> 1) % 2);
    if (dexID == MILCERY && nextMonsno == ALCREMIE) {
        float yaw = EntityManager::get_activeFieldPlayer(nullptr)->fields.super.super.super.yawAngle;
        int32_t periodOfDay = GameManager::get_currentPeriodOfDay(nullptr);
        uint8_t group;
        bool north = yaw >= 135 && yaw < 225;
        bool west = yaw >= 225 && yaw < 315;
        bool south = yaw >= 315 || yaw < 45;
        bool east = yaw >= 45 && yaw < 135;
        bool day = periodOfDay < 2;
        bool night = periodOfDay > 2;
        if (south && day) group = 0;
        else if (east && day) group = 1;
        else if (south && night) group = 2;
        else if (north && night) group = 3;
        else if (west && night) group = 4;
        else if (east && night) group = 5;
        else if (north && day) group = 6;
        else if (west && day) group = 7;
        else group = 8;
        formID += group * 7;
    }
    __this->ChangeMonsNo(nextMonsno, formID, nullptr);
    int32_t cond = PersonalSystem::GetEvolutionCondition(routeIndex, nullptr);
    if (cond == EvolveCond::TUUSHIN_ITEM || cond == EvolveCond::SOUBI_NOON || cond == EvolveCond::SOUBI_NIGHT)
        a->SetItemNo(NULL_ITEM, nullptr);
}
