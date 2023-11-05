#include "Pml/PokePara/CoreParam.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Pml::PokePara;

// DexIDs
constexpr uint16_t XERNEAS = 716;
constexpr uint16_t ZACIAN = 888;
constexpr uint16_t ZAMAZENTA = 889;

// ItemIDs
constexpr uint16_t RUSTED_SWORD = 1103;
constexpr uint16_t RUSTED_SHIELD = 1104;

// MoveIDs
constexpr int32_t IRON_HEAD = 442;
constexpr int32_t BEHEMOTH_BLADE = 781;
constexpr int32_t BEHEMOTH_BASH = 782;

// WazaIdxIDs
constexpr uint8_t NULL_WAZA_IDX = 4;

void Dpr_Battle_Logic_POKECON_setupPokeParam(POKECON_o *__this, BTL_POKEPARAM_o *pokeParam, uint8_t pokeID,
                                             PokemonParam_o *srcParam, DefaultPowerUpDesc_o **defaultPowerUpDesc,
                                             MyStatus_o *playerData, MethodInfo *method) {
    __this->setupPokeParam(pokeParam, pokeID, srcParam, defaultPowerUpDesc, playerData, nullptr);
    auto *cp = (CoreParam_o *)pokeParam->fields.m_coreParam->fields.ppSrc;
    bool fastModeStarted = cp->StartFastMode(nullptr);
    uint16_t dexID = pokeParam->GetMonsNo(nullptr);
    uint16_t formID = pokeParam->fields.m_formNo;
    uint16_t itemID = pokeParam->GetItem(nullptr);
    if (dexID == XERNEAS && formID == 0) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
    }
    if (dexID == ZACIAN && formID == 0 && itemID == RUSTED_SWORD) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
        uint8_t wazaIdx = pokeParam->WAZA_SearchIdx(IRON_HEAD, nullptr);
        if (wazaIdx != NULL_WAZA_IDX)
            pokeParam->WAZA_UpdateID(wazaIdx, BEHEMOTH_BLADE, 0, false, nullptr);
    }
    if (dexID == ZAMAZENTA && formID == 0 && itemID == RUSTED_SHIELD) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
        uint8_t wazaIdx = pokeParam->WAZA_SearchIdx(IRON_HEAD, nullptr);
        if (wazaIdx != NULL_WAZA_IDX)
            pokeParam->WAZA_UpdateID(wazaIdx, BEHEMOTH_BASH, 0, false, nullptr);
    }
    cp->EndFastMode(fastModeStarted, nullptr);
}