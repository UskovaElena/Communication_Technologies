/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoCAN20A
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoCAN20A
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2021 Elena Uskova. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECO_CAN_2_0_A_H__
#define __I_ECO_CAN_2_0_A_H__

#include "IEcoBase1.h"

/* IEcoCAN20AMessage IID = {5F248D48-03E0-4355-9334-C5EE9C23D566} */
#ifndef __IID_IEcoCAN20AMessage
static const UGUID IID_IEcoCAN20AMessage = {0x01, 0x10, 0x5F, 0x24, 0x8D, 0x48, 0x03, 0xE0, 0x43, 0x55, 0x93, 0x34, 0xC5, 0xEE, 0x9C, 0x23, 0xD5, 0x66};
#endif /* __IID_IEcoCAN20AMessage */

typedef struct IEcoCAN20AMessageVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoCAN20AMessage* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoCAN20AMessage* me);
    uint32_t (*Release)(/* in */ struct IEcoCAN20AMessage* me);

    /* IEcoCAN20AMessage */
    void (*set_Identifier)(/* in */ struct IEcoCAN20AMessage* me, /* in */ uint16_t id11Bit);
    uint16_t (*get_Identifier)(/* in */ struct IEcoCAN20AMessage* me);
    void (*set_RTR)(/* in */ struct IEcoCAN20AMessage* me, /* in */ bool_t bit);
    bool_t (*get_RTR)(/* in */ struct IEcoCAN20AMessage* me);
    void (*set_DLC)(/* in */ struct IEcoCAN20AMessage* me, /* in */ uint8_t length4Bit);
    uint8_t (*get_DLC)(/* in */ struct IEcoCAN20AMessage* me);
    void (*set_Data)(/* in */ struct IEcoCAN20AMessage* me, /* in */ byte_t* data);
    byte_t* (*get_Data)(/* in */ struct IEcoCAN20AMessage* me);
    void (*set_CRC)(/* in */ struct IEcoCAN20AMessage* me, /* in */ uint16_t crc);
    uint16_t (*get_CRC)(/* in */ struct IEcoCAN20AMessage* me);

} IEcoCAN20AMessageVTbl, *IEcoCAN20AMessageVTblPtr;

interface IEcoCAN20AMessage {
    struct IEcoCAN20AMessageVTbl *pVTbl;
} IEcoCAN20AMessage;

/* IEcoCAN20A IID = {20EB0BF3-27CC-4EA3-B745-0786F0AD3917} */
#ifndef __IID_IEcoCAN20A
static const UGUID IID_IEcoCAN20A = {0x01, 0x10, 0x20, 0xEB, 0x0B, 0xF3, 0x27, 0xCC, 0x4E, 0xA3, 0xB7, 0x45, 0x07, 0x86, 0xF0, 0xAD, 0x39, 0x17};
#endif /* __IID_IEcoCAN20A */

typedef struct IEcoCAN20AVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoCAN20A* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoCAN20A* me);
    uint32_t (*Release)(/* in */ struct IEcoCAN20A* me);

    /* IEcoCAN20A */
    int16_t (*Init)(/* in */ struct IEcoCAN20A* me);
    IEcoCAN20AMessage* (*get_Message)(/* in */ struct IEcoCAN20A* me);
    int16_t (*TransmittingMessage)(/* in */ struct IEcoCAN20A* me, /* in */ IEcoCAN20AMessage* pIMsg);
    int16_t (*ReceivingMessage)(/* in */ struct IEcoCAN20A* me, /* out */ IEcoCAN20AMessage** ppIMsg);
    int16_t (*set_Bitrate)(/* in */ struct IEcoCAN20A* me, /* in */ uint16_t speed);
    int16_t (*set_MessageFiltering)(/* in */ struct IEcoCAN20A* me, /* in */ uint32_t filter);

} IEcoCAN20AVTbl, *IEcoCAN20AVTblPtr;

interface IEcoCAN20A {
    struct IEcoCAN20AVTbl *pVTbl;
} IEcoCAN20A;


#endif /* __I_ECO_CAN_2_0_A_H__ */
