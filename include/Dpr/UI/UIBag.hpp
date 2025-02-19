#include "il2cpp.hpp"
#include "System/Array.hpp"

#include "ContextMenuID.hpp"
#include "Dpr/UnderGround/UgFieldManager.hpp"
#include "EvolveDemoTools.hpp"
#include "PlayerWork.hpp"
#include "Pml/PokePara/PokemonParam.hpp"
#include "SmartPoint/Components/Fader.hpp"
#include "System/Action.hpp"
#include "System/Collections/Generic/List.hpp"
#include "UIMsgWindowController.hpp"

using namespace Dpr::Item;
using namespace Pml::PokePara;
using namespace System;
using namespace System::Collections::Generic;
using namespace UnityEngine::Events;

namespace Dpr
{
    namespace UI 
    {
        struct UIBag_BattleBootParam_Fields {
            int32_t TopMemberIndex;
            bool IsTrainerBattle;
            bool isDouble;
            struct System_Boolean_array* SasiosaeFlags;
        };

        struct UIBag_BattleBootParam_o {
            UIBag_BattleBootParam_Fields fields;
        };

        struct UIBag_c;

        struct UIBag_Fields {
            UIWindow_Fields super;
            struct BagItemPanel_o* bagItemPanel;
            struct PokemonParty_o* pokemonParty;
            struct BagWazaSelectPanel_o* wazaSelectPanel;
            struct UnityEngine_RectTransform_o* effectRoot;
            int32_t _animStateIn;
            int32_t _animStateOut;
            int32_t bootType;
            int32_t modeType;
            PokemonParam_o* onlyViewPokemonParam;
            int32_t onlyViewPartyIndex;
            int32_t onlyViewBattlePokemonId;
            struct UIBag_BattleBootParam_o battleBootParam;
            struct Action_int__o* onSelectedKinomiItem;
            struct Action_o* onCompleteAutoPilot;
            struct UIMsgWindowController_o* msgWindowController;
            struct PokemonParty_Param_o* pokemonPartyParam;
            int32_t displayMoney;
            bool isWaitUpdate;
            bool isWaitPokemonParty;
            bool isKinomiContact;
            bool isDontBuryNuts;
            bool isAutoPilot;
            bool _IsOpenFromBattleTeam_k__BackingField;
        };

        struct UIBag_o {
            UIBag_c *klass;
            void *monitor;
            UIBag_Fields fields;

            void Close(UnityAction_UIWindow__o *onClosed_, int32_t nextWindowId, bool isPlayCloseSe, MethodInfo *method);
            float GetRecoverHpRate(int32_t recoveryHpValue, MethodInfo *method);
            void OpenContextMenu(ContextMenuID_array *contextMenuIDs, Action_ContextMenuID__o *onSelected, UnityEngine_Vector2_o pivot, UnityEngine_Vector3_o pos, Action_o *onClosed, bool isNoDecideSe, bool isNoCancelSe, MethodInfo *method);
            void StartSelectPokemonParty(UnityAction_PokemonPartyItem__int__o *onClicked, MethodInfo *method);
        };

        struct UIBag___c__DisplayClass144_0_c;

        struct UIBag___c__DisplayClass144_0_Fields {
            struct UIBag_o *__4__this;
            struct PokemonParam_o *pokemonParam;
            struct PokemonPartyItem_o *pokemonPartyItem;
        };

        struct UIBag___c__DisplayClass144_0_o {
            struct UIBag___c__DisplayClass144_0_c *klass;
            void *monitor;
            struct UIBag___c__DisplayClass144_0_Fields fields;

            void ctor(MethodInfo *method);
        };

        struct UIBag___c__DisplayClass145_0_c;

        struct UIBag___c__DisplayClass145_0_Fields {
            struct PokemonParam_o *pokemonParam;
            struct UIBag_o *__4__this;
        };

        struct UIBag___c__DisplayClass145_0_o {
            struct UIBag___c__DisplayClass145_0_c *klass;
            void *monitor;
            struct UIBag___c__DisplayClass145_0_Fields fields;

            void ctor(MethodInfo *method);
        };

        struct UIBag___c__DisplayClass145_1_c;

        struct UIBag___c__DisplayClass145_1_Fields {
            int32_t addWazaNo;
            struct UIBag___c__DisplayClass145_0_o* CS___8__locals1;
            struct Action_WazaNo__WazaNo__o* __9__4;
            struct Action_int__o* __9__3;
        };

        struct UIBag___c__DisplayClass145_1_o {
            struct UIBag___c__DisplayClass145_1_c *klass;
            void *monitor;
            struct UIBag___c__DisplayClass145_1_Fields fields;
        };

        struct UIBag___c__DisplayClass127_1_c;

        struct UIBag___c__DisplayClass127_0_c;

        struct UIBag___c__DisplayClass127_0_Fields {
            struct UIBag_o* __4__this;
            ItemInfo_o* item;
            Action_o* useItemAction;
            Action_o* equipItemAction;
            Action_o* __9__12;
            Action_o* __9__17;
            UnityAction_UnityAction_UIWindow___o* __9__13;
            UnityAction_UnityAction_UIWindow___o* __9__19;
        };

        struct UIBag___c__DisplayClass127_0_o {
            UIBag___c__DisplayClass127_0_c *klass;
            void *monitor;
            UIBag___c__DisplayClass127_0_Fields fields;
        };

        struct UIBag___c__DisplayClass127_1_Fields {
            int32_t fieldFuncType;
            struct UIBag___c__DisplayClass127_0_o* CS___8__locals1;
        };

        struct UIBag___c__DisplayClass127_1_o {
            UIBag___c__DisplayClass127_1_c *klass;
            void *monitor;
            UIBag___c__DisplayClass127_1_Fields fields;
        };

        struct UIBag___c__DisplayClass127_5_c;

        struct UIBag___c__DisplayClass127_5_Fields {
            List_PokemonPartyItem__o* recoverPokemonItems;
            struct UIBag___c__DisplayClass127_1_o* CS___8__locals5;
        };

        struct UIBag___c__DisplayClass127_5_o {
            UIBag___c__DisplayClass127_5_c *klass;
            void *monitor;
            UIBag___c__DisplayClass127_5_Fields fields;
        };

        struct UIBag___c__DisplayClass127_6_c;

        struct UIBag___c__DisplayClass127_6_Fields {
            int32_t itemIndex;
            struct UIBag___c__DisplayClass127_5_o* CS___8__locals6;
            struct System_Action_o* __9__22;
        };

        struct UIBag___c__DisplayClass127_6_o {
            UIBag___c__DisplayClass127_6_c *klass;
            void *monitor;
            UIBag___c__DisplayClass127_6_Fields fields;

            void _ShowItemContextMenu_g__UpdateHp_20(MethodInfo *method);
        };

        struct UIBag___c__DisplayClass127_2_c;

        struct UIBag___c__DisplayClass127_2_Fields {
            UnityAction_UIWindow__o* saveOnPreClose;
            UnityAction_UIWindow__o* saveOnClosed;
            struct UIBag___c__DisplayClass127_1_o* CS___8__locals2;
        };

        struct UIBag___c__DisplayClass127_2_o {
            UIBag___c__DisplayClass127_2_c *klass;
            void *monitor;
            UIBag___c__DisplayClass127_2_Fields fields;
        };
        
        struct UIBag___c__DisplayClass133_1_c;
        
        struct UIBag___c__DisplayClass133_0_c;
        
        struct UIBag___c__DisplayClass133_0_Fields {
            struct UIBag_o* __4__this;
            struct Pml_PokePara_PokemonParam_o* pokeParam;
            ItemInfo_o* itemInfo;
            int32_t index;
            struct PokemonPartyItem_o* pokemonPartyItem;
            struct System_Action_o* __9__7;
            struct System_Action_o* __9__8;
            struct System_Action_o* __9__10;
            struct System_Action_o* __9__15;
        };
        
        struct UIBag___c__DisplayClass133_0_o {
            UIBag___c__DisplayClass133_0_c *klass;
            void *monitor;
            UIBag___c__DisplayClass133_0_Fields fields;
        };
        
        struct UIBag___c__DisplayClass133_1_Fields {
            int32_t seikaku;
            int32_t powerID;
            int32_t addExpValue;
            uint32_t beforeHp;
            struct UIBag___c__DisplayClass133_0_o* CS___8__locals1;
            struct System_Action_int__o* __9__6;
        };
        
        struct UIBag___c__DisplayClass133_1_o {
            UIBag___c__DisplayClass133_1_c *klass;
            void *monitor;
            UIBag___c__DisplayClass133_1_Fields fields;
        };
        
        struct UIBag___c__DisplayClass133_2_c;
        
        struct UIBag___c__DisplayClass133_2_Fields {
            EvolveDemoTools_Param_o evolveParam;
            struct UIBag___c__DisplayClass133_1_o* CS___8__locals2;
        };

        struct UIBag___c__DisplayClass133_2_o {
            UIBag___c__DisplayClass133_2_c *klass;
            void *monitor;
            UIBag___c__DisplayClass133_2_Fields fields;
        };

        struct UIBag___c__DisplayClass133_3_c;

        struct UIBag___c__DisplayClass133_3_Fields {
            int32_t amount;
            struct UIBag___c__DisplayClass133_2_o* CS___8__locals3;
        };

        struct UIBag___c__DisplayClass133_3_o {
            UIBag___c__DisplayClass133_3_c *klass;
            void *monitor;
            UIBag___c__DisplayClass133_3_Fields fields;
        };

        extern void *UIBag___c__DisplayClass127_2_TypeInfo;
        extern void *UIBag___c__DisplayClass127_5_TypeInfo;
        extern void *UIBag___c__DisplayClass127_6_TypeInfo;
        extern void *UIBag___c__DisplayClass133_3_TypeInfo;
        extern void *UIBag___c__DisplayClass144_0_TypeInfo;
        extern void *UIBag___c__DisplayClass145_0_TypeInfo;
        extern void *UIBag___c__DisplayClass145_1_TypeInfo;

        extern MethodInfo *UIBag___c__DisplayClass127_0__ShowItemContextMenu_g__EndUseAction_0;
        extern MethodInfo *UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__12;
        extern MethodInfo *UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__13;
        extern MethodInfo *UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__17;
        extern MethodInfo *UIBag___c__DisplayClass127_0__ShowItemContextMenu_b__19;
        extern MethodInfo *UIBag___c__DisplayClass127_2__ShowItemContextMenu_b__14;
        extern MethodInfo *UIBag___c__DisplayClass133_3__OnPokemonPartyClickedToUseItem_b__4;
        extern MethodInfo *UIBag___c__DisplayClass144_0__UseFormChangeItem_b__0;
        extern MethodInfo *UIBag___c__DisplayClass145_1__ShowFormChangeResult_b__2;
        extern MethodInfo *UIBag_EndSelectPokemonParty;
        extern MethodInfo *UIBag_OnPokemonPartyClickedToUseItem;
        extern MethodInfo *UIBag_ShowFormChangeResult;
    }
}