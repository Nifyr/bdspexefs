#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ExPokePos_c;

            struct ExPokePos_Fields {
                int32_t m_type;
                uint8_t m_basePos;
            };

            struct ExPokePos_o {
                ExPokePos_c *klass;
                void *monitor;
                ExPokePos_Fields fields;

                void ctor(int32_t type, uint8_t basePos, MethodInfo *method);
            };

            extern void *ExPokePos_TypeInfo;

            namespace ExPosType {
                enum ExPosType {
                    BASE_POS,
                    NEXT_FRIENDS,
                    AREA_ENEMY,
                    AREA_OTHERS,
                    AREA_MYTEAM,
                    AREA_FRIENDS,
                    AREA_ALL,
                    FULL_ENEMY,
                    FULL_FRIENDS,
                    FULL_ALL
                };
            }
        }
    }
}