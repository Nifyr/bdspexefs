#include "il2cpp.hpp"

#include "System/Collections/Generic/List.hpp"

using namespace System::Collections::Generic;

namespace Dpr
{
    namespace UI 
    {
        struct PokemonParty_c;

        struct PokemonParty_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            struct UnityEngine_RectTransform_o* _contentRoot;
            struct UnityEngine_RectTransform_o* _basePlateRoot;
            struct UnityEngine_Sprite_array* _spriteBasePlates;
            List_PokemonPartyItem__o* _activeItems;
            int32_t _selectIndex;
            struct UnityEngine_UI_VerticalLayoutGroup_o* _verticalLayoutGroup;
            struct PokemonPartyItem_o* _fromSwapItem;
            int32_t _fromSwapSiblingIndex;
            struct UnityEngine_Events_UnityAction_PokemonPartyItem__PokemonPartyItem__o* _onSwapChanged;
            struct PokemonPartyItem_o* _fromItemSwapItem;
            struct UnityEngine_Events_UnityAction_PokemonPartyItem__PokemonPartyItem__bool__o* _onItemSwapChanged;
            bool _isActived;
            struct UIInputController_o* _input;
            struct UnityEngine_Events_UnityAction_PokemonPartyItem__int__o* onClicked;
            struct UnityEngine_Events_UnityAction_PokemonPartyItem__int__o* onSelectChanged;
            struct PokemonParty_Param_o* _param;
        };

        struct PokemonParty_o {
            PokemonParty_c *klass;
            void *monitor;
            PokemonParty_Fields fields;
        };
    }
}