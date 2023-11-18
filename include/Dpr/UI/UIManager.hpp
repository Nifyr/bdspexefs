#include "il2cpp.hpp"

#include "System/Func.hpp"

namespace Dpr
{
    namespace UI 
    {
        struct UIManager_o {
            void CloseXMenu(UnityAction_UnityAction_UIWindow___o *onCall, MethodInfo *method);
            Il2CppObject * CreateUIWindow_object_(int32_t windowId, MethodInfo *method);
            void UseDSPlayerItem(MethodInfo *method);
        };

        struct UIManager_RGCTXs;

        struct UIManager_VTable {
            VirtualInvokeData _0_Equals;
            VirtualInvokeData _1_Finalize;
            VirtualInvokeData _2_GetHashCode;
            VirtualInvokeData _3_ToString;
            VirtualInvokeData _4_Awake;
            VirtualInvokeData _5_OnApplicationQuit;
        };

        struct UIManager_StaticFields {
            int32_t StickLLeft;
            int32_t StickLRight;
            int32_t StickLUp;
            int32_t StickLDown;
            int32_t ButtonA;
            int32_t ButtonB;
            int32_t ButtonX;
            int32_t ButtonY;
            int32_t ButtonPlusMinus;
            struct UnityEngine_Events_UnityAction_ZoneID__int__o* onWazaFly;
            struct UnityEngine_Events_UnityAction_int__o* onDressChanged;
            struct System_Func_UIManager_FieldWazaParam__UIManager_FieldUseResult__o* onFieldWaza;
            Func_ItemInfo__UIManager_FieldUseResult__o* onUseFieldItem;
            struct System_Action_int__int__ItemInfo__o* onUseItemInBattle;
            struct System_Action_FieldPoketch_HidenWazaType__o* onUseHidenWaza;
            struct System_Func_Vector2__FieldPoketch_DowsingResult__o* onUseDowsing;
            struct UIManager_ComparerPokemonIcon_o* _comparerPokemonIcon;
            struct UIManager_ComparerAshiatoIcon_o* _comparerAshiatoIcon;
            struct UIManager_ComparerZukanDisplay_o* _comparerZukanDisplay;
            struct UIManager_ComparerPokemonVoice_o* _comparerPokemonVoice;
            struct UIManager_ComparerZukanCompareHeight_o* _comparerZukanCompareHeight;
            struct UIManager_LangParam_array* _langParams;
            struct System_Collections_Generic_List_UIManager_PokemonParamMapping__o* _pokemonParamMappings;
            int32_t _id_GrayscaleAmount;
            struct UIManager_ComparerTownMapGuide_o* _comparerTownMapGuide;
            struct UIManager_ComparerPlaceName_o* _comparerPlaceName;
        };

        struct UIManager_c {
            Il2CppClass_1 _1;
            struct UIManager_StaticFields* static_fields;
            UIManager_RGCTXs* rgctx_data;
            Il2CppClass_2 _2;
            UIManager_VTable vtable;
        };

        extern UIManager_c *UIManager_TypeInfo;

        extern MethodInfo *UIManager_CreateUIWindow_UILevelUp_;
    }
}