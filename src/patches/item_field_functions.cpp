#include "ContextMenuID.hpp"
#include "Dpr/Item/ItemInfo.hpp"
#include "Dpr/UI/PokemonPartyItem.hpp"
#include "Dpr/UI/UIBag.hpp"
#include "FlagWork.hpp"
#include "GameManager.hpp"
#include "Pml/PokePara/CoreParam.hpp"
#include "Pml/PokePara/PokemonParam.hpp"
#include "System/Action.hpp"
#include "System/Collections/Generic/List.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "util.hpp"

using namespace Dpr::Item;
using namespace Dpr::UI;
using namespace Pml::PokePara;
using namespace System;
using namespace System::Collections::Generic;

// ItemIDs
constexpr uint16_t GRACIDEA = 466;
constexpr uint16_t REVEAL_GLASS = 638;
constexpr uint16_t ROTOM_CATALOG = 1278;

// DexIDs
constexpr uint16_t ROTOM = 479;
constexpr uint16_t SHAYMIN = 492;
constexpr uint16_t TORNADUS = 641;
constexpr uint16_t THUNDURUS = 642;
constexpr uint16_t LANDORUS = 645;

// Reveal Glass
void ConditionalAdd(List_ZoneID__o * zidl, int32_t flagNo, int32_t item) {
    if (FlagWork::GetFlag(0x530,nullptr))
        zidl->Add(0x54,List_ContextMenuID__Add);
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
    Pml::PokePara::PokemonParam_o *pp = pokemonPartyItem->fields._param->fields.pokemonParam;
    uibdc1440->fields.pokemonParam = pp;
    system_array_init(&uibdc1440->fields.pokemonParam);
    int32_t itemID = itemInfo->get_Id(nullptr);
    CoreParam_o *cp = (CoreParam_o *)pp;
    UIMsgWindowController_o *uimwc = __this->fields.msgWindowController;
    int32_t dexID = cp->GetMonsNo(nullptr);
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
        GameManager::get_currentPeriodOfDay(nullptr) - 3 > 1 && cp->GetSick(nullptr) != 3) {
            auto *onComplete = (Action_PokeWalkingFormation_SheetSheet1__o *)
                    il2cpp_object_new(Action_PokemonParam__TypeInfo);
            onComplete->ctor((Il2CppObject *)__this, UIBag_ShowFormChangeResult);
            if (pokemonPartyItem->FormChange(1, __this->fields.effectRoot, nullptr,
                                             (Action_PokemonParam__o *)onComplete, nullptr))
                __this->fields.isWaitUpdate = true;
            return;
        }
    }
    if (itemID == REVEAL_GLASS && (dexID == TORNADUS || dexID == THUNDURUS || dexID == LANDORUS)) {
        auto *onComplete = (Action_PokeWalkingFormation_SheetSheet1__o *)
                il2cpp_object_new(Action_PokemonParam__TypeInfo);
        onComplete->ctor((Il2CppObject *)__this, UIBag_ShowFormChangeResult);
        if (pokemonPartyItem->FormChange(1 - formID, __this->fields.effectRoot, nullptr,
                                         (Action_PokemonParam__o *)onComplete, nullptr))
            __this->fields.isWaitUpdate = true;
        __this->Close(__this->fields.super.onClosed, (__this->fields).super._prevWindowId,
                      '\x01', nullptr);
        return;
    }
    auto *onCloseWindow = (Action_o *)il2cpp_object_new(Action_TypeInfo);
    onCloseWindow->ctor((Il2CppObject *)__this, UIBag_EndSelectPokemonParty);
    uimwc->OpenMsgWindow(0, StringLiteral_11693, true, false, nullptr, onCloseWindow, nullptr);
}