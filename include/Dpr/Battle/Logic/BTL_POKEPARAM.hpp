#pragma once

#include "il2cpp.hpp"
#include "BTL_SICKCONT.hpp"
#include "Pml/PokePara/CoreParam.h"
#include "Pml/PokePara/PokemonParam.hpp"
#include "PokeTypePair.hpp"
#include "System/Array.hpp"

using namespace Pml::PokePara;

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BTL_POKEPARAM_CORE_PARAM_c;

            struct BTL_POKEPARAM_GModeParam_c;

            struct BTL_POKEPARAM_GModeParam_Fields {
                bool isGMode;
                uint8_t passedTurnCount;
            };

            struct BTL_POKEPARAM_GModeParam_o {
                BTL_POKEPARAM_GModeParam_c *klass;
                void *monitor;
                BTL_POKEPARAM_GModeParam_Fields fields;
            };

            struct BTL_POKEPARAM_CORE_PARAM_Fields {
                PokemonParam_o* ppSrc;
                uint32_t personalRand;
                uint32_t exp;
                uint16_t monsno;
                uint16_t formno;
                uint16_t hpMax;
                uint16_t hp;
                uint16_t item;
                uint16_t usedItem;
                uint16_t defaultTokusei;
                uint8_t level;
                uint8_t myID;
                uint8_t mons_pow;
                uint8_t mons_agility;
                uint8_t seikaku;
                uint8_t native_talent_hp;
                uint8_t native_talent_atk;
                uint8_t native_talent_def;
                uint8_t native_talent_spatk;
                uint8_t native_talent_spdef;
                uint8_t native_talent_agi;
                uint16_t defaultFormNo;
                bool fHensin;
                bool fFakeEnable;
                bool fBtlIn;
                bool fDontResetFormByByOut;
                bool fForceGEnable;
                struct BTL_SICKCONT_array* sickCont;
                struct System_Byte_array* wazaSickCounter;
                uint8_t confrontRecCount;
                struct System_Byte_array* confrontRec;
                uint16_t totalTurnCount;
                uint8_t fakeViewTargetPokeId;
                struct DefaultPowerUpDesc_o* defaultPowerUpDesc;
                uint8_t deadCause;
                uint8_t deadCausePokeID;
                uint8_t killCount;
                bool isRaidBoss;
                struct RaidBossParam_o* raidBossParam;
                struct BTL_POKEPARAM_GModeParam_o* gParam;
            };

            struct BTL_POKEPARAM_CORE_PARAM_o {
                BTL_POKEPARAM_CORE_PARAM_c *klass;
                void *monitor;
                BTL_POKEPARAM_CORE_PARAM_Fields fields;
            };

            struct BTL_POKEPARAM_BASE_PARAM_o;

            struct BTL_POKEPARAM_VARIABLE_PARAM_c;

            struct BTL_POKEPARAM_VARIABLE_PARAM_Fields {
                int8_t attack;
                int8_t defence;
                int8_t sp_attack;
                int8_t sp_defence;
                int8_t agility;
                int8_t hit;
                int8_t avoid;
            };

            struct BTL_POKEPARAM_VARIABLE_PARAM_o {
                BTL_POKEPARAM_VARIABLE_PARAM_c *klass;
                void *monitor;
                BTL_POKEPARAM_VARIABLE_PARAM_Fields fields;
            };

            struct BTL_POKEPARAM_DORYOKU_PARAM_o;
            struct BTL_POKEPARAM_WAZA_SET_array;
            struct BTL_POKEPARAM_WAZADMG_REC_array_array;
            struct FieldStatus_o;

            struct BTL_POKEPARAM_Fields {
                BTL_POKEPARAM_CORE_PARAM_o* m_coreParam;
                BTL_POKEPARAM_BASE_PARAM_o* m_baseParam;
                BTL_POKEPARAM_VARIABLE_PARAM_o* m_varyParam;
                BTL_POKEPARAM_DORYOKU_PARAM_o* m_doryokuParam;
                BTL_POKEPARAM_WAZA_SET_array* m_waza;
                uint16_t m_tokusei;
                uint16_t m_weight;
                uint8_t m_wazaCnt;
                uint8_t m_formNo;
                uint8_t m_friendship;
                uint8_t m_criticalRank;
                uint8_t m_usedWazaCount;
                uint8_t m_prevWazaType;
                uint8_t m_spActPriority;
                uint16_t m_turnCount;
                uint16_t m_appearedTurn;
                uint16_t m_wazaContCounter;
                uint8_t m_prevTargetPos;
                int32_t m_prevActWazaID;
                int32_t m_prevSelectWazaID;
                int32_t m_prevDamagedWaza;
                System::Array<uint8_t> * m_turnFlag;
                System::Array<uint8_t> * m_contFlag;
                System::Array<uint8_t> * m_permFlag;
                System::Array<uint8_t> * m_counter;
                System::Array<uint32_t> * m_permCounter;
                BTL_POKEPARAM_WAZADMG_REC_array_array* m_wazaDamageRec;
                System::Array<uint8_t> * m_dmgrecCount;
                uint8_t m_dmgrecTurnPtr;
                uint8_t m_dmgrecPtr;
                uint16_t m_migawariHP;
                int32_t m_combiWazaID;
                uint8_t m_combiPokeID;
                FieldStatus_o* m_fldSim;
            };

            struct BTL_POKEPARAM_c;

            struct BTL_POKEPARAM_o
            {
                BTL_POKEPARAM_c *klass;
                void *monitor;
                BTL_POKEPARAM_Fields fields;

                void ChangeForm(uint8_t formNo, bool dontResetFormByOut, MethodInfo *method);
                bool CheckNemuri(int32_t checkMode, MethodInfo *method);
                bool CheckSick(int32_t sickType,MethodInfo *method);
                bool CONFRONT_REC_IsMatch(uint8_t pokeID, MethodInfo *method);
                void correctMaxHP(MethodInfo *method);
                uint8_t COUNTER_Get(int32_t cnt, MethodInfo *method);
                uint8_t GetFriendship(MethodInfo *method);
                uint8_t GetID(MethodInfo *method);
                uint16_t GetItem(MethodInfo *method);
                uint16_t GetItemEffective(FieldStatus_o **fldSim, MethodInfo *method);
                uint16_t GetMonsNo(MethodInfo *method);
                uint32_t GetPokeSick(MethodInfo *method);
                PokeTypePair_o GetPokeType(MethodInfo *method);
                BTL_SICKCONT_o GetSickCont(int32_t sick, MethodInfo *method);
                uint16_t GetSickParam(int32_t sick, MethodInfo *method);
                Pml::PokePara::CoreParam * GetSrcDataConst(MethodInfo *method);
                int32_t GetValue(int32_t valueID,MethodInfo *method);
                bool HENSIN_Check(MethodInfo *method);
                bool IsDead(MethodInfo *method);
                bool IsGMode(MethodInfo *method);
                bool IsMatchTokusei(int32_t tokusei, MethodInfo *method);
                bool IsMatchType(uint8_t type,MethodInfo *method);
                bool PERMFLAG_Get(int32_t flagID, MethodInfo *method);
                void setupBySrcDataBase(bool fTypeUpdate, bool fParamUpdate, bool isGMode, MethodInfo *method);
                bool TURNFLAG_Get(int32_t flagID, MethodInfo *method);
                void TURNFLAG_Set(int32_t flagID, MethodInfo *method);
                int32_t WAZA_GetID(uint8_t idx, MethodInfo *method);
                uint16_t WAZA_GetPP(uint8_t wazaIdx, MethodInfo *method);
                bool WAZA_IsUsable(int32_t waza, MethodInfo *method);
                uint8_t WAZA_SearchIdx(int32_t waza, MethodInfo *method);
                void WAZA_UpdateID(uint8_t wazaIdx, int32_t waza, uint8_t ppMax, bool fPermenent, MethodInfo *method);
            };

            namespace BTL_POKEPARAM_ValueID
            {
                enum BTL_POKEPARAM_ValueID {
                    BPP_VALUE_NULL,
                    BPP_ATTACK_RANK,
                    BPP_DEFENCE_RANK,
                    BPP_SP_ATTACK_RANK,
                    BPP_SP_DEFENCE_RANK,
                    BPP_AGILITY_RANK,
                    BPP_HIT_RATIO,
                    BPP_AVOID_RATIO,
                    BPP_ATTACK,
                    BPP_DEFENCE,
                    BPP_SP_ATTACK,
                    BPP_SP_DEFENCE,
                    BPP_AGILITY,
                    BPP_HP,
                    BPP_HP_BEFORE_G,
                    BPP_MAX_HP,
                    BPP_MAX_HP_BEFORE_G,
                    BPP_LEVEL,
                    BPP_TOKUSEI,
                    BPP_TOKUSEI_EFFECTIVE,
                    BPP_SEX,
                    BPP_SEIKAKU,
                    BPP_PERSONAL_RAND,
                    BPP_EXP,
                    BPP_MONS_POW,
                    BPP_MONS_AGILITY,
                    BPP_RANKVALUE_START = 1,
                    BPP_RANKVALUE_END = 7,
                    BPP_RANKVALUE_RANGE = 7
                };
            }

            namespace BTL_POKEPARAM_TurnFlag
            {
                enum BTL_POKEPARAM_TurnFlag {
                    TURNFLG_ACTION_START,
                    TURNFLG_ACTION_DONE,
                    TURNFLG_DAMAGED,
                    TURNFLG_WAZAPROC_DONE,
                    TURNFLG_SHRINK,
                    TURNFLG_KIAI_READY,
                    TURNFLG_KIAI_SHRINK,
                    TURNFLG_MAMORU,
                    TURNFLG_ITEM_CONSUMED,
                    TURNFLG_ITEM_CANT_USE,
                    TURNFLG_COMBIWAZA_READY,
                    TURNFLG_TAMEHIDE_OFF,
                    TURNFLG_MOVED,
                    TURNFLG_TURNCHECK_SICK_PASSED,
                    TURNFLG_HITRATIO_UP,
                    TURNFLG_NAGETUKERU_USING,
                    TURNFLG_MAMORU_ONLY_DAMAGE_WAZA,
                    TURNFLG_RESERVE_ITEM_SPEND,
                    TURNFLG_APPEARED_BY_POKECHANGE,
                    TURNFLG_CANT_ACTION,
                    TURNFLG_TRAPPSHELL_READY,
                    TURNFLG_GWALL_BROKEN,
                    TURNFLG_RAIDBOSS_REINFORCE_DONE,
                    TURNFLG_RAIDBOSS_ANGRY,
                    TURNFLG_RAIDBOSS_ANGRY_WAZA_ADD_DONE,
                    TURNFLG_RANK_UP,
                    TURNFLG_RANK_DOWN,
                    TURNFLG_MAX
                };
            }

            namespace BTL_POKEPARAM_NemuriCheckMode
            {
                enum BTL_POKEPARAM_NemuriCheckMode
                {
                    NEMURI_CHECK_ONLY_SICK,
                    NEMURI_CHECK_INCLUDE_ZETTAINEMURI
                };
            }

            namespace BTL_POKEPARAM_Counter
            {
                enum BTL_POKEPARAM_Counter
                {
                    COUNTER_TAKUWAERU,
                    COUNTER_TAKUWAERU_DEF,
                    COUNTER_TAKUWAERU_SPDEF,
                    COUNTER_MAMORU,
                    COUNTER_FREEFALL,
                    COUNTER_TURN_FROM_GWALL_BROKEN,
                    COUNTER_MAX
                };
            }

            namespace BTL_POKEPARAM_ExTypeCause
            {
                enum BTL_POKEPARAM_ExTypeCause
                {
                    EXTYPE_CAUSE_NONE,
                    EXTYPE_CAUSE_HALLOWEEN,
                    EXTYPE_CAUSE_MORINONOROI
                };
            }
        }
    }
}