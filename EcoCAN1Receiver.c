/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoCAN1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Elena Uskova. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoCAN1.h"
#include "IdEcoSPI1.h"
#include "IEcoCAN20B.h"
#include "IEcoCAN20BMCP2515Controller.h"

byte_t msg1[6] = "Hello";
byte_t msg2[8] = {0x01, 0x01, 0x02, 0x03, 0x00, 0x05, 0x06, 0x07};

int16_t Delay(/*in*/ double_t milliseconds) {
    uint16_t count = 325;

    for (double_t i = 0; i < milliseconds; i++) {
        for (uint16_t j = 0; j < count; j++) {
            asm volatile ("NOP\n\t" ::: "memory");
        }
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoCAN20BMCP2515Controller* pIMCP2515 = 0;
    IEcoCAN20BMessage* pIMessage = 0;
    IEcoCAN20B* pICAN = 0;
    uint8_t iLen = 0;
    uint8_t index = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы с CAN */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCAN1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_77FD7CF25D7B463686FFC7FA2138B717);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы с SPI */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoSPI1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_DAA1B7FDA387445F9A04E119400ECB91);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif


    /* Получение тестируемого интерфейса */
    pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCAN1, 0, &IID_IEcoCAN20B, (void**) &pICAN);
    if (result != 0 && pICAN == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Инициализация CAN */
    result = pICAN->pVTbl->Init(pICAN);

    /* Получение интерфейса управления контроллером MCP2515 */
    pICAN->pVTbl->QueryInterface(pICAN, &IID_IEcoCAN20BMCP2515Controller, (void**)&pIMCP2515);
    if (result != 0 && pIMCP2515 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Инициализация контроллера */
    pIMCP2515->pVTbl->Init(pIMCP2515, 10);


    /* Пример 1: Получение кадра данных с маркировкой "67"
      ---------------                       -----------------
      |             |                       |               |
      | TRANSMITTER | ---- Data Frame ----> |  RECEIVER(s)  |
      |             |                       |               |
      ---------------                       -----------------
    */

    /* Настраиваем 2-й пин порта D на вывод */
    (*(volatile uint8_t *)(0x2A)) = 0B00000100;
    (*(volatile uint8_t *)(0x2B)) = 0B00000000;
    
    /* Получение сообщения */
    while (1) {
        //if (pICAN->pVTbl->IsReceive(pICAN)) {
            //iLen = pICAN->pVTbl->ReceivingMessage(pICAN, &pIMessage);
            //for(index = 0; index < iLen; index++) {
                //if(index==0) {
                    //(*(volatile uint8_t *)(0x2B)) = 0B00000100;
                    //Delay(500);
                //}
                //else if(index==4) {
                    //(*(volatile uint8_t *)(0x2B)) = 0B00000000;
                //}
            //}
        //}
        Delay(1000);
    }

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение тестируемого интерфейса */
    if (pICAN != 0) {
        pICAN->pVTbl->Release(pICAN);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

