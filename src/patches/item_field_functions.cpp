#include "Dpr/Message/MessageWordSetHelper.hpp"
#include "Dpr/UI/PokemonPartyItem.hpp"
#include "Dpr/UI/UIBag.hpp"
#include "FlagWork.hpp"
#include "GameManager.hpp"
#include "ItemWork.hpp"
#include "Pml/PokePara/CoreParam.hpp"
#include "Pml/PmlUse.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "System/Action.hpp"
#include "System/Collections/Generic/List.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "util.hpp"

#define MAKEUP_BAG_ENABLED true
#define MAX_MOVE_COUNT 4
#define MAX_EGG_MOVE_COUNT 4

using namespace Dpr::Message;
using namespace Dpr::UI;
using namespace Pml;
using namespace Pml::Personal;
using namespace XLSXContent;

// ItemIDs
constexpr uint16_t GRACIDEA = 466;
constexpr uint16_t DNA_SPLICERS = 628;
constexpr uint16_t REVEAL_GLASS = 638;
constexpr uint16_t MAKEUP_BAG = 706;
constexpr uint16_t PRISON_BOTTLE = 765;
constexpr uint16_t ZYGARDE_CUBE = 847;
constexpr uint16_t RED_NECTAR = 853;
constexpr uint16_t YELLOW_NECTAR = 854;
constexpr uint16_t PINK_NECTAR = 855;
constexpr uint16_t PURPLE_NECTAR = 856;
constexpr uint16_t N_SOLARIZER = 943;
constexpr uint16_t N_LUNARIZER = 944;
constexpr uint16_t ROTOM_CATALOG = 1278;
constexpr uint16_t REINS_OF_UNITY = 1590;

// DexIDs
constexpr uint16_t PIKACHU = 25;
constexpr uint16_t ROTOM = 479;
constexpr uint16_t SHAYMIN = 492;
constexpr uint16_t TORNADUS = 641;
constexpr uint16_t THUNDURUS = 642;
constexpr uint16_t RESHIRAM = 643;
constexpr uint16_t ZEKROM = 644;
constexpr uint16_t LANDORUS = 645;
constexpr uint16_t KYUREM = 646;
constexpr uint16_t FURFROU = 676;
constexpr uint16_t ZYGARDE = 718;
constexpr uint16_t HOOPA = 720;
constexpr uint16_t ORICORIO = 741;
constexpr uint16_t SOLGALEO = 791;
constexpr uint16_t LUNALA = 792;
constexpr uint16_t NECROZMA = 800;
constexpr uint16_t GLASTRIER = 896;
constexpr uint16_t SPECTRIER = 897;
constexpr uint16_t CALYREX = 898;

constexpr uint16_t UNOWN = 201; // Testing
constexpr uint16_t KYOGRE = 382;
constexpr uint16_t GROUDON = 383;

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

// Form-change on use items
void ConditionalAdd(List_ZoneID__o * zidl, int32_t flagNo, int32_t item) {
    if (FlagWork::GetFlag(0x530,nullptr))
        zidl->Add(0x54,List_ContextMenuID__Add);
}
bool FormChange(UIBag_o *uib, PokemonPartyItem_o *ppi, bool *fail, uint16_t nextFormID) {
    auto *onComplete = (Action_PokeWalkingFormation_SheetSheet1__o *)
            il2cpp_object_new(Action_PokemonParam__TypeInfo);
    onComplete->ctor((Il2CppObject *)uib, UIBag_ShowFormChangeResult);
    *fail = false;
    return ppi->FormChange(nextFormID, uib->fields.effectRoot, nullptr,
                           (Action_PokemonParam__o *)onComplete, nullptr);
}
void FormChangeClose(UIBag_o *uib, PokemonPartyItem_o *ppi, bool *fail, uint16_t nextFormID) {
    FormChange(uib, ppi, fail, nextFormID);
    uib->Close(uib->fields.super.onClosed, uib->fields.super._prevWindowId, false,
               nullptr);
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
void ForgetMove(UIBag_o *uib, CoreParam_o *cp, int32_t forgetMoveID, int32_t fallbackMoveID, bool *close) {
    EnsureTypeInfoLoaded(&DAT_7104cbd69d, 0x95ab);
    uint8_t wazaIndex = cp->GetWazaIndex(forgetMoveID, nullptr);
    if (wazaIndex == NULL_WAZA_IDX) return;
    *close = false;
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
void LearnMove(UIBag_o *uib, PokemonParam_o *pp, int32_t moveID, bool *close) {
    EnsureTypeInfoLoaded(&DAT_7104cbb9d0, 0x9a20);
    auto *cp = (CoreParam_o *)pp;
    if (cp->GetWazaIndex(moveID, nullptr) != NULL_WAZA_IDX) return;
    *close = false;
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
    auto *uibdc1450 = (UIBag___c__DisplayClass145_0_o *) il2cpp_object_new(UIBag___c__DisplayClass145_0_TypeInfo);
    uibdc1450->ctor(nullptr);
    uibdc1450->fields.pokemonParam = pp;
    system_array_init(&uibdc1450->fields.pokemonParam);
    uibdc1450->fields.__4__this = uib;
    system_array_init(&uibdc1450->fields.__4__this);
    EnsureTypeInfoLoaded(&DAT_7104cbd69e, 0x95ac);
    auto *uibdc1451 = (UIBag___c__DisplayClass145_1_o *) il2cpp_object_new(UIBag___c__DisplayClass145_1_TypeInfo);
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
void ReduceToLearnableMoves(UIBag_o *uib, PokemonParam_o *pp, int32_t fallbackMoveID, bool *close) {
    auto *cp = (CoreParam_o *)pp;
    int32_t dexID = cp->GetMonsNo(nullptr);
    uint16_t formID = cp->GetFormNo(nullptr);
    PersonalSystem::LoadPersonalData(dexID, formID, nullptr);
    PersonalSystem::LoadWazaOboeData(dexID, formID, nullptr);
    uint8_t learnSetSize = PersonalSystem::GetWazaOboeNum(nullptr);
    Array<ItemTable_SheetWazaMachine_o *> *itswms = PmlUse_o::get_Instance((MethodInfo *) nullptr)->fields.itemPrmTotal->fields.WazaMachine;
    uint8_t moveCount = cp->GetWazaCount(nullptr);
    for (int i = 0; i < moveCount; ++i) {
        int32_t moveID = cp->GetWazaNo(i, nullptr);
        if (moveID == NULL_WAZA) continue;
        bool keep = false;
        for (int j = 0; j < MAX_EGG_MOVE_COUNT && !keep; ++j)
            keep = moveID == cp->GetTamagoWazaNo(j, nullptr);
        for (int j = 0; j < learnSetSize && !keep; ++j)
            keep = moveID == PersonalSystem::GetWazaOboeWazaNo(j, nullptr);
        for (int j = 0; j < itswms->max_length && !keep; ++j) {
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
        LearnMove(uib, pp, fallbackMoveID, close);
}
extern bool DAT_7104cbb9cf;
extern String_o *StringLiteral_11712;
extern String_o *StringLiteral_11693;
void Dpr_UI_UIBag_UseFormChangeItem(UIBag_o *__this, PokemonPartyItem_o *pokemonPartyItem, ItemInfo_o *itemInfo, MethodInfo *method) {
    EnsureTypeInfoLoaded(&DAT_7104cbb9cf, 0x9a2e);
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
    bool fail = true;
    if (itemID == ROTOM_CATALOG && dexID == ROTOM) {
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
    uint16_t formID = cp->GetFormNo(nullptr);
    if (itemID == GRACIDEA) {
        EnsureClassInit(GameManager_TypeInfo);
        if (dexID == SHAYMIN && formID == 0 &&
        GameManager::get_currentPeriodOfDay(nullptr) - 3 > 1 && cp->GetSick(nullptr) != 3)
            if (FormChange(__this, pokemonPartyItem, &fail, 1))
                __this->fields.isWaitUpdate = true;
    } else if (MAKEUP_BAG_ENABLED && itemID == MAKEUP_BAG) {
        if (dexID == PIKACHU && formID >= 1 && formID < 7) {
            uint16_t nextFormID = formID % 6 + 1;
            FormChange(__this, pokemonPartyItem, &fail, nextFormID);
            bool close = true;
            switch (nextFormID) {
                case 1:
                    ForgetMove(__this, cp, FLYING_PRESS, THUNDER_SHOCK, &close);
                    break;
                case 2:
                    LearnMove(__this, pp, METEOR_MASH, &close);
                    break;
                case 3:
                    RemoveMove(cp, METEOR_MASH);
                    LearnMove(__this, pp, ICICLE_CRASH, &close);
                    break;
                case 4:
                    RemoveMove(cp, ICICLE_CRASH);
                    LearnMove(__this, pp, DRAINING_KISS, &close);
                    break;
                case 5:
                    RemoveMove(cp, DRAINING_KISS);
                    LearnMove(__this, pp, ELECTRIC_TERRAIN, &close);
                    break;
                case 6:
                    RemoveMove(cp, ELECTRIC_TERRAIN);
                    LearnMove(__this, pp, FLYING_PRESS, &close);
                    break;
                default: break;
            }
            if (close)
                __this->Close(__this->fields.super.onClosed, __this->fields.super._prevWindowId,
                              false, nullptr);
        } else if (dexID == FURFROU)
            FormChangeClose(__this, pokemonPartyItem, &fail, (formID + 1) % 10);
    } else if ((itemID == REVEAL_GLASS && (dexID == TORNADUS || dexID == THUNDURUS || dexID == LANDORUS)) ||
            (itemID == PRISON_BOTTLE && dexID == HOOPA))
        FormChangeClose(__this, pokemonPartyItem, &fail, (formID + 1) % 2);
    else if (itemID == DNA_SPLICERS && dexID == KYUREM) {
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
            FormChange(__this, pokemonPartyItem, &fail, nextFormID);
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
            __this->Close(__this->fields.super.onClosed, __this->fields.super._prevWindowId,
                          false, nullptr);
        }
    } else if (itemID == ZYGARDE_CUBE && dexID == ZYGARDE && formID < 4)
        FormChangeClose(__this, pokemonPartyItem, &fail, (formID + 1) % 4);
    else if (dexID == ORICORIO) {
        if (itemID == RED_NECTAR && formID != 0)
            FormChangeClose(__this, pokemonPartyItem, &fail, 0);
        else if (itemID == YELLOW_NECTAR && formID != 1)
            FormChangeClose(__this, pokemonPartyItem, &fail, 1);
        else if (itemID == PINK_NECTAR && formID != 2)
            FormChangeClose(__this, pokemonPartyItem, &fail, 2);
        else if (itemID == PURPLE_NECTAR && formID != 3)
            FormChangeClose(__this, pokemonPartyItem, &fail, 3);
        if (!fail)
            ItemWork::SubItem(itemID, 1, nullptr);
    } else if (dexID == NECROZMA) {
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
            FormChange(__this, pokemonPartyItem, &fail, nextFormID);
            bool close = true;
            switch (nextFormID) {
                case 0:
                    ForgetMove(__this, cp, SUNSTEEL_STRIKE, CONFUSION, &close);
                    ForgetMove(__this, cp, MOONGEIST_BEAM, CONFUSION, &close);
                    break;
                case 1:
                    LearnMove(__this, pp, SUNSTEEL_STRIKE, &close);
                    break;
                case 2:
                    LearnMove(__this, pp, MOONGEIST_BEAM, &close);
                    break;
                default: break;
            }
            if (close)
                __this->Close(__this->fields.super.onClosed, __this->fields.super._prevWindowId,
                              false, nullptr);
        }
    } else if (itemID == REINS_OF_UNITY && dexID == CALYREX) {
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
            FormChange(__this, pokemonPartyItem, &fail, nextFormID);
            bool close = true;
            switch (nextFormID) {
                case 0:
                    ReduceToLearnableMoves(__this, pp, CONFUSION, &close);
                    break;
                case 1:
                    LearnMove(__this, pp, GLACIAL_LANCE, &close);
                    break;
                case 2:
                    LearnMove(__this, pp, ASTRAL_BARRAGE, &close);
                    break;
                default: break;
            }
            if (close)
                __this->Close(__this->fields.super.onClosed, __this->fields.super._prevWindowId,
                          false, nullptr);
        }
    }
    if (!fail) return;
    auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
    onCloseWindow->ctor((Il2CppObject *)__this, UIBag_EndSelectPokemonParty);
    uimwc->OpenMsgWindow(0, StringLiteral_11693, true, false, nullptr, onCloseWindow, nullptr);
}