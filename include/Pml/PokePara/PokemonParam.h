#pragma once

#include "Pml/PokePara/CoreParam.h"

namespace Pml
{
    namespace PokePara
    {
        struct PokemonParam_Fields {
            CoreParam_Fields super;
        };

        struct PokemonParam_c;
        struct PokemonParam_o {
            PokemonParam_c *klass;
            void *monitor;
            PokemonParam_Fields fields;
        };
    }
}

