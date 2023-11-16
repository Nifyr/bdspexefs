#include "il2cpp.hpp"

#include "BATTLE_SETUP_PARAM.hpp"
#include "Dpr/BallDeco.hpp"
#include "System/Collections/IEnumerator.hpp"

using namespace System::Collections;

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct MainModule_RGCTXs;

            struct MainModule_VTable {
                VirtualInvokeData _0_Equals;
                VirtualInvokeData _1_Finalize;
                VirtualInvokeData _2_GetHashCode;
                VirtualInvokeData _3_ToString;
            };

            struct MainModule_c {
                Il2CppClass_1 _1;
                struct Dpr_Battle_Logic_MainModule_StaticFields* static_fields;
                MainModule_RGCTXs* rgctx_data;
                Il2CppClass_2 _2;
                MainModule_VTable vtable;
            };
            
            struct MainModule_Fields {
                struct Dpr_Battle_Logic_BATTLE_SETUP_PARAM_o* m_setupParam;
                struct Dpr_Battle_Logic_BattleViewBase_o* m_viewCore;
                struct Dpr_Battle_Logic_Random_o* m_randSys;
                uint64_t m_randomSeed;
                struct Dpr_Battle_Logic_MainModule_pSubProc_o* m_subProc;
                int32_t m_subSeq;
                int32_t m_setupStep;
                struct Dpr_Battle_Logic_MainModule_pMainProc_o* m_mainLoop;
                struct Pml_PokeParty_array* m_srcParty;
                struct Pml_PokeParty_array* m_srcPartyForServer;
                struct Pml_PokeParty_o* m_tmpParty;
                struct Dpr_Battle_Logic_MyStatus_o* m_playerStatus;
                struct System_Boolean_array* m_fClientQuit;
                int32_t m_rule;
                uint32_t m_regularMoney;
                uint32_t m_bonusMoney;
                uint32_t m_loseMoney;
                int32_t m_msgSpeed;
                uint16_t m_LimitTimeGame;
                uint16_t m_LimitTimeClient;
                uint16_t m_LimitTimeCommand;
                int32_t m_serverResult;
                int32_t m_serverResultCause;
                uint8_t m_myClientID;
                uint8_t m_myOrgPos;
                int32_t m_changeMode;
                uint8_t m_MultiAIDataSeq;
                uint8_t m_MultiAIClientNum;
                struct System_Byte_array* m_MultiAIClientID;
                bool m_fCommError;
                bool m_fCommErrorMainQuit;
                bool m_fWazaEffectEnable;
                bool m_fGetMoneyFixed;
                bool m_fLoseMoneyFixed;
                bool m_padding;
                bool m_isFinalizeStarted;
                struct Dpr_Battle_Logic_BTL_SERVER_o* m_server;
                struct Dpr_Battle_Logic_BTL_SERVER_o* m_cmdCheckServer;
                struct Dpr_Battle_Logic_BTL_CLIENT_array* m_client;
                struct Dpr_Battle_Logic_BTL_CLIENT_array* m_dummyClient;
                struct Dpr_Battle_Logic_TRAINER_DATA_array* m_trainerParam;
                struct Dpr_Battle_Logic_ClientPublicInformation_array* m_clientPublicInformation;
                struct Dpr_Battle_Logic_AdapterFactory_o* m_adapterFactory;
                struct Dpr_Battle_Logic_rec_Reader_o* m_recReader;
                struct System_Boolean_array* m_moneyDblUpCause;
                struct System_Collections_Generic_Dictionary_uint__uint__o* m_zukanDataOnBattleStart;
                struct Dpr_Battle_Logic_PokeIDRec_o* m_deadPokeIDRec;
                struct Dpr_Battle_Logic_BattleEnv_o* m_battleEnvForClient;
                struct Dpr_Battle_Logic_BattleEnv_o* m_battleEnvForServer;
                struct Dpr_Battle_Logic_Net_Client_o* m_iPtrNetClient;
                bool isInitialized;
                bool isFinalized;
                struct Dpr::BallDeco::CapsuleData_o DummyCapsuleData;
            };
            
            struct MainModule_o {
                MainModule_c *klass;
                void *monitor;
                MainModule_Fields fields;

                void CalcNatsukiItemUse(BTL_POKEPARAM_o *bpp, uint16_t itemNo, MethodInfo *method);
                IEnumerator_o * FinalizeCoroutine(MethodInfo *method);
                int32_t GetClientSide(uint8_t clientID, MethodInfo *method);
                int32_t GetEscapeMode(MethodInfo *method);
                IEnumerator_o * LeavenOnErrorCoroutine(MethodInfo *method);
                bool IsFriendPokeID(uint8_t pokeID1, uint8_t pokeID2, MethodInfo *method);
                bool IsSkyBattle(MethodInfo *method);
                void RegisterZukanSeeFlag(BTL_POKEPARAM_o *bpp, MethodInfo *method);
                void setSrcPartyToBattleEnv(BattleEnv_o *battleEnv, uint8_t clientID, bool forServer, MethodInfo *method);
                void setSubProcForSetup(BATTLE_SETUP_PARAM_o *setup_param, MethodInfo *method);
                void setup_raid_srcParty(MethodInfo *method);
                void setup_raid_trainerParam(MethodInfo *method);
                void setup_raid_boss(BattleEnv_o *env, MethodInfo *method);
            };

            struct MainModule {
                static uint8_t PokeIDtoClientID(uint8_t pokeID, MethodInfo *method);
            };

            extern void *MainModule_TypeInfo;
        }
    }
}