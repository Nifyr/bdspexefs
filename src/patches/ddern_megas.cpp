#include "Dpr/Battle/Logic/ActionDesc.hpp"
#include "Dpr/Battle/Logic/BtlEscapeMode.hpp"
#include "Dpr/Battle/Logic/BtlStrType.hpp"
#include "Dpr/Battle/Logic/ContFlag.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/InterruptCode.hpp"
#include "Dpr/Battle/Logic/PokeActionCategory.hpp"
#include "Dpr/Battle/Logic/PokeSet.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_CheckSpecialWazaAdditionalEffectOccur.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_FormChange.hpp"
#include "Dpr/Battle/Logic/Section_InterruptAction.hpp"
#include "Dpr/Battle/Logic/Section_ProcessActionCore.hpp"
#include "Pml/WazaData/WazaSick.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;
using namespace Pml::PokePara;
using namespace Pml::WazaData;

// DexIDs
constexpr uint16_t ALAKAZAM = 65;
constexpr uint16_t AMPHAROS = 181;
constexpr uint16_t MILOTIC = 350;
constexpr uint16_t GARCHOMP = 445;
constexpr uint16_t GALLADE = 475;

void FormChange(Section_ProcessActionCore_o *spac, uint8_t pokeID, uint8_t formID) {
    auto * desc = (Section_FromEvent_FormChange_Description_o *)
            il2cpp_object_new(Section_FromEvent_FormChange_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.formNo = formID;
    desc->fields.isDontResetFormByOut = true;
    desc->fields.isDisplayTokuseiWindow = false;
    desc->fields.isDisplayChangeEffect = true;
    desc->fields.successMessage->Setup(BtlStrType::BTL_STRTYPE_SET, 304, nullptr);
    desc->fields.successMessage->AddArg(pokeID, nullptr);
    auto * result = (Section_FromEvent_FormChange_Result_o *)
            il2cpp_object_new(Section_FromEvent_FormChange_Result_TypeInfo);
    result->ctor(nullptr);
    spac->fields.super.m_pSectionContainer->fields.m_section_FromEvent_FormChange->
            Execute(result, &desc, nullptr);
}

void Dpr_Battle_Logic_Section_ProcessActionCore_Execute_0(Section_ProcessActionCore_o *spac,
                                                          Section_ProcessActionCore_Result_o *pResult,
                                                          Section_ProcessActionCore_Description_o **description,
                                                          MethodInfo *method) {
    system_load_typeinfo((void *)0x2c56);
    system_load_typeinfo((void *)0x88fe);
    PokeAction_o *pa = (*description)->fields.pokeAction;
    if (pa->fields.fDone) return;
    pa->fields.fDone = true;
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
    uint16_t dexID = bpp->GetMonsNo(nullptr);
    uint8_t formID = bpp->fields.m_formNo;
    if (((dexID == MILOTIC || dexID == GARCHOMP) && formID == 0) || dexID == GALLADE) {
        FormChange(spac, pokeID, 1);
    }
    if ((dexID == AMPHAROS || dexID == ALAKAZAM) && formID == 2) {
        FormChange(spac, pokeID, 3);
    }
    spac->action(pa, nullptr);
    if (pac < 3) {
        bpp->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_ACTION_DONE, nullptr);
        scp->SetContFlag(bpp,ContFlag::CONTFLG_ACTION_DONE, nullptr);
    }
    if (spac->fields.super.m_pSharedData->fields.m_interruptAccessor->IsRequested(InterruptCode::QUIT_ESCAPE,
                                                                                  nullptr)) return;
    el->Event_ActProcEnd(bpp, pac, nullptr);
}