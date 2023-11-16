#include "il2cpp.hpp"

namespace Pml
{
    namespace PokePara
    {
        struct OwnerInfo_c;

        struct OwnerInfo_Fields {
            uint32_t trainerId;
            uint8_t sex;
            uint8_t langID;
            struct String_o* name;
        };

        struct OwnerInfo_o {
            OwnerInfo_c *klass;
            void *monitor;
            OwnerInfo_Fields fields;
        };
    }
}