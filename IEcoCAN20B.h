/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoCAN20B
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoCAN20B
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

#ifndef __I_ECO_CAN_2_0_B_H__
#define __I_ECO_CAN_2_0_B_H__

#include "IEcoBase1.h"

/* IEcoCAN20BMessage IID = {8CC0027B-E0A7-4E0D-B343-32D0C13B1A5A} */
#ifndef __IID_IEcoCAN20BMessage
static const UGUID IID_IEcoCAN20BMessage = {0x01, 0x10, 0x8C, 0xC0, 0x02, 0x7B, 0xE0, 0xA7, 0x4E, 0x0D, 0xB3, 0x43, 0x32, 0xD0, 0xC1, 0x3B, 0x1A, 0x5A};
#endif /* __IID_IEcoCAN20BMessage */

typedef struct IEcoCAN20BMessageVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoCAN20BMessage* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoCAN20BMessage* me);
    uint32_t (*Release)(/* in */ struct IEcoCAN20BMessage* me);

    /* IEcoCAN20AMessage */
    void (*set_Identifier)(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint16_t id11Bit);
    uint16_t (*get_Identifier)(/* in */ struct IEcoCAN20BMessage* me);
    void (*set_RTR)(/* in */ struct IEcoCAN20BMessage* me, /* in */ bool_t bit);
    bool_t (*get_RTR)(/* in */ struct IEcoCAN20BMessage* me);
    void (*set_DLC)(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint8_t length4Bit);
    uint8_t (*get_DLC)(/* in */ struct IEcoCAN20BMessage* me);
    void (*set_Data)(/* in */ struct IEcoCAN20BMessage* me, /* in */ byte_t* data);
    byte_t* (*get_Data)(/* in */ struct IEcoCAN20BMessage* me);
    void (*set_CRC)(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint16_t crc);
    uint16_t (*get_CRC)(/* in */ struct IEcoCAN20BMessage* me);

    /* IEcoCAN20BMessage */
    void (*set_ExtendedIdentifier)(/* in */ struct IEcoCAN20BMessage* me, /* in */ uint32_t id18Bit);
    uint32_t (*get_ExtendedIdentifier)(/* in */ struct IEcoCAN20BMessage* me);
    void (*set_SRR)(/* in */ struct IEcoCAN20BMessage* me, /* in */ bool_t bit);
    bool_t (*get_SRR)(/* in */ struct IEcoCAN20BMessage* me);
    void (*set_IDE)(/* in */ struct IEcoCAN20BMessage* me, /* in */ bool_t bit);
    bool_t (*get_IDE)(/* in */ struct IEcoCAN20BMessage* me);

} IEcoCAN20BMessageVTbl, *IEcoCAN20BMessageVTblPtr;

interface IEcoCAN20BMessage {
    struct IEcoCAN20BMessageVTbl *pVTbl;
} IEcoCAN20BMessage;

/* IEcoCAN20B IID = {CBA23E4B-7C97-440E-8EAF-9372DE4B644D} */
#ifndef __IID_IEcoCAN20B
static const UGUID IID_IEcoCAN20B = {0x01, 0x10, 0xCB, 0xA2, 0x3E, 0x4B, 0x7C, 0x97, 0x44, 0x0E, 0x8E, 0xAF, 0x93, 0x72, 0xDE, 0x4B, 0x64, 0x4D};
#endif /* __IID_IEcoCAN20B */

typedef struct IEcoCAN20BVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoCAN20B* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoCAN20B* me);
    uint32_t (*Release)(/* in */ struct IEcoCAN20B* me);

    /* IEcoCAN20B */
    int16_t (*Init)(/* in */ struct IEcoCAN20B* me);
    IEcoCAN20BMessage* (*get_Message)(/* in */ struct IEcoCAN20B* me);
    int16_t (*TransmittingMessage)(/* in */ struct IEcoCAN20B* me, /* in */ IEcoCAN20BMessage* pIMsg);
    int16_t (*ReceivingMessage)(/* in */ struct IEcoCAN20B* me, /* out */ IEcoCAN20BMessage** ppIMsg);
    int16_t (*set_Bitrate)(/* in */ struct IEcoCAN20B* me, /* in */ uint16_t speed);
    int16_t (*set_MessageFiltering)(/* in */ struct IEcoCAN20B* me, /* in */ uint32_t filter);

} IEcoCAN20BVTbl, *IEcoCAN20BVTblPtr;

interface IEcoCAN20B {
    struct IEcoCAN20BVTbl *pVTbl;
} IEcoCAN20B;


#endif /* __I_ECO_CAN_2_0_B_H__ */
