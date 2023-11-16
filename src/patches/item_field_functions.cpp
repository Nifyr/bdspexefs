#include "Audio/AudioManager.hpp"
#include "BtlTowerWork.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Message/MessageWordSetHelper.hpp"
#include "Dpr/UI/PokemonPartyItem.hpp"
#include "Dpr/UI/UIManager.hpp"
#include "FieldManager.hpp"
#include "FlagWork.hpp"
#include "GameManager.hpp"
#include "ItemWork.hpp"
#include "PlayerWork.hpp"
#include "Pml/Item/ItemData.hpp"
#include "Pml/PokePara/CoreParam.hpp"
#include "Pml/PmlUse.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "SmartPoint/AssetAssistant/Sequencer.hpp"
#include "SmartPoint/AssetAssistant/SingletonMonoBehaviour.hpp"
#include "System/Action.hpp"
#include "System/Collections/Generic/List.hpp"
#include "ZoneWork.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "util.hpp"

#define MAKEUP_BAG_ENABLED true
#define MAX_MOVE_COUNT 4
#define MAX_EGG_MOVE_COUNT 4

using namespace Audio;
using namespace Dpr::Message;
using namespace Dpr::UI;
using namespace Pml;
using namespace Pml::Item;
using namespace Pml::Personal;
using namespace SmartPoint::AssetAssistant;
using namespace XLSXContent;
using namespace UnityEngine::Events;

// ItemIDs
constexpr uint16_t SUPER_REPEL = 76;
constexpr uint16_t MAX_REPEL = 77;
constexpr uint16_t REPEL = 79;
constexpr uint16_t GRISEOUS_ORB = 112;
constexpr uint16_t DOUSE_DRIVE = 116;
constexpr uint16_t SHOCK_DRIVE = 117;
constexpr uint16_t BURN_DRIVE = 118;
constexpr uint16_t CHILL_DRIVE = 119;
constexpr uint16_t EXP_SHARE = 216;
constexpr uint16_t GRACIDEA = 466;
constexpr uint16_t RED_ORB = 534;
constexpr uint16_t BLUE_ORB = 535;
constexpr uint16_t DNA_SPLICERS = 628;
constexpr uint16_t REVEAL_GLASS = 638;
constexpr uint16_t GENGARITE = 656;
constexpr uint16_t GARDEVOIRITE = 657;
constexpr uint16_t AMPHAROSITE = 658;
constexpr uint16_t VENUSAURITE = 659;
constexpr uint16_t CHARIZARDITE_X = 660;
constexpr uint16_t BLASTOISINITE = 661;
constexpr uint16_t MEWTWONITE_X = 662;
constexpr uint16_t MEWTWONITE_Y = 663;
constexpr uint16_t BLAZIKENITE = 664;
constexpr uint16_t MEDICHAMITE = 665;
constexpr uint16_t HOUNDOOMINITE = 666;
constexpr uint16_t AGGRONITE = 667;
constexpr uint16_t BANETTITE = 668;
constexpr uint16_t TYRANITARITE = 669;
constexpr uint16_t SCIZORITE = 670;
constexpr uint16_t PINSIRITE = 671;
constexpr uint16_t AERODACTYLITE = 672;
constexpr uint16_t LUCARIONITE = 673;
constexpr uint16_t ABOMASITE = 674;
constexpr uint16_t KANGASKHANITE = 675;
constexpr uint16_t GYARADOSITE = 676;
constexpr uint16_t ABSOLITE = 677;
constexpr uint16_t CHARIZARDITE_Y = 678;
constexpr uint16_t ALAKAZITE = 679;
constexpr uint16_t HERACRONITE = 680;
constexpr uint16_t MAWILITE = 681;
constexpr uint16_t MANECTITE = 682;
constexpr uint16_t GARCHOMPITE = 683;
constexpr uint16_t LATIASITE = 684;
constexpr uint16_t LATIOSITE = 685;
constexpr uint16_t MAKEUP_BAG = 706;
constexpr uint16_t SWAMPERTITE = 752;
constexpr uint16_t SCEPTILITE = 753;
constexpr uint16_t SABLENITE = 754;
constexpr uint16_t ALTARIANITE = 755;
constexpr uint16_t GALLADITE = 756;
constexpr uint16_t AUDINITE = 757;
constexpr uint16_t METAGROSSITE = 758;
constexpr uint16_t SHARPEDONITE = 759;
constexpr uint16_t SLOWBRONITE = 760;
constexpr uint16_t STEELIXITE = 761;
constexpr uint16_t PIDGEOTITE = 762;
constexpr uint16_t GLALITITE = 763;
constexpr uint16_t DIANCITE = 764;
constexpr uint16_t PRISON_BOTTLE = 765;
constexpr uint16_t CAMERUPTITE = 767;
constexpr uint16_t LOPUNNITE = 768;
constexpr uint16_t SALAMENCITE = 769;
constexpr uint16_t BEEDRILLITE = 770;
constexpr uint16_t ZYGARDE_CUBE = 847;
constexpr uint16_t RED_NECTAR = 853;
constexpr uint16_t YELLOW_NECTAR = 854;
constexpr uint16_t PINK_NECTAR = 855;
constexpr uint16_t PURPLE_NECTAR = 856;
constexpr uint16_t N_SOLARIZER = 943;
constexpr uint16_t N_LUNARIZER = 944;
constexpr uint16_t RUSTED_SWORD = 1103;
constexpr uint16_t RUSTED_SHIELD = 1104;
constexpr uint16_t ROTOM_CATALOG = 1278;
constexpr uint16_t REINS_OF_UNITY = 1590;

// DexIDs
constexpr uint16_t VENUSAUR = 3;
constexpr uint16_t CHARIZARD = 6;
constexpr uint16_t BLASTOISE = 9;
constexpr uint16_t BEEDRILL = 15;
constexpr uint16_t PIDGEOT = 18;
constexpr uint16_t PIKACHU = 25;
constexpr uint16_t ALAKAZAM = 65;
constexpr uint16_t SLOWBRO = 80;
constexpr uint16_t GENGAR = 94;
constexpr uint16_t KANGASKHAN = 115;
constexpr uint16_t PINSIR = 127;
constexpr uint16_t GYARADOS = 130;
constexpr uint16_t AERODACTYL = 142;
constexpr uint16_t MEWTWO = 150;
constexpr uint16_t AMPHAROS = 181;
constexpr uint16_t STEELIX = 208;
constexpr uint16_t SCIZOR = 212;
constexpr uint16_t HERACROSS = 214;
constexpr uint16_t HOUNDOOM = 229;
constexpr uint16_t TYRANITAR = 248;
constexpr uint16_t SCEPTILE = 254;
constexpr uint16_t BLAZIKEN = 257;
constexpr uint16_t SWAMPERT = 260;
constexpr uint16_t GARDEVOIR = 282;
constexpr uint16_t SABLEYE = 302;
constexpr uint16_t MAWILE = 303;
constexpr uint16_t AGGRON = 306;
constexpr uint16_t MEDICHAM = 308;
constexpr uint16_t MANECTRIC = 310;
constexpr uint16_t SHARPEDO = 319;
constexpr uint16_t CAMERUPT = 323;
constexpr uint16_t ALTARIA = 334;
constexpr uint16_t BANETTE = 354;
constexpr uint16_t ABSOL = 359;
constexpr uint16_t GLALIE = 362;
constexpr uint16_t SALAMENCE = 373;
constexpr uint16_t METAGROSS = 376;
constexpr uint16_t LATIAS = 380;
constexpr uint16_t LATIOS = 381;
constexpr uint16_t KYOGRE = 382;
constexpr uint16_t GROUDON = 383;
constexpr uint16_t LOPUNNY = 428;
constexpr uint16_t GARCHOMP = 445;
constexpr uint16_t LUCARIO = 448;
constexpr uint16_t ABOMASNOW = 460;
constexpr uint16_t GALLADE = 475;
constexpr uint16_t ROTOM = 479;
constexpr uint16_t GIRATINA = 487;
constexpr uint16_t SHAYMIN = 492;
constexpr uint16_t ARCEUS = 493;
constexpr uint16_t AUDINO = 531;
constexpr uint16_t TORNADUS = 641;
constexpr uint16_t THUNDURUS = 642;
constexpr uint16_t RESHIRAM = 643;
constexpr uint16_t ZEKROM = 644;
constexpr uint16_t LANDORUS = 645;
constexpr uint16_t KYUREM = 646;
constexpr uint16_t GENESECT = 649;
constexpr uint16_t FURFROU = 676;
constexpr uint16_t ZYGARDE = 718;
constexpr uint16_t DIANCIE = 719;
constexpr uint16_t HOOPA = 720;
constexpr uint16_t ORICORIO = 741;
constexpr uint16_t SILVALLY = 773;
constexpr uint16_t SOLGALEO = 791;
constexpr uint16_t LUNALA = 792;
constexpr uint16_t NECROZMA = 800;
constexpr uint16_t ZACIAN = 888;
constexpr uint16_t ZAMAZENTA = 889;
constexpr uint16_t GLASTRIER = 896;
constexpr uint16_t SPECTRIER = 897;
constexpr uint16_t CALYREX = 898;

// MoveIDs
constexpr int32_t NULL_WAZA = 0;
constexpr int32_t THUNDER_SHOCK = 84;
constexpr int32_t CONFUSION = 93;
constexpr int32_t SCARY_FACE = 184;
constexpr int32_t METEOR_MASH = 309;
constexpr int32_t GLACIATE = 549;
constexpr int32_t FREEZE_SHOCK = 553;
constexpr int32_t ICE_BURN = 554;
constexpr int32_t ICICLE_CRASH = 556;
constexpr int32_t FUSION_FLARE = 558;
constexpr int32_t FUSION_BOLT = 559;
constexpr int32_t FLYING_PRESS = 560;
constexpr int32_t DRAINING_KISS = 577;
constexpr int32_t ELECTRIC_TERRAIN = 604;
constexpr int32_t SUNSTEEL_STRIKE = 713;
constexpr int32_t MOONGEIST_BEAM = 714;
constexpr int32_t GLACIAL_LANCE = 824;
constexpr int32_t ASTRAL_BARRAGE = 825;

// WazaIdx
constexpr uint8_t NULL_WAZA_IDX = 4;

// Form-change on equip item
bool Pml_PokePara_CalcTool_DecideFormNoFromHoldItem(int32_t monsno, uint32_t holdItemno, uint16_t *formno, MethodInfo *method) {
    switch (monsno) {
        case GIRATINA: *formno = holdItemno == GRISEOUS_ORB; break;
        case ARCEUS: *formno = MultitypeType(holdItemno); break;
        case GENESECT:
            switch (holdItemno) {
                case SHOCK_DRIVE: *formno = 1; break;
                case BURN_DRIVE: *formno = 2; break;
                case CHILL_DRIVE: *formno = 3; break;
                case DOUSE_DRIVE: *formno = 4; break;
                default: *formno = 0; break;
            }
        case SILVALLY: *formno = RKSSystemType(holdItemno); break;
        default: return false;
    }
    return true;
}
bool Dpr_Battle_Logic_Common_CheckUnbreakablePokeItem(uint16_t monsno, uint16_t itemID, MethodInfo *method) {
    bool unbreakable = false;
    switch (monsno) {
        case VENUSAUR: unbreakable = itemID == VENUSAURITE; break;
        case CHARIZARD: unbreakable = itemID == CHARIZARDITE_X || itemID == CHARIZARDITE_Y; break;
        case BLASTOISE: unbreakable = itemID == BLASTOISINITE; break;
        case BEEDRILL: unbreakable = itemID == BEEDRILLITE; break;
        case PIDGEOT: unbreakable = itemID == PIDGEOTITE; break;
        case ALAKAZAM: unbreakable = itemID == ALAKAZITE; break;
        case SLOWBRO: unbreakable = itemID == SLOWBRONITE; break;
        case GENGAR: unbreakable = itemID == GENGARITE; break;
        case KANGASKHAN: unbreakable = itemID == KANGASKHANITE; break;
        case PINSIR: unbreakable = itemID == PINSIRITE; break;
        case GYARADOS: unbreakable = itemID == GYARADOSITE; break;
        case AERODACTYL: unbreakable = itemID == AERODACTYLITE; break;
        case MEWTWO: unbreakable = itemID == MEWTWONITE_X || itemID == MEWTWONITE_Y; break;
        case AMPHAROS: unbreakable = itemID == AMPHAROSITE; break;
        case STEELIX: unbreakable = itemID == STEELIXITE; break;
        case SCIZOR: unbreakable = itemID == SCIZORITE; break;
        case HERACROSS: unbreakable = itemID == HERACRONITE; break;
        case HOUNDOOM: unbreakable = itemID == HOUNDOOMINITE; break;
        case TYRANITAR: unbreakable = itemID == TYRANITARITE; break;
        case SCEPTILE: unbreakable = itemID == SCEPTILITE; break;
        case BLAZIKEN: unbreakable = itemID == BLAZIKENITE; break;
        case SWAMPERT: unbreakable = itemID == SWAMPERTITE; break;
        case GARDEVOIR: unbreakable = itemID == GARDEVOIRITE; break;
        case SABLEYE: unbreakable = itemID == SABLENITE; break;
        case MAWILE: unbreakable = itemID == MAWILITE; break;
        case AGGRON: unbreakable = itemID == AGGRONITE; break;
        case MEDICHAM: unbreakable = itemID == MEDICHAMITE; break;
        case MANECTRIC: unbreakable = itemID == MANECTITE; break;
        case SHARPEDO: unbreakable = itemID == SHARPEDONITE; break;
        case CAMERUPT: unbreakable = itemID == CAMERUPTITE; break;
        case ALTARIA: unbreakable = itemID == ALTARIANITE; break;
        case BANETTE: unbreakable = itemID == BANETTITE; break;
        case ABSOL: unbreakable = itemID == ABSOLITE; break;
        case GLALIE: unbreakable = itemID == GLALITITE; break;
        case SALAMENCE: unbreakable = itemID == SALAMENCITE; break;
        case METAGROSS: unbreakable = itemID == METAGROSSITE; break;
        case LATIAS: unbreakable = itemID == LATIASITE; break;
        case LATIOS: unbreakable = itemID == LATIOSITE; break;
        case KYOGRE: unbreakable = itemID == BLUE_ORB; break;
        case GROUDON: unbreakable = itemID == RED_ORB; break;
        case LOPUNNY: unbreakable = itemID == LOPUNNITE; break;
        case GARCHOMP: unbreakable = itemID == GARCHOMPITE; break;
        case LUCARIO: unbreakable = itemID == LUCARIONITE; break;
        case ABOMASNOW: unbreakable = itemID == ABOMASITE; break;
        case GALLADE: unbreakable = itemID == GALLADITE; break;
        case AUDINO: unbreakable = itemID == AUDINITE; break;
        case GENESECT: unbreakable = itemID == SHOCK_DRIVE || itemID == BURN_DRIVE || itemID == CHILL_DRIVE ||
        itemID == DOUSE_DRIVE; break;
        case DIANCIE: unbreakable = itemID == DIANCITE; break;
        case SILVALLY: unbreakable = RKSSystemType(itemID) > 0; break;
        case ZACIAN: unbreakable = itemID == RUSTED_SWORD; break;
        case ZAMAZENTA: unbreakable = itemID == RUSTED_SHIELD; break;
        default: break;
    }
    return unbreakable || Common::CheckUnbreakablePokeItem(monsno, itemID, method);
}

// Exp Share
// 70+ externals...
extern bool DAT_7104cbb2ca;
extern bool DAT_7104cbd681;
extern String_o *StringLiteral_7097;
extern String_o *StringLiteral_11534;
extern String_o *StringLiteral_11693;
extern String_o *StringLiteral_11711;
extern String_o *StringLiteral_11713;
extern String_o *StringLiteral_11719;
extern String_o *StringLiteral_11720;
extern String_o *StringLiteral_11721;
extern String_o *StringLiteral_11722;
extern String_o *StringLiteral_11723;
extern String_o *StringLiteral_11724;
void Dpr_UI_UIBag___c__DisplayClass127_1__ShowItemContextMenu_b__11(UIBag___c__DisplayClass127_1_o *__this,
                                                                    MethodInfo *method) {
    EnsureTypeInfoInit(&DAT_7104cbd681, 0x9563);
    EnsureTypeInfoInit(&DAT_7104cbb2ca, 0x6bcc);
    EnsureClassInit(PlayerWork_TypeInfo);
    EnsureClassInit(MessageWordSetHelper_TypeInfo);
    EnsureClassInit(FieldManager_TypeInfo);
    EnsureClassInit(ItemWork_TypeInfo);
    EnsureClassInit(SingletonMonoBehaviour_UIManager__TypeInfo);
    EnsureClassInit(SingletonMonoBehaviour_AudioManager__TypeInfo);
    EnsureClassInit(UIWindow_TypeInfo);
    EnsureClassInit(Sequencer_TypeInfo);
    EnsureClassInit(BtlTowerWork_TypeInfo);
    EnsureClassInit(UIManager_TypeInfo);
    int32_t fieldFuncType = __this->fields.fieldFuncType;
    UIBag___c__DisplayClass127_0_o *uibdc1270 = __this->fields.CS___8__locals1;
    ItemInfo_o *ii = uibdc1270->fields.item;
    UIBag_o *uib = uibdc1270->fields.__4__this;
    UIMsgWindowController_o *uimwc = uib->fields.msgWindowController;
    FieldWalkingManager_o *fwm = FieldManager_TypeInfo->static_fields->fwMng;
    int32_t itemID = ii->get_Id(nullptr);
    auto * uim = (UIManager_o *)SingletonMonoBehaviour_object_::get_Instance(
            SingletonMonoBehaviour_UIManager__get_Instance);
    switch (fieldFuncType) {
        case ItemData_FieldFunctionType::ITEMUSE_FLD_RECOVER:
        case ItemData_FieldFunctionType::ITEMUSE_FLD_WAZA:
        case ItemData_FieldFunctionType::ITEMUSE_FLD_EVOLUTION:
        case ItemData_FieldFunctionType::ITEMUSE_FLD_APPLICATION:
        case ItemData_FieldFunctionType::ITEMUSE_FLD_KINOMI:
        case ItemData_FieldFunctionType::ITEMUSE_FLD_FORM_CHANGE: {
            if (!ii->get_IsRecoveryAllDead(nullptr)) {
                uimwc->OpenMsgWindow(
                        0, StringLiteral_11711, false, false,
                        nullptr, nullptr, nullptr);
                auto *onClicked = (UnityAction_object__int__o *)
                        il2cpp_object_new(UnityAction_PokemonPartyItem__int__TypeInfo);
                onClicked->ctor((Il2CppObject *)uib, UIBag_OnPokemonPartyClickedToUseItem);
                uib->StartSelectPokemonParty((UnityAction_PokemonPartyItem__int__o *)onClicked,
                                             nullptr);
                return;
            }
            auto *uibdc1275 = (UIBag___c__DisplayClass127_5_o *)
                    il2cpp_object_new(UIBag___c__DisplayClass127_5_TypeInfo);
            uibdc1275->fields.CS___8__locals5 = __this;
            system_array_init(&uibdc1275->fields.CS___8__locals5);
            auto *xmtis = (List_XMenuTopItem__o *)
                    il2cpp_object_new(List_PokemonPartyItem__TypeInfo);
            xmtis->ctor(List_PokemonPartyItem__ctor);
            uibdc1275->fields.recoverPokemonItems = (List_PokemonPartyItem__o *)xmtis;
            system_array_init(&uibdc1275->fields.recoverPokemonItems);
            List_PokemonPartyItem__o *ppis = uib->fields.pokemonParty->fields._activeItems;
            int32_t ppiCount = ppis->fields._size;
            float recoverRatio = uib->GetRecoverHpRate(ii->get_RecoveryHpValue(nullptr), nullptr);
            for (int32_t i = 0; i < ppiCount; ++i) {
                PokemonPartyItem_o *ppi = ppis->fields._items->m_Items[i];
                auto *cp = (CoreParam_o *)ppi->fields._param->fields.pokemonParam;
                if (!cp->IsHpZero(nullptr))
                    continue;
                uint32_t maxHP = cp->GetMaxHp(nullptr);
                uint32_t recoverHP = 1;
                if (maxHP != 1)
                    recoverHP = (int32_t)(recoverRatio * (float)maxHP);
                cp->RecoverHp(recoverHP, nullptr);
                xmtis->Add(ppi, List_PokemonPartyItem__Add);
                fwm->CreateTurearuki(nullptr);
            }
            if (xmtis->fields._size != 0) {
                auto *uibdc1276 = (UIBag___c__DisplayClass127_6_o *)
                        il2cpp_object_new(UIBag___c__DisplayClass127_6_TypeInfo);
                uibdc1276->fields.CS___8__locals6 = uibdc1275;
                system_array_init(&uibdc1276->fields.CS___8__locals6);
                uibdc1276->fields.itemIndex = 0;
                uibdc1276->_ShowItemContextMenu_g__UpdateHp_20(nullptr);
                return;
            }
            auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
            onCloseWindow->ctor((Il2CppObject *)uibdc1270,
                                UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
            uimwc->OpenMsgWindow(0x0, StringLiteral_11693, true, false, nullptr, onCloseWindow, nullptr);
            return;
        }
        case ItemData_FieldFunctionType::ITEMUSE_FLD_BAG_MSG: {
            auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
            onCloseWindow->ctor((Il2CppObject *)uibdc1270,
                                UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
            if (itemID == EXP_SHARE) {
                PlayerWork::SetBool(2198, !PlayerWork::GetBool(2198, nullptr), nullptr);
                MessageWordSetHelper::SetPlayerNickNameWord(0, nullptr);
                MessageWordSetHelper::SetItemWord(1, itemID, 1, nullptr);
                uimwc->OpenMsgWindow(0, StringLiteral_11723, true, false, nullptr, onCloseWindow, nullptr);
                return;
            }
            if ((itemID != SUPER_REPEL && itemID != MAX_REPEL && itemID != REPEL) ||
            ZoneWork::IsUnderGround(PlayerWork::get_zoneID(nullptr), nullptr)) {
                MessageWordSetHelper::SetPlayerNickNameWord(0,nullptr);
                uimwc->OpenMsgWindow(0, StringLiteral_11713, true, false, nullptr, onCloseWindow, nullptr);
                return;
            }
            uint16_t oldItemID = 0;
            if (ItemWork::IsUseSpray(&oldItemID, nullptr)) {
                uimwc->OpenMsgWindow(0x0,StringLiteral_11722, true, false,nullptr, onCloseWindow, nullptr);
                return;
            }
            ItemWork::SetSpray(itemID, (int16_t)(ii->GetParam(ItemData_PrmID::ATTACK, nullptr) * 5), nullptr);
            ItemWork::SubItem(itemID, 1, nullptr);
            auto *am = (AudioManager_o *)SingletonMonoBehaviour_object_::get_Instance(
                    SingletonMonoBehaviour_AudioManager__get_Instance);
            am->PlaySe(0x8e8a8de1, nullptr, nullptr);
            MessageWordSetHelper::SetPlayerNickNameWord(0, nullptr);
            MessageWordSetHelper::SetItemWord(1, itemID, 1, nullptr);
            onCloseWindow = uibdc1270->fields.__9__17;
            if (onCloseWindow == nullptr) {
                onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
                onCloseWindow->ctor((Il2CppObject *)uibdc1270, UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__17);
                uibdc1270->fields.__9__17 = onCloseWindow;
                system_array_init(&uibdc1270->fields.__9__17);
            }
            uimwc->OpenMsgWindow(0, StringLiteral_11723, true, false, nullptr, onCloseWindow, nullptr);
            return;
        }
        case ItemData_FieldFunctionType::ITEMUSE_FLD_BOUKENNOOTO: {
            uib->Close(nullptr, 37, true, nullptr);
            Action_o *action = uibdc1270->fields.__9__12;
            if (action == nullptr) {
                action = (Action_o *)il2cpp_object_new(Action_TypeInfo);
                action->ctor((Il2CppObject *)uibdc1270, UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__12);
                uibdc1270->fields.__9__12 = action;
                system_array_init(&uibdc1270->fields.__9__12);
            }
            Color_o color = { .fields = { .r = 0.0, .g = 0.0, .b = 0.0, .a = 0.0 } };
            IEnumerator_o *routine = ((UIWindow_o *)uib)->FadeTransition_object_(color, UIWindow_TypeInfo->
            static_fields->TransitionFadeFillColor.fields.r, action, UIWindow_FadeTransition_AdventureNoteWindow_);
            Sequencer::Start(routine, nullptr);
            return;
        }
        case ItemData_FieldFunctionType::ITEMUSE_FLD_POFINKEESU: {
            auto *uibdc1272 = (UIBag___c__DisplayClass127_2_o *)
                    il2cpp_object_new(UIBag___c__DisplayClass127_2_TypeInfo);
            uibdc1272->fields.CS___8__locals2 = __this;
            system_array_init(&uibdc1272->fields.CS___8__locals2);
            uibdc1272->fields.saveOnClosed = uib->fields.super.onClosed;
            system_array_init(&uibdc1272->fields.saveOnClosed);
            uibdc1272->fields.saveOnPreClose = uib->fields.super.onPreClose;
            system_array_init(&uibdc1272->fields.saveOnPreClose);
            uib->fields.super.onPreClose = nullptr;
            system_array_init(&uib->fields.super.onPreClose);
            auto *onClosed_ = (UnityAction_XMenuTopItem__o *)il2cpp_object_new(UnityAction_UIWindow__TypeInfo);
            onClosed_->ctor((Il2CppObject *)uibdc1272, UIBag___c__DisplayClass127_2__ShowItemContextMenu_b__14);
            uib->Close((UnityAction_UIWindow__o *)onClosed_, 45, true, nullptr);
            return;
        }
        case ItemData_FieldFunctionType::ITEMUSE_FLD_TENKAINOHUE: {
            int32_t zoneID = PlayerWork::get_zoneID(nullptr);
            if (zoneID != 0xd8 && zoneID != 0xd9) {
                MessageWordSetHelper::SetPlayerNickNameWord(0, nullptr);
                auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
                onCloseWindow->ctor((Il2CppObject *)uibdc1270,
                                    UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
                uimwc->OpenMsgWindow(0, StringLiteral_11713, true, false, nullptr, onCloseWindow, nullptr);
                return;
            }
            auto *onCall = (UnityAction_XMenuTopItem__o *)uibdc1270->fields.__9__13;
            if (onCall == nullptr) {
                onCall = (UnityAction_XMenuTopItem__o *)
                        il2cpp_object_new(UnityAction_UnityAction_UIWindow___TypeInfo);
                onCall->ctor((Il2CppObject *)uibdc1270, UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__13);
                uibdc1270->fields.__9__13 = (UnityAction_UnityAction_UIWindow___o *)onCall;
                system_array_init(&uibdc1270->fields.__9__13);
            }
            uim->CloseXMenu((UnityAction_UnityAction_UIWindow___o *)onCall, nullptr);
            return;
        }
        case ItemData_FieldFunctionType::ITEMUSE_FLD_POINTOKAADO: {
            MessageWordSetHelper::SetDigitWord(0x0, BtlTowerWork::GetBP(nullptr),nullptr);
            auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
            onCloseWindow->ctor((Il2CppObject *)uibdc1270,
                                UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
            uimwc->OpenMsgWindow(0, StringLiteral_11721, true, false, nullptr, onCloseWindow, nullptr);
            return;
        }
        case ItemData_FieldFunctionType::ITEMUSE_FLD_DS_PLAYER: {
            uim->UseDSPlayerItem(nullptr);
            String_o *labelName = StringLiteral_11720;
            if (!ItemWork::IsDsPlayer(nullptr)) {
                labelName = StringLiteral_11719;
            }
            auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
            onCloseWindow->ctor(
                    (Il2CppObject *)uibdc1270,UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
            uimwc->OpenMsgWindow(0, labelName, true, false, nullptr, onCloseWindow, nullptr);
            return;
        }
        default: {
            auto *onUseFieldItem = (Func_object__Int32Enum__o *)UIManager_TypeInfo->static_fields->onUseFieldItem;
            if (UIManager_TypeInfo->static_fields->onUseFieldItem != nullptr) {
                int32_t fieldUseResult = onUseFieldItem->Invoke(
                        (Il2CppObject *)ii, Func_ItemInfo__UIManager_FieldUseResult__Invoke);
                if (fieldUseResult == 2) {
                    fwm->SetPartnerNameToLabel(0, nullptr);
                    auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
                    onCloseWindow->ctor((Il2CppObject *)uibdc1270,
                                        UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
                    uimwc->OpenMsgWindow(StringLiteral_7097, StringLiteral_11534, true, false,
                                         nullptr, onCloseWindow, nullptr);
                    return;
                }
                if (fieldUseResult == 0) {
                    if (!ii->get_IsNoSpend(nullptr))
                        ItemWork::SubItem(itemID, 1, nullptr);
                    PlayerWork_TypeInfo->static_fields->_UsedFieldItem_k__BackingField = ii;
                    system_array_init(&PlayerWork_TypeInfo->static_fields->_UsedFieldItem_k__BackingField);
                    auto *onCall = (UnityAction_XMenuTopItem__o *)uibdc1270->fields.__9__19;
                    if (onCall == nullptr) {
                        onCall = (UnityAction_XMenuTopItem__o *)
                                il2cpp_object_new(UnityAction_UnityAction_UIWindow___TypeInfo);
                        onCall->ctor(
                                (Il2CppObject *)uibdc1270, UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__19);
                        uibdc1270->fields.__9__19 = (UnityAction_UnityAction_UIWindow___o *)onCall;
                        system_array_init(&uibdc1270->fields.__9__19);
                    }
                    uim->CloseXMenu((UnityAction_UnityAction_UIWindow___o *)onCall,nullptr);
                    return;
                }
            }
            auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
            onCloseWindow->ctor((Il2CppObject *)uibdc1270,
                                UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0);
            if (fieldFuncType != ItemData_FieldFunctionType::ITEMUSE_FLD_CYCLE || !PlayerWork::IsFormBicycle(nullptr)) {
                MessageWordSetHelper::SetPlayerNickNameWord(0, nullptr);
                uimwc->OpenMsgWindow(0, StringLiteral_11713, true, false, nullptr, onCloseWindow, nullptr);
                return;
            }
            uimwc->OpenMsgWindow(0, StringLiteral_11724, true, false, nullptr, onCloseWindow, nullptr);
            return;
        }
    }
}
bool Dpr_Battle_Logic_MainModule_HasPlayerGakusyuSouti(MainModule_o *mainModule) {
    return !PlayerWork::GetBool(2198, nullptr);
}

// Form-change on use items
void ConditionalAdd(List_ZoneID__o * zidl, int32_t flagNo, int32_t item) {
    if (FlagWork::GetFlag(0x530,nullptr))
        zidl->Add(0x54,List_ContextMenuID__Add);
}
bool FormChange(UIBag_o *uib, PokemonPartyItem_o *ppi, bool *success, uint16_t nextFormID) {
    auto *onComplete = (Action_PokeWalkingFormation_SheetSheet1__o *)
            il2cpp_object_new(Action_PokemonParam__TypeInfo);
    onComplete->ctor((Il2CppObject *)uib, UIBag_ShowFormChangeResult);
    *success = true;
    return ppi->FormChange(nextFormID, uib->fields.effectRoot, nullptr,
                           (Action_PokemonParam__o *)onComplete, nullptr);
}
int32_t GetFuseDexID(UIBag_o *uib, uint16_t option0, uint16_t option1) {
    List_PokemonPartyItem__o *ppil = uib->fields.pokemonParty->fields._activeItems;
    for (int32_t i = 0; i < ppil->fields._size; ++i) {
        int32_t otherDexID = ((CoreParam_o *)ppil->fields._items->m_Items[i]->fields._param->fields.pokemonParam)->
                GetMonsNo(nullptr);
        if (otherDexID == option0 || otherDexID == option1)
            return otherDexID;
    }
    return -1;
}
bool PartyHasDexID(UIBag_o *uib, uint16_t dexID) {
    List_PokemonPartyItem__o *ppil = uib->fields.pokemonParty->fields._activeItems;
    for (int32_t i = 0; i < ppil->fields._size; ++i) {
        int32_t otherDexID = ((CoreParam_o *)ppil->fields._items->m_Items[i]->fields._param->fields.pokemonParam)->
                GetMonsNo(nullptr);
        if (otherDexID == dexID)
            return true;
    }
    return false;
}
void ReplaceMove(CoreParam_o *cp, int32_t oldMoveID, int32_t newMoveID) {
    uint8_t wazaIndex = cp->GetWazaIndex(oldMoveID, nullptr);
    if (wazaIndex == NULL_WAZA_IDX) return;
    cp->SetWaza(wazaIndex, newMoveID, nullptr);
}
void RemoveMove(CoreParam_o *cp, int32_t removeMoveID) {
    uint8_t wazaIndex = cp->GetWazaIndex(removeMoveID, nullptr);
    cp->SetWaza(wazaIndex, NULL_WAZA, nullptr);
    cp->SetWazaPPUpCount(wazaIndex, 0, nullptr);
    cp->SetWazaPP(wazaIndex, 0, nullptr);
    cp->CloseUpWazaPos(nullptr);
}
extern String_o *StringLiteral_11741;
extern bool DAT_7104cbd69d;
void ForgetMove(UIBag_o *uib, CoreParam_o *cp, int32_t forgetMoveID, int32_t fallbackMoveID) {
    EnsureTypeInfoInit(&DAT_7104cbd69d, 0x95ab);
    uint8_t wazaIndex = cp->GetWazaIndex(forgetMoveID, nullptr);
    if (wazaIndex == NULL_WAZA_IDX) return;
    RemoveMove(cp, forgetMoveID);
    if (cp->GetWazaCount(nullptr) == 0)
        cp->SetWaza(0, fallbackMoveID, nullptr);
    MessageWordSetHelper::SetPokemonNickNameWord(0, cp, true, nullptr);
    MessageWordSetHelper::SetWazaNameWord(1, forgetMoveID, nullptr);
    uib->fields.msgWindowController->OpenMsgWindow(0, StringLiteral_11741, true,
                                                   false, nullptr,
                                                   nullptr, nullptr);
}
extern String_o *StringLiteral_11737;
extern String_o *StringLiteral_11742;
extern bool DAT_7104cbb9d0;
extern bool DAT_7104cbd69e;
void LearnMove(UIBag_o *uib, PokemonParam_o *pp, int32_t moveID) {
    EnsureTypeInfoInit(&DAT_7104cbb9d0, 0x9a20);
    auto *cp = (CoreParam_o *)pp;
    if (cp->GetWazaIndex(moveID, nullptr) != NULL_WAZA_IDX) return;
    uint8_t wazaIndex = cp->GetWazaCount(nullptr);
    if (wazaIndex < MAX_MOVE_COUNT) {
        cp->SetWaza(wazaIndex, moveID, nullptr);
        MessageWordSetHelper::SetPokemonNickNameWord(0, cp, true, nullptr);
        MessageWordSetHelper::SetWazaNameWord(1, moveID, nullptr);
        socket_log_initialize();
        socket_log_fmt("StringLiteral_11737: %X", StringLiteral_11737);
        uib->fields.msgWindowController->OpenMsgWindow(0, StringLiteral_11737, true,
                                                       false, nullptr,
                                                       nullptr, nullptr);
        return;
    }
    auto *uibdc1450 = (UIBag___c__DisplayClass145_0_o *)
            il2cpp_object_new(UIBag___c__DisplayClass145_0_TypeInfo);
    uibdc1450->ctor(nullptr);
    uibdc1450->fields.pokemonParam = pp;
    system_array_init(&uibdc1450->fields.pokemonParam);
    uibdc1450->fields.__4__this = uib;
    system_array_init(&uibdc1450->fields.__4__this);
    EnsureTypeInfoInit(&DAT_7104cbd69e, 0x95ac);
    auto *uibdc1451 = (UIBag___c__DisplayClass145_1_o *)
            il2cpp_object_new(UIBag___c__DisplayClass145_1_TypeInfo);
    uibdc1451->fields.CS___8__locals1 = uibdc1450;
    system_array_init(&uibdc1451->fields.CS___8__locals1);
    uibdc1451->fields.addWazaNo = moveID;
    MessageWordSetHelper::SetPokemonNickNameWord(0, cp, true, nullptr);
    MessageWordSetHelper::SetWazaNameWord(1, moveID, nullptr);
    auto *onFinishedMessage = (Action_o *) il2cpp_object_new(Action_TypeInfo);
    onFinishedMessage->ctor((Il2CppObject *)uibdc1451,
                            UIBag___c__DisplayClass145_1__ShowFormChangeResult_b__2);
    uib->fields.msgWindowController->OpenMsgWindow(0, StringLiteral_11742, true,
                                                   false, onFinishedMessage, nullptr,
                                                   nullptr);
}
void ReduceToLearnableMoves(UIBag_o *uib, PokemonParam_o *pp, int32_t fallbackMoveID) {
    auto *cp = (CoreParam_o *)pp;
    int32_t dexID = cp->GetMonsNo(nullptr);
    uint16_t formID = cp->GetFormNo(nullptr);
    PersonalSystem::LoadPersonalData(dexID, formID, nullptr);
    PersonalSystem::LoadWazaOboeData(dexID, formID, nullptr);
    uint8_t learnSetSize = PersonalSystem::GetWazaOboeNum(nullptr);
    Array<ItemTable_SheetWazaMachine_o *> *itswms =
            PmlUse_o::get_Instance(nullptr)->fields.itemPrmTotal->fields.WazaMachine;
    uint8_t moveCount = cp->GetWazaCount(nullptr);
    for (int i = 0; i < moveCount; ++i) {
        int32_t moveID = cp->GetWazaNo(i, nullptr);
        if (moveID == NULL_WAZA) continue;
        bool keep = false;
        for (int j = 0; j < MAX_EGG_MOVE_COUNT && !keep; ++j)
            keep = moveID == cp->GetTamagoWazaNo(j, nullptr);
        for (int j = 0; j < learnSetSize && !keep; ++j)
            keep = moveID == PersonalSystem::GetWazaOboeWazaNo(j, nullptr);
        for (uint32_t j = 0; j < itswms->max_length && !keep; ++j) {
            ItemTable_SheetWazaMachine_o *itswm = itswms->m_Items[j];
            if (PersonalSystem::CheckPersonalWazaMachine(itswm->fields.machineNo, (MethodInfo *) nullptr))
                keep = moveID == itswm->fields.wazaNo;
        }
        if (keep) continue;
        cp->SetWaza(i, NULL_WAZA, nullptr);
        cp->SetWazaPPUpCount(i, 0, nullptr);
        cp->SetWazaPP(i, 0, nullptr);
    }
    cp->CloseUpWazaPos(nullptr);
    if (cp->GetWazaCount(nullptr) == 0)
        LearnMove(uib, pp, fallbackMoveID);
}
extern bool DAT_7104cbb9cf;
extern String_o *StringLiteral_11712;
void Dpr_UI_UIBag_UseFormChangeItem(UIBag_o *__this, PokemonPartyItem_o *pokemonPartyItem, ItemInfo_o *itemInfo,
                                    MethodInfo *method) {
    EnsureTypeInfoInit(&DAT_7104cbb9cf, 0x9a2e);
    auto *uibdc1440 = (UIBag___c__DisplayClass144_0_o *)
            il2cpp_object_new(UIBag___c__DisplayClass144_0_TypeInfo);
    uibdc1440->ctor(nullptr);
    uibdc1440->fields.__4__this = __this;
    system_array_init(&uibdc1440->fields.__4__this);
    uibdc1440->fields.pokemonPartyItem = pokemonPartyItem;
    system_array_init(&uibdc1440->fields.pokemonPartyItem);
    PokemonParam_o *pp = pokemonPartyItem->fields._param->fields.pokemonParam;
    uibdc1440->fields.pokemonParam = pp;
    system_array_init(&uibdc1440->fields.pokemonParam);
    int32_t itemID = itemInfo->get_Id(nullptr);
    auto *cp = (CoreParam_o *)pp;
    UIMsgWindowController_o *uimwc = __this->fields.msgWindowController;
    int32_t dexID = cp->GetMonsNo(nullptr);
    uint16_t formID = cp->GetFormNo(nullptr);
    bool success = false;
    switch (itemID) {
        case ROTOM_CATALOG: {
            if (dexID != ROTOM) break;
            auto *cmidl = (List_ZoneID__o *)
                    il2cpp_object_new(List_ContextMenuID__TypeInfo);
            cmidl->ctor(List_ContextMenuID__ctor);
            cmidl->Add(0x53,List_ContextMenuID__Add);
            ConditionalAdd(cmidl, 0x530, 0x54);
            ConditionalAdd(cmidl, 0x531, 0x55);
            ConditionalAdd(cmidl, 0x532, 0x56);
            ConditionalAdd(cmidl, 0x533, 0x57);
            ConditionalAdd(cmidl, 0x534, 0x58);
            cmidl->Add(0x59,List_ContextMenuID__Add);
            auto *cmida = (Action_Notification_Message__o *) il2cpp_object_new(Action_ContextMenuID__TypeInfo);
            cmida->ctor((Il2CppObject *)uibdc1440, UIBag___c__DisplayClass144_0__UseFormChangeItem_b__0);
            UnityEngine_Vector2_o pivot = { .fields = { .x = 0.5, .y = 0.5 } };
            UnityEngine_Vector3_o pos = { .fields = { .x = 1040.0, .y = 360.0, .z = 0.0 } };
            __this->OpenContextMenu((ContextMenuID_array *)((List_Int32Enum__o *)cmidl)->ToArray(
                                            List_ContextMenuID__ToArray), (Action_ContextMenuID__o *)cmida, pivot, pos,
                                    nullptr,false,false, nullptr);
            uimwc->OpenMsgWindow(0, StringLiteral_11712, false, true,
                                 nullptr, nullptr, nullptr);
            return;
        }
        case GRACIDEA: {
            EnsureClassInit(GameManager_TypeInfo);
            if (dexID == SHAYMIN && formID == 0 &&
                GameManager::get_currentPeriodOfDay(nullptr) - 3 > 1 && cp->GetSick(nullptr) != 3)
                FormChange(__this, pokemonPartyItem, &success, 1);
        }
        case MAKEUP_BAG: {
            if (!MAKEUP_BAG_ENABLED) break;
            if (dexID == PIKACHU && formID >= 1 && formID < 7) {
                uint16_t nextFormID = formID % 6 + 1;
                FormChange(__this, pokemonPartyItem, &success, nextFormID);
                switch (nextFormID) {
                    case 1:
                        ForgetMove(__this, cp, FLYING_PRESS, THUNDER_SHOCK);
                        break;
                    case 2:
                        LearnMove(__this, pp, METEOR_MASH);
                        break;
                    case 3:
                        RemoveMove(cp, METEOR_MASH);
                        LearnMove(__this, pp, ICICLE_CRASH);
                        break;
                    case 4:
                        RemoveMove(cp, ICICLE_CRASH);
                        LearnMove(__this, pp, DRAINING_KISS);
                        break;
                    case 5:
                        RemoveMove(cp, DRAINING_KISS);
                        LearnMove(__this, pp, ELECTRIC_TERRAIN);
                        break;
                    case 6:
                        RemoveMove(cp, ELECTRIC_TERRAIN);
                        LearnMove(__this, pp, FLYING_PRESS);
                        break;
                    default: break;
                }
            } else if (dexID == FURFROU)
                FormChange(__this, pokemonPartyItem, &success, (formID + 1) % 10);
        }
        case REVEAL_GLASS: {
            if (dexID == TORNADUS || dexID == THUNDURUS || dexID == LANDORUS)
                FormChange(__this, pokemonPartyItem, &success, (formID + 1) % 2);
        }
        case PRISON_BOTTLE: {
            if (dexID == HOOPA)
                FormChange(__this, pokemonPartyItem, &success, (formID + 1) % 2);
        }
        case DNA_SPLICERS: {
            if (dexID != KYUREM) break;
            uint16_t nextFormID = formID;
            if (formID == 0)
                switch (GetFuseDexID(__this, RESHIRAM, ZEKROM)) {
                    case RESHIRAM: nextFormID = 1; break;
                    case ZEKROM: nextFormID = 2; break;
                    default: break;
                }
            else
                nextFormID = 0;
            if (nextFormID != formID) {
                FormChange(__this, pokemonPartyItem, &success, nextFormID);
                switch (nextFormID) {
                    case 0:
                        ReplaceMove(cp, FREEZE_SHOCK, GLACIATE);
                        ReplaceMove(cp, ICE_BURN, GLACIATE);
                        ReplaceMove(cp, FUSION_FLARE, SCARY_FACE);
                        ReplaceMove(cp, FUSION_BOLT, SCARY_FACE);
                        break;
                    case 1:
                        ReplaceMove(cp, SCARY_FACE, FUSION_FLARE);
                        ReplaceMove(cp, GLACIATE, ICE_BURN);
                        break;
                    case 2:
                        ReplaceMove(cp, SCARY_FACE, FUSION_BOLT);
                        ReplaceMove(cp, GLACIATE, FREEZE_SHOCK);
                        break;
                    default: break;
                }
            }
        }
        case ZYGARDE_CUBE: {
            if (dexID == ZYGARDE && formID < 4)
                FormChange(__this, pokemonPartyItem, &success, (formID + 1) % 4);
        }
        case RED_NECTAR:
        case YELLOW_NECTAR:
        case PINK_NECTAR:
        case PURPLE_NECTAR: {
            if (dexID != ORICORIO) break;
            if (itemID == RED_NECTAR && formID != 0)
                FormChange(__this, pokemonPartyItem, &success, 0);
            else if (itemID == YELLOW_NECTAR && formID != 1)
                FormChange(__this, pokemonPartyItem, &success, 1);
            else if (itemID == PINK_NECTAR && formID != 2)
                FormChange(__this, pokemonPartyItem, &success, 2);
            else if (itemID == PURPLE_NECTAR && formID != 3)
                FormChange(__this, pokemonPartyItem, &success, 3);
            if (success)
                ItemWork::SubItem(itemID, 1, nullptr);
        }
        case N_SOLARIZER:
        case N_LUNARIZER: {
            if (dexID != NECROZMA) break;
            uint16_t nextFormID = formID;
            if (itemID == N_SOLARIZER) {
                if (formID == 0 && PartyHasDexID(__this, SOLGALEO))
                    nextFormID = 1;
                else if (formID == 1)
                    nextFormID = 0;
            } else if (itemID == N_LUNARIZER) {
                if (formID == 0 && PartyHasDexID(__this, LUNALA))
                    nextFormID = 2;
                else if (formID == 2)
                    nextFormID = 0;
            }
            if (formID != nextFormID) {
                FormChange(__this, pokemonPartyItem, &success, nextFormID);
                switch (nextFormID) {
                    case 0:
                        ForgetMove(__this, cp, SUNSTEEL_STRIKE, CONFUSION);
                        ForgetMove(__this, cp, MOONGEIST_BEAM, CONFUSION);
                        break;
                    case 1:
                        LearnMove(__this, pp, SUNSTEEL_STRIKE);
                        break;
                    case 2:
                        LearnMove(__this, pp, MOONGEIST_BEAM);
                        break;
                    default: break;
                }
            }
        }
        case REINS_OF_UNITY: {
            if (dexID != CALYREX) break;
            uint16_t nextFormID = formID;
            if (formID == 0)
                switch (GetFuseDexID(__this, GLASTRIER, SPECTRIER)) {
                    case GLASTRIER: nextFormID = 1; break;
                    case SPECTRIER: nextFormID = 2; break;
                    default: break;
                }
            else
                nextFormID = 0;
            if (nextFormID != formID) {
                FormChange(__this, pokemonPartyItem, &success, nextFormID);
                switch (nextFormID) {
                    case 0:
                        ReduceToLearnableMoves(__this, pp, CONFUSION);
                        break;
                    case 1:
                        LearnMove(__this, pp, GLACIAL_LANCE);
                        break;
                    case 2:
                        LearnMove(__this, pp, ASTRAL_BARRAGE);
                        break;
                    default: break;
                }
            }
        }
        default: break;
    }
    if (success) {
        pokemonPartyItem->Setup(pokemonPartyItem->fields._param, nullptr);
        return;
    }
    auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
    onCloseWindow->ctor((Il2CppObject *)__this, UIBag_EndSelectPokemonParty);
    uimwc->OpenMsgWindow(0, StringLiteral_11693, true, false,
                         nullptr, onCloseWindow, nullptr);
}
