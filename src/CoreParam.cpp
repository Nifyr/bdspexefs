#include "il2cpp.hpp"
#include "Pml/PokePara/CoreParam.h"
#include "Pml/PmlUse.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "Dpr/Battle/Logic/ItemData.h"
#include "System/Array.hpp"
#include "System/Collections/Generic/HashSet.hpp"
#include "logger.hpp"
#include "util.hpp"

using namespace Pml::PokePara;
using namespace System::Collections::Generic;

// 0x04bdc5d0
extern void ** PTR_DAT_04bd86f0;
// 0x04bdc5f0
extern void ** PTR_DAT_04bdc5f0;

enum CategoryType
{
	Heal = 0,
	Ball = 1,
	Battle = 2,
	Nuts = 3,
	Tools = 4,
	WazaMachine = 5,
	Treasure = 6,
	Food = 7,
	Important = 8,
	Length = 9,
};

namespace XLSXContent
{
    namespace ItemTable
    {
        struct SheetWazaMachine_Fields {
            int32_t itemNo;
            int32_t machineNo;
            int32_t wazaNo;
        };

        struct SheetWazaMachine_c;

        struct SheetWazaMachine_o {
            SheetWazaMachine_c *klass;
            void *monitor;
            SheetWazaMachine_Fields fields;
        };

        struct SheetItem_Fields {
            int16_t no;
            uint8_t type;
            int32_t iconid;
            int32_t price;
            int32_t bp_price;
            uint8_t eqp;
            uint8_t atc;
            uint8_t nage_atc;
            uint8_t sizen_atc;
            uint8_t sizen_type;
            uint8_t tuibamu_eff;
            uint8_t sort;
            uint8_t group;
            uint8_t group_id;
            uint8_t fld_pocket;
            uint8_t field_func;
            uint8_t battle_func;
            uint8_t wk_cmn;
            uint8_t wk_critical_up;
            uint8_t wk_atc_up;
            uint8_t wk_def_up;
            uint8_t wk_agi_up;
            uint8_t wk_hit_up;
            uint8_t wk_spa_up;
            uint8_t wk_spd_up;
            uint8_t wk_prm_pp_rcv;
            int8_t wk_prm_hp_exp;
            int8_t wk_prm_pow_exp;
            int8_t wk_prm_def_exp;
            int8_t wk_prm_agi_exp;
            int8_t wk_prm_spa_exp;
            int8_t wk_prm_spd_exp;
            int8_t wk_friend1;
            int8_t wk_friend2;
            int8_t wk_friend3;
            uint8_t wk_prm_hp_rcv;
            uint32_t flags0;
        };

        struct SheetItem_c;

        struct SheetItem_o {
            SheetItem_c *klass;
            void *monitor;
            SheetItem_Fields fields;
        };
    }

    struct ItemTable_c;
}

using namespace XLSXContent;
using namespace XLSXContent::ItemTable;
using namespace Pml::Personal;
using namespace Dpr::Battle::Logic;

// 0x04bdc5f8
extern MethodInfo ** PTR_HashSet_Add_WazaNo_MethodInfo;

HashSet_WazaNo__o * CoreParam::CollectRemindableWaza( MethodInfo *method )
{
    // Pml.PokePara.CoreParam$$CollectRemindableWaza
    system_load_typeinfo(*PTR_DAT_04bd86f0);
    // I have no idea why I was loading this but it is probably important
    // system_load_typeinfo(*PTR_DAT_04bdc5f0);
    socket_log_fmt("CollectRemindableWaza\n");

    int32_t monsNo = this->GetMonsNo((MethodInfo *) nullptr);
    uint16_t formNo = this->GetFormNo((MethodInfo *) nullptr);
    socket_log_fmt("monsNo: %04X\n", monsNo);
    socket_log_fmt("formNo: %02X\n", formNo);
    HashSet_WazaNo__o * hashSet = this->_CollectRemindableWaza((MethodInfo *) nullptr);
    socket_log_fmt("hashSet: %08X\n", hashSet);

    PmlUse_o * pmlUse = PmlUse_o::get_Instance((MethodInfo *) nullptr);
    socket_log_fmt("pmlUse: %08X\n", pmlUse);
    ItemTable_o * itemTable = pmlUse->fields.itemPrmTotal;
    socket_log_fmt("itemTable: %08X\n", itemTable);
    System::Array<ItemTable_SheetWazaMachine_o *> * wazaMachine = itemTable->fields.WazaMachine;
    socket_log_fmt("wazaMachine: %08X\n", wazaMachine);
    socket_log_fmt("this->fields.m_accessor: %08X\n", this->fields.m_accessor);

    ItemTable_SheetWazaMachine_o * iWazaMachine;
    for (size_t i = 0; i < wazaMachine->max_length; i++)
    {
        iWazaMachine = wazaMachine->m_Items[i];
        if (!ItemData::HaveItem(iWazaMachine->fields.itemNo, (MethodInfo *) nullptr))
        {
            continue;
        }
        
        PersonalSystem::LoadPersonalData(monsNo, formNo, (MethodInfo *) nullptr);
        if (!PersonalSystem::CheckPersonalWazaMachine(iWazaMachine->fields.machineNo, (MethodInfo *) nullptr))
        {
            continue;
        }
        if (this->fields.m_accessor->GetWazaNo(0, (MethodInfo *) nullptr) == iWazaMachine->fields.wazaNo)
        {
            continue;
        }

        if (this->fields.m_accessor->GetWazaNo(1, (MethodInfo *) nullptr) == iWazaMachine->fields.wazaNo)
        {
            continue;
        }

        if (this->fields.m_accessor->GetWazaNo(2, (MethodInfo *) nullptr) == iWazaMachine->fields.wazaNo)
        {
            continue;
        }

        if (this->fields.m_accessor->GetWazaNo(3, (MethodInfo *) nullptr) == iWazaMachine->fields.wazaNo)
        {
            continue;
        }

        hashSet->Add(iWazaMachine->fields.wazaNo, *PTR_HashSet_Add_WazaNo_MethodInfo);
    }
    
    socket_log_fmt("Added TM's move to list\n");
    return hashSet;
}


HashSet_WazaNo__o * CoreParam_CollectRemindableWaza(CoreParam * __this, MethodInfo *method )
{
    return __this->CollectRemindableWaza(method);
}