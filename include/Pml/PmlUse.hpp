#include "il2cpp.hpp"

#include "XLSXContent/ItemTable.hpp"

using namespace XLSXContent;

namespace Pml
{

    struct PmlUse_Fields {
        bool isAutoLoad;
        struct XLSXContent_PersonalTable_o* personalTotal;
        struct XLSXContent_GrowTable_o* growTableTotal;
        struct XLSXContent_EvolveTable_o* evolveTableTotal;
        struct XLSXContent_WazaOboeTable_o* wazaOboeTotal;
        struct XLSXContent_WazaTable_o* wazaDataTotal;
        ItemTable_o* itemPrmTotal;
        struct XLSXContent_TamagoWazaTable_o* tamagoWazaTotal;
        struct XLSXContent_AddPersonalTable_o* addPersonalTotal;
        struct XLSXContent_SealTable_o* sealTotal;
        struct XLSXContent_UgItemTable_o* ugItemPrmTotal;
        struct XLSXContent_TamaTable_o* tamaTableTotal;
        struct XLSXContent_PedestalTable_o* pedestalTableTotal;
        struct XLSXContent_StoneStatuEeffect_o* stoneStatuEeffectTotal;
        struct XLSXContent_UgFatherPos_o* ugfPosTotal;
        struct XLSXContent_UgFatherExpansion_o* ugfExpansionTotal;
        struct XLSXContent_UgFatherShopTable_o* ugfShopTotal;
        struct Pml_PokePara_EvolveManager_o* evolveManager;
        bool isABAppended;
        bool isInitialized;
        bool _IsPersistentTiming_k__BackingField;
    };

    struct PmlUse_c;

    struct PmlUse_o {
        // 0x027fb230
        static PmlUse_o * get_Instance(MethodInfo * method);

        PmlUse_c *klass;
        void *monitor;
        PmlUse_Fields fields;
    };
}