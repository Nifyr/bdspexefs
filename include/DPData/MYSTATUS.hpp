#include "il2cpp.hpp"

#include "System/String.hpp"

using namespace System;

namespace DPData {
    struct MYSTATUS_Fields {
        String_o* name;
        uint32_t id;
        int32_t gold;
        bool sex;
        uint8_t region_code;
        uint8_t badge;
        uint8_t trainer_view;
        uint8_t rom_code;
        bool dp_clear;
        uint8_t body_type;
        uint8_t fashion;
        int32_t defaultPokeType;
        bool dsPlayerFlag;
        int32_t turewalkMemberIndex;
        struct UnityEngine_Vector2Int_o grid;
        float height;
        float rotation;
    };

    struct MYSTATUS_o {
        MYSTATUS_Fields fields;
    };
}
