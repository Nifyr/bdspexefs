#include "il2cpp.hpp"
#include "Dpr/UI/UIBag.hpp"
#include "level_cap.hpp"
#include "logger.hpp"
#include "util.hpp"

namespace Dpr
{
    namespace UI {
        struct BagItemButton_c;
        struct BagItemButton_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            struct UnityEngine_UI_Image_o* iconImage;
            struct UIText_o* nameText;
            struct UnityEngine_UI_Image_o* newIconImage;
            struct UnityEngine_UI_Image_o* favoriteIconImage;
            struct UIText_o* stockCountLabelText;
            struct UIText_o* stockCountValueText;
            struct UnityEngine_UI_Image_o* registerButtonImage;
            struct UnityEngine_Sprite_array* shortcutButonSprites;
            int32_t index;
            struct UnityEngine_RectTransform_o* rectTransform;
            struct Dpr::Item::ItemInfo_o* item;
        };

        struct BagItemButton_o {
            BagItemButton_c *klass;
            void *monitor;
            BagItemButton_Fields fields;
        };


        struct BagItemPanel_Fields {
            UnityEngine_MonoBehaviour_Fields super;
            struct Cursor_o* cursor;
            struct BagIconPanel_o* bagIconPanel;
            struct UIText_o* moneyValueText;
            struct UIButtonSelector_o* categoryButtonSelector;
            struct UIText_o* categoryNameText;
            struct UnityEngine_RectTransform_o* categoryLeftArrowRectTransform;
            struct UnityEngine_RectTransform_o* categoryRightArrowRectTransform;
            struct UIScrollView_o* itemListScrollView;
            struct UIText_o* noDataText;
            struct BagItemDescriptionPanel_o* bagItemDescriptionPanel;
            struct BagItemSelectAmount_o* selectAmount;
            bool isRemoveNewEnable;
            bool isBattle;
            struct Dpr_Item_ItemListMemory_o* itemListMemory;
            struct System_Collections_Generic_List_ItemInfo__o* items;
            struct BagCategoryButton_o* currentCategoryButton;
            struct UnityEngine_Coroutine_o* removeNewIconCoroutine;
            struct System_Action_int__o* onDecideSelectAmountCallback;
            struct System_Action_o* onCancelSelectAmountCallback;
            struct System_Action_int__o* onSelectAmountValueChangedCallback;
            int32_t _CurrentCategoryId_k__BackingField;
            struct BagItemButton_o* _SelectedItemButton_k__BackingField;
            struct System_Action_BagItemButton__o* OnChangeSelectItem;
        };

        struct BagItemPanel_c;
        struct BagItemPanel_o {
            BagItemPanel_c *klass;
            void *monitor;
            BagItemPanel_Fields fields;
        };

        struct UIBag_c;
    }
}

// void UIBag_OnPokemonPartyClickedToUseItem
//                (UIBag_o *__this, PokemonPartyItem_o *pokemonPartyItem,int32_t index,
//                MethodInfo *method)
// {

// }

const int32_t EVERLASTING_CANDY_ID = 1825; 

uint32_t isValidRareCandy(uint32_t level, Dpr::UI::UIBag_o *__this)
{
    socket_log_fmt("isValidRareCandy\n");
    socket_log_fmt("[isValidRareCandy] level: %08X\n", level);
    socket_log_fmt("[isValidRareCandy] __this: %08X\n", __this);
    il2cpp_runtime_class_init(PlayerWork_TypeInfo);
    // Game clear
    if (PlayerWork::GetSytemFlag(5, (MethodInfo *) nullptr))
    {
        socket_log_fmt("Game Clear!\n");
        return 100 - level;
    }

    // Is Level Cap enabled
    if (!PlayerWork::GetBool(2197, (MethodInfo *) nullptr))
    {
        socket_log_fmt("Level cap disabled!\n");
        return 100 - level;
    }

    Dpr::Item::ItemInfo_o * item = __this->fields.bagItemPanel->fields._SelectedItemButton_k__BackingField->fields.item;
    if (item->get_Id(nullptr) != EVERLASTING_CANDY_ID)
    {
        socket_log_fmt("Not an everlasting candy!\n");
        return 100 - level;
    }

    uint32_t max_level = getMaxLevel();

    if (level >= max_level)
    {
        socket_log_fmt("Above level cap!\n");
        return 0;
    } else {
        socket_log_fmt("Below level cap!\n");
        return max_level - level;
    }
}

int32_t ItemWork_SubItem(int32_t itemno,int32_t num,MethodInfo *method)
{
    socket_log_fmt("[ItemWork_SubItem] itemno: %08X\n", itemno);
    socket_log_fmt("[ItemWork_SubItem] num: %08X\n", num);
    if (itemno != EVERLASTING_CANDY_ID)
    {
        return ItemWork::SubItem(itemno, num, method);
    }
    // More like a nullptr return. Hopefully that is valid for this. Otherwise I can always change it to call
    // PlayerWork$$GetItem
    return 0;
}