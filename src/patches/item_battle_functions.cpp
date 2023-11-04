#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/MainModule.hpp"
#include "Dpr/Battle/Logic/Section_UseItem_Core.hpp"
#include "ItemUseConst.hpp"
#include "Pml/Item/ItemData.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Pml::Item;

// ItemIDs
constexpr uint16_t ADRENALIN_ORB = 846;

// Flutes
extern bool DAT_7104cc09ba;
void Dpr_Battle_Logic_Section_UseItem_Core_Execute(Section_UseItem_Core_o *__this,
                                                   Section_UseItem_Core_Result_o *pResult,
                                                   Section_UseItem_Core_Description_o **description,
                                                   MethodInfo *method) {
    EnsureTypeInfoLoaded(&DAT_7104cc09ba, 0x791b);
    pResult->fields.useResult = 0;
    pResult->fields.isConsumed = false;
    pResult->fields.isUsedBall = false;
    EnsureClassInit(MainModule_TypeInfo);
    uint8_t targetArea = 0;
    uint8_t targetPos = 0;
    Section_UseItem_Core_Description_o *suicd = *description;
    BTL_POKEPARAM_o *target = __this->getTaragetInfo(&targetArea, &targetPos,
                                                     suicd->fields.targetID, nullptr);
    BTL_POKEPARAM_o *poke = suicd->fields.poke;
    uint16_t itemID = suicd->fields.itemID;
    ServerCommandPutter_o *scp = __this->fields.super.m_pServerCmdPutter;
    scp->Message_Std(0x23, MainModule::PokeIDtoClientID(poke->GetID(nullptr), nullptr),
                     itemID, nullptr);
    if (itemID == ADRENALIN_ORB) {
        scp->Message_Std(0x51, nullptr);
        pResult->fields.useResult = 0;
        return;
    }
    EnsureClassInit(Calc_TypeInfo);
    if (Calc::ITEM_IsBall(itemID, nullptr)) {
        bool isUsed = 0;
        bool isCaptured = 0;
        __this->useBall(poke, itemID, &isUsed, &isCaptured,
                        suicd->fields.capContext, nullptr);
        pResult->fields.useResult = isCaptured << 1;
        pResult->fields.isConsumed = isUsed;
        pResult->fields.isUsedBall = true;
        return;
    }
    EnsureClassInit(ItemUseConst_TypeInfo);
    if (Calc::ITEM_GetParam(itemID, ItemData_PrmID::B_FUNC, nullptr) ==
    ItemUseConst_TypeInfo->static_fields->ITEMUSE_BTL_ESCAPE) {
        if (((Section_o *)__this)->GetRule(nullptr) != 2) {
            pResult->fields.useResult = 1;
            pResult->fields.isConsumed = true;
            return;
        }
        scp->Message_Std(0x51, nullptr);
        pResult->fields.useResult = 0;
        return;
    }
    if (!__this->canUseItem(itemID, targetArea, targetPos, nullptr)) {
        scp->Message_Std(0xdb, nullptr);
        pResult->fields.useResult = 0;
        return;
    }
    uint16_t cmd = 0xa1;
    if (targetPos != 5)
        cmd = 0xa2;
    ServerCommandQueue_o *scq = __this->fields.super.m_pServerCmdQueue;
    uint16_t pos = scq->ReservePutPos(cmd, nullptr);
    Section_UseItem_Core_ItemEffectInfo_array *seicieis = __this->get_s_itemEffectTable(nullptr);
    if (seicieis->max_length <= 0) {
        scp->Message_Std(0x51, nullptr);
        pResult->fields.useResult = 0;
        return;
    }
    bool effectSuccess = false;
    for (uint32_t i = 0; i < seicieis->max_length; ++i) {
        Section_UseItem_Core_ItemEffectInfo_o *suiciei = seicieis->m_Items[i];
        int32_t itemParam = Calc::ITEM_GetParam(itemID, suiciei->fields.effect,nullptr);
        if (itemParam == 0) continue;
        effectSuccess |= suiciei->fields.func->Invoke(target, itemID, itemParam, suicd->fields.actParam,
                                                      nullptr);
    }
    if (!effectSuccess) {
        scp->Message_Std(0x51, nullptr);
        pResult->fields.useResult = 0;
        return;
    }
    int32_t legacyParam = 0xf;
    if (targetPos != 5)
        legacyParam = 3;
    System_Int32_array *legacyParamArray;
    if (targetPos == 5) {
        legacyParamArray = (System_Int32_array *)system_array_new(System_Int32_array_TypeInfo, 1);
        legacyParamArray->m_Items[0] = legacyParam;
    }
    else {
        legacyParamArray = (System_Int32_array *)system_array_new(System_Int32_array_TypeInfo,2);
        legacyParamArray->m_Items[0] = targetPos;
        legacyParamArray->m_Items[1] = legacyParam;
    }
    scq->Put_ToReservedPos(pos, cmd, legacyParamArray, nullptr);
    pResult->fields.isConsumed = Calc::ITEM_GetParam(itemID, ItemData_PrmID::USE_SPEND, nullptr) ==
            0;
    __this->fields.super.m_pMainModule->CalcNatsukiItemUse(target, itemID, nullptr);
    pResult->fields.useResult = 0;
    return;
}