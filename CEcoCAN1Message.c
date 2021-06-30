/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCAN1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoCAN1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Elena Uskova. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoCAN1Message.h"
#include "CEcoCAN1MCP2515Controller.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCAN20BMessage
 * </описание>
 *
 */
int16_t CEcoCAN1Message_QueryInterface(/* in */ struct IEcoCAN20BMessage* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCAN20AMessage) ) {
        *ppv = &pCMe->m_pVTblICAN20BMsg;
        pCMe->m_pVTblICAN20BMsg->AddRef((IEcoCAN20BMessage*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCAN20BMessage) ) {
        *ppv = &pCMe->m_pVTblICAN20BMsg;
        pCMe->m_pVTblICAN20BMsg->AddRef((IEcoCAN20BMessage*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblICAN20BMsg;
        pCMe->m_pVTblICAN20BMsg->AddRef((IEcoCAN20BMessage*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoCAN20BMessage
 * </описание>
 *
 */
uint32_t CEcoCAN1Message_AddRef(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoCAN20BMessage
 * </описание>
 *
 */
uint32_t CEcoCAN1Message_Release(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCAN1Message((IEcoCAN20BMessage*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция set_Identifier
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_Identifier(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint16_t id11Bit) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_Identifier = id11Bit;
}

/*
 *
 * <сводка>
 *   Функция get_Identifier
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint16_t CEcoCAN1Message_get_Identifier(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_Identifier;
}

/*
 *
 * <сводка>
 *   Функция set_RTR
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_RTR(/* in */ struct IEcoCAN20BMessage* me, /* in */ bool_t bit) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_RTR = bit;
}

/*
 *
 * <сводка>
 *   Функция get_RTR
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
bool_t CEcoCAN1Message_get_RTR(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_RTR;
}

/*
 *
 * <сводка>
 *   Функция set_DLC
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_DLC(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint8_t length4Bit) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_DLC = length4Bit;
}

/*
 *
 * <сводка>
 *   Функция get_DLC
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint8_t CEcoCAN1Message_get_DLC(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_DLC;
}


/*
 *
 * <сводка>
 *   Функция set_Data
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_Data(/* in */ struct IEcoCAN20BMessage* me, /* in */ byte_t* data) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;
    int8_t iIndex = 0;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    /* Поле данных */
    for (iIndex = 0; iIndex < 8; iIndex++) {
        if (iIndex < pCMe->m_DLC) {
            pCMe->m_Data[iIndex] = data[iIndex];
        }
        else {
            pCMe->m_Data[iIndex] = 0;
        }
    }
}

/*
 *
 * <сводка>
 *   Функция get_Data
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
byte_t* CEcoCAN1Message_get_Data(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    return pCMe->m_Data;
}

/*
 *
 * <сводка>
 *   Функция set_CRC
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_CRC(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint16_t crc) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_CRC = crc;
}

/*
 *
 * <сводка>
 *   Функция get_CRC
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint16_t CEcoCAN1Message_get_CRC(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_CRC;
}

/*
 *
 * <сводка>
 *   Функция set_ExtendedIdentifier
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_ExtendedIdentifier(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint32_t id18Bit) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_ExtendedIdentifier = id18Bit;
}

/*
 *
 * <сводка>
 *   Функция get_Identifier
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t CEcoCAN1Message_get_ExtendedIdentifier(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_ExtendedIdentifier;
}

/*
 *
 * <сводка>
 *   Функция set_SRR
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_SRR(/* in */ struct IEcoCAN20BMessage* me, /* in */ bool_t bit) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_SRR = bit;
}

/*
 *
 * <сводка>
 *   Функция get_SRR
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
bool_t CEcoCAN1Message_get_SRR(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_SRR;
}

/*
 *
 * <сводка>
 *   Функция set_IDE
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
void CEcoCAN1Message_set_IDE(/* in */ struct IEcoCAN20BMessage* me, /* in */ bool_t bit) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return;
    }

    pCMe->m_IDE = bit;
}

/*
 *
 * <сводка>
 *   Функция get_IDE
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
bool_t CEcoCAN1Message_get_IDE(/* in */ struct IEcoCAN20BMessage* me) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)me;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_IDE;
}

/* Create Virtual Table */
IEcoCAN20BMessageVTbl g_x8CC0027BE0A74E0DB34332D0C13B1A5AVTbl = {
    CEcoCAN1Message_QueryInterface,
    CEcoCAN1Message_AddRef,
    CEcoCAN1Message_Release,
    CEcoCAN1Message_set_Identifier,
    CEcoCAN1Message_get_Identifier,
    CEcoCAN1Message_set_RTR,
    CEcoCAN1Message_get_RTR,
    CEcoCAN1Message_set_DLC,
    CEcoCAN1Message_get_DLC,
    CEcoCAN1Message_set_Data,
    CEcoCAN1Message_get_Data,
    CEcoCAN1Message_set_CRC,
    CEcoCAN1Message_get_CRC,
    CEcoCAN1Message_set_ExtendedIdentifier,
    CEcoCAN1Message_get_ExtendedIdentifier,
    CEcoCAN1Message_set_SRR,
    CEcoCAN1Message_get_SRR,
    CEcoCAN1Message_set_IDE,
    CEcoCAN1Message_get_IDE
};

/* Выделяем память под один экземпляр */
CEcoCAN1Message g_x8CC0027BE0A74E0DB34332D0C13B1A5AVTblCAN1Message = {
    &g_x8CC0027BE0A74E0DB34332D0C13B1A5AVTbl,
    0,
    0
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t createCEcoCAN1Message(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCAN20BMessage** ppICANMsg) {
    int16_t result = -1;
    CEcoCAN1Message* pCMe = 0;

    /* Проверка указателей */
    if (ppICANMsg == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_x8CC0027BE0A74E0DB34332D0C13B1A5AVTblCAN1Message;

    if (pCMe->m_cRef > 1) {
        pCMe->m_cRef++;
    } else {
        /* Установка счетчика ссылок на компонент */
        pCMe->m_cRef = 1;
    }

    /* Возврат указателя на интерфейс */
    *ppICANMsg = (IEcoCAN20BMessage*)pCMe;

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void deleteCEcoCAN1Message(/* in */ IEcoCAN20BMessage* pICANMsg) {
    CEcoCAN1Message* pCMe = (CEcoCAN1Message*)pICANMsg;

    if (pICANMsg != 0 ) {
    }
}
