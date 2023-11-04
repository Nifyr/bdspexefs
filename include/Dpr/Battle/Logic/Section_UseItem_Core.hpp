#pragma once

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "POKE_CAPTURED_CONTEXT.hpp"
#include "Section.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_UseItem_Core_c;
            
            struct Section_UseItem_Core_ItemEffectInfo_c;

            struct Section_UseItem_Core_ItemEffectFuncPtr_o {
                bool Invoke(BTL_POKEPARAM_o *target, uint16_t itemID, int32_t itemParam, uint8_t actParam, MethodInfo *method);
            };
            
            struct Section_UseItem_Core_ItemEffectInfo_Fields {
                int32_t effect;
                uint8_t range;
                struct Section_UseItem_Core_ItemEffectFuncPtr_o* func;
            };
            
            struct Section_UseItem_Core_ItemEffectInfo_o {
                Section_UseItem_Core_ItemEffectInfo_c *klass;
                void *monitor;
                Section_UseItem_Core_ItemEffectInfo_Fields fields;
            };
            
            struct Section_UseItem_Core_ItemEffectInfo_array {
                Il2CppObject obj;
                Il2CppArrayBounds *bounds;
                il2cpp_array_size_t max_length;
                Section_UseItem_Core_ItemEffectInfo_o* m_Items[65535];
            };

            struct Section_UseItem_Core_Fields {
                struct Section_Fields super;
                struct Section_UseItem_Core_ItemEffectInfo_array* s_itemEffectTableInstance;
            };

            struct Section_UseItem_Core_o {
                Section_UseItem_Core_c *klass;
                void *monitor;
                Section_UseItem_Core_Fields fields;

                bool canUseItem(uint16_t itemID, uint8_t targetArea, uint8_t targetPos, MethodInfo *method);
                Section_UseItem_Core_ItemEffectInfo_array * get_s_itemEffectTable(MethodInfo *method);
                BTL_POKEPARAM_o * getTaragetInfo(uint8_t *pTargetArea, uint8_t *pTargetPos, uint8_t targetPokeID, MethodInfo *method);
                void useBall(BTL_POKEPARAM_o *userPoke, uint16_t itemID, bool *pIsUsed, bool *pIsCaptured, POKE_CAPTURED_CONTEXT_o *pCaptureContext, MethodInfo *method);
            };
            
            struct Section_UseItem_Core_Result_c;
            
            struct Section_UseItem_Core_Result_Fields {
                uint8_t useResult;
                bool isConsumed;
                bool isUsedBall;
            };
            
            struct Section_UseItem_Core_Result_o {
                Section_UseItem_Core_Result_c *klass;
                void *monitor;
                Section_UseItem_Core_Result_Fields fields;
            };
            
            struct Section_UseItem_Core_Description_c;
            
            struct Section_UseItem_Core_Description_Fields {
                struct BTL_POKEPARAM_o* poke;
                uint16_t itemID;
                uint8_t actParam;
                uint8_t targetID;
                struct POKE_CAPTURED_CONTEXT_o* capContext;
            };
            
            struct Section_UseItem_Core_Description_o {
                Section_UseItem_Core_Description_c *klass;
                void *monitor;
                Section_UseItem_Core_Description_Fields fields;
            };
        }
    }
}