#include "Pml/PokePara/CoreParam.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "logger.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Pml::PokePara;

// DexIDs
constexpr uint16_t XERNEAS = 716;
constexpr uint16_t GROUDON = 383;

void Dpr_Battle_Logic_POKECON_setupPokeParam(POKECON_o *__this, BTL_POKEPARAM_o *pokeParam, uint8_t pokeID,
                                             PokemonParam_o *srcParam, DefaultPowerUpDesc_o **defaultPowerUpDesc,
                                             MyStatus_o *playerData, MethodInfo *method) {
    __this->setupPokeParam(pokeParam, pokeID, srcParam, defaultPowerUpDesc, playerData, nullptr);
    auto *cp = (CoreParam_o *)pokeParam->fields.m_coreParam->fields.ppSrc;
    bool fastModeStarted = cp->StartFastMode(nullptr);
    if (pokeParam->GetMonsNo(nullptr) == GROUDON && pokeParam->fields.m_formNo == 0) {
        pokeParam->ChangeForm(1, true, nullptr);
        pokeParam->fields.m_tokusei = cp->GetTokuseiNo(nullptr);
    }
    cp->EndFastMode(fastModeStarted, nullptr);
}