#include "il2cpp.hpp"
#include "System/Array.hpp"

namespace XLSXContent
{
    struct WazaTable_c;

    struct WazaTable_SheetWaza_c;

    struct WazaTable_SheetWaza_Fields {
        int32_t wazaNo;
        bool isValid;
        uint8_t type;
        uint8_t category;
        uint8_t damageType;
        uint8_t power;
        uint8_t hitPer;
        uint8_t basePP;
        int8_t priority;
        uint8_t hitCountMax;
        uint8_t hitCountMin;
        uint16_t sickID;
        uint8_t sickPer;
        uint8_t sickCont;
        uint8_t sickTurnMin;
        uint8_t sickTurnMax;
        uint8_t criticalRank;
        uint8_t shrinkPer;
        uint16_t aiSeqNo;
        int8_t damageRecoverRatio;
        int8_t hpRecoverRatio;
        uint8_t target;
        uint8_t rankEffType1;
        uint8_t rankEffType2;
        uint8_t rankEffType3;
        int8_t rankEffValue1;
        int8_t rankEffValue2;
        int8_t rankEffValue3;
        uint8_t rankEffPer1;
        uint8_t rankEffPer2;
        uint8_t rankEffPer3;
        uint32_t flags;
        uint32_t contestWazaNo;
    };

    struct WazaTable_SheetWaza_o {
        WazaTable_SheetWaza_c *klass;
        void *monitor;
        WazaTable_SheetWaza_Fields fields;
    };

    struct WazaTable_SheetWaza_array {
        Il2CppObject obj;
        Il2CppArrayBounds *bounds;
        il2cpp_array_size_t max_length;
        WazaTable_SheetWaza_o* m_Items[65535];
    };

    struct WazaTable_Fields {
        UnityEngine_ScriptableObject_Fields super;
        struct WazaTable_SheetWaza_array* Waza;
        struct WazaTable_SheetYubiwohuru_array* Yubiwohuru;
    };

    struct WazaTable_o {
        WazaTable_c *klass;
        void *monitor;
        WazaTable_Fields fields;
    };
}