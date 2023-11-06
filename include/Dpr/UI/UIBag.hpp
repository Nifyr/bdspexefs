#include "il2cpp.hpp"
#include "System/Array.hpp"

#include "ContextMenuID.hpp"
#include "Pml/PokePara/PokemonParam.hpp"
#include "System/Action.hpp"
#include "UIMsgWindowController.hpp"
#include "UIWindow.hpp"

using namespace System;

namespace Dpr
{
    namespace UI 
    {
        struct UIBag_BattleBootParam_Fields {
            int32_t TopMemberIndex;
            bool IsTrainerBattle;
            bool isDouble;
            System::Array<bool> * SasiosaeFlags;
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
            struct PokemonParam_o* onlyViewPokemonParam;
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
            bool isAutoPilot;
        };

        struct UIBag_o {
            UIBag_c *klass;
            void *monitor;
            UIBag_Fields fields;

            void OpenContextMenu(ContextMenuID_array *contextMenuIDs, Action_ContextMenuID__o *onSelected, UnityEngine_Vector2_o pivot, UnityEngine_Vector3_o pos, Action_o *onClosed, bool isNoDecideSe, bool isNoCancelSe, MethodInfo *method);
            void Close(UnityEngine_Events_UnityAction_UIWindow__o *onClosed_, int32_t nextWindowId, bool isPlayCloseSe, MethodInfo *method);
        };

        struct UIBag___c__DisplayClass144_0_c;

        struct UIBag___c__DisplayClass144_0_Fields {
            struct UIBag_o *__4__this;
            struct Pml::PokePara::PokemonParam_o *pokemonParam;
            struct PokemonPartyItem_o *pokemonPartyItem;
        };

        struct UIBag___c__DisplayClass144_0_o {
            struct UIBag___c__DisplayClass144_0_c *klass;
            void *monitor;
            struct UIBag___c__DisplayClass144_0_Fields fields;

            void ctor(MethodInfo *method);
        };

        extern void *UIBag___c__DisplayClass144_0_TypeInfo;

        extern MethodInfo *UIBag___c__DisplayClass144_0__UseFormChangeItem_b__0;
        extern MethodInfo *UIBag_EndSelectPokemonParty;
        extern MethodInfo *UIBag_ShowFormChangeResult;
    }
}