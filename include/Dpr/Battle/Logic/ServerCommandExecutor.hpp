#pragma once

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ServerCommandExecutor_c;

            struct ServerCommandExecutor_Fields {
                struct MainModule_o* m_pMainModule;
                struct BattleEnv_o* m_pBattleEnv;
                struct EventSystem_o* m_pEventSystem;
            };

            struct ServerCommandExecutor_o
            {
                ServerCommandExecutor_c *klass;
                void *monitor;
                ServerCommandExecutor_Fields fields;
            };
        }
    }
}