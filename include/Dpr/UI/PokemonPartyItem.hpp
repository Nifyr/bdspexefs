#include "il2cpp.hpp"
#include "Pml/PokePara/PokemonParam.hpp"
#include "PokemonParty.hpp"
#include "System/Action.hpp"

using namespace System;
using namespace Pml::PokePara;

namespace Dpr
{
    namespace UI 
    {
        struct PokemonPartyItem_c;
        
        struct PokemonPartyItem_Param_c;
        
        struct PokemonPartyItem_Param_Fields {
            PokemonParam_o* pokemonParam;
            bool showItemName;
            struct PokemonPartyItem_Param_Contest_o* contest;
            struct PokemonPartyItem_Param_Battle_o* battle;
            struct PokemonPartyItem_Param_RotomSelect_o* rotomSelect;
        };
        
        struct PokemonPartyItem_Param_o {
            PokemonPartyItem_Param_c *klass;
            void *monitor;
            PokemonPartyItem_Param_Fields fields;
        };
        
        struct PokemonPartyItem_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            struct UnityEngine_RectTransform_o* _root;
            struct UnityEngine_RectTransform_o* _infoRoot;
            struct UnityEngine_RectTransform_o* _statusRoot;
            struct UIText_o* _name;
            struct UIText_o* _hp;
            struct UIText_o* _maxHp;
            struct HpBar_o* _hpBar;
            struct UnityEngine_UI_Image_o* _hpBG;
            struct UIText_o* _level;
            struct UnityEngine_UI_Image_o* _sex;
            struct UnityEngine_RectTransform_o* _itemRoot;
            struct PokemonIcon_o* _pokemonIcon;
            struct PokemonSick_o* _sick;
            struct UnityEngine_RectTransform_o* _pair;
            struct PokemonPartyItem_Contest_o* _contest;
            struct PokemonPartyItem_RotomSelect_o* _rotomSelect;
            struct UnityEngine_RectTransform_o* _usableItemRoot;
            float _formChangeLoadIconTiming;
            int32_t _stateBits;
            struct PokemonPartyItem_Param_o* _param;
            bool isShowUsableItem;
            struct UnityEngine_Vector3_o _offsetIconPos;
            struct UnityEngine_Vector3_o _initIconPos;
            struct UnityEngine_Animator_o* _animator;
            struct UnityEngine_Coroutine_o* _coroutine;
            struct EffectInstance_o* _effectInstance;
            bool _isDestroy;
        };
        
        struct PokemonPartyItem_o {
            PokemonPartyItem_c *klass;
            void *monitor;
            PokemonPartyItem_Fields fields;

            bool FormChange(uint16_t formNo, UnityEngine_RectTransform_o *effectRoot, Action_PokemonParam__o *onChangeIcon, Action_PokemonParam__o *onComplete, MethodInfo *method);
            void Setup(PokemonPartyItem_Param_o *param, MethodInfo *method);
        };

        struct PokemonPartyItem_array {
            Il2CppObject obj;
            Il2CppArrayBounds *bounds;
            il2cpp_array_size_t max_length;
            PokemonPartyItem_o* m_Items[65535];
        };
    }
}