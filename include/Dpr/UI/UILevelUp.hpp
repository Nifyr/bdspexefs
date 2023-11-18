#include "il2cpp.hpp"

namespace Dpr
{
    namespace UI 
    {
        struct UILevelUp_c;

        struct UILevelUp_Param_Fields {
            struct System_UInt32_array* AddExpValues;
            int32_t TargetIndex;
            int32_t LevelUpCount;
            struct Pml_PokeParty_o* PokeParty;
            struct Dpr_Battle_Logic_BattleViewBase_ExpGetResult_o* BattleExpGetResult;
        };

        struct UILevelUp_Param_o {
            UILevelUp_Param_Fields fields;
        };
        
        struct UILevelUp_Fields {
            UIWindow_Fields super;
            int32_t _animStateIn;
            int32_t _animStateOut;
            struct LevelUpPokemonPanel_array* levelUpPokemonPanels;
            struct LevelUpStatusPanel_o* statusPanel;
            struct UILevelUp_Param_o param;
            struct UIMsgWindowController_o* msgWindowController;
            bool isAnimateGauge;
            bool isPlayGaugeUpSe;
            bool isPlayLevelUpSe;
            bool isWaitExit;
        };
        
        struct UILevelUp_o {
            UILevelUp_c *klass;
            void *monitor;
            UILevelUp_Fields fields;

            void Open(UILevelUp_Param_o *param, int32_t prevWindowId, MethodInfo *method);
        };
    }
}