/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoCAN1MCP2515Controller
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoCAN1MCP2515Controller
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2021 Elena Uskova. All rights reserved.
 * </автор>
 *
 */


#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "CEcoCAN1MCP2515Controller.h"
#include <time.h>

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCAN1
 * </описание>
 *
 */
int16_t CEcoCAN1MCP2515Controller_QueryInterface(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCAN20BMCP2515Controller) ) {
        *ppv = &pCMe->m_pVTblIMCP2515;
        pCMe->m_pVTblIMCP2515->AddRef((IEcoCAN20BMCP2515Controller*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIMCP2515;
        pCMe->m_pVTblIMCP2515->AddRef((IEcoCAN20BMCP2515Controller*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoCAN1
 * </описание>
 *
 */
uint32_t CEcoCAN1MCP2515Controller_AddRef(/* in */ struct IEcoCAN20BMCP2515Controller* me) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

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
 *   Функция Release для интерфейса IEcoCAN1
 * </описание>
 *
 */
uint32_t CEcoCAN1MCP2515Controller_Release(/* in */ struct IEcoCAN20BMCP2515Controller* me) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCAN1MCP2515Controller((IEcoCAN20BMCP2515Controller*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}


/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция - инициализация !!!!!!!!!!!
 * </описание>
 *
 */
int16_t CEcoCAN1MCP2515Controller_Init(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ int8_t pinChipSelect) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;
	CEcoCAN1* pCCAN = (CEcoCAN1*)me;  //?
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

	/* spi */
    pCMe->m_pISPI->pVTbl->Init(pCMe->m_pISPI, 0);
	CEcoCAN1MCP2515Controller_Reset(pCMe);
	CEcoCAN1->m_pVTblICAN20B->set_Bitrate(pCCAN, MCP_16MHZ, CAN_125KBPS);   //?
	CEcoCAN1MCP2515Controller_set_Mode(pCMe,CANCTRL_REQOP_NORMAL);
	
    return 0;
}

/*
 *
 * <сводка>
 *   Функция Transmit
 * </сводка>
 *
 * <описание>
 *   Функция
 *    передача байтов данных через SPI
 * </описание>
 *
 */
 
int16_t CEcoCAN1MCP2515Controller_Transmit(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ IEcoCAN20BMessage* pICANMsg) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, RXM0EID8);  //instruction LOAD TX BUFFER p69, 0x22
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, TXB1SIDH);   // адрес регистра TXB1SIDH - 0x41
	pCMe->m_pISPI->pVTbl->TransmitArray(pCMe->m_pISPI, pICANMsg->pVTbl->get_Data(pICANMsg), pICANMsg->pVTbl->get_DLC(pICANMsg));   // передача данных

    return 0;
}



/*
 *
 * <сводка>
 *   Функция Reset ????
 * </сводка>
 *
 * <описание>
 *   Функция
 *    
 * </описание>
 *
 */
void CEcoCAN1MCP2515Controller_Reset(/* in */ struct IEcoCAN20BMCP2515Controller* me) {
	CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

	/* Проверка указателей */
	if (me == 0 ) {
		return -1;
	}

	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_RESET);
	
	Delay(10);
	
	uint8_t zeros[14];
	memset(zeros, 0, sizeof(zeros));
	CEcoCAN1MCP2515Controller_writeRegisters(pCMe, TXB0CTRL, zeros, 14);
	CEcoCAN1MCP2515Controller_writeRegisters(pCMe, TXB1CTRL, zeros, 14);
	CEcoCAN1MCP2515Controller_writeRegisters(pCMe, TXB2CTRL, zeros, 14);

	CEcoCAN1MCP2515Controller_writeRegister(pCMe, RXB0CTRL, 0);
	CEcoCAN1MCP2515Controller_writeRegister(pCMe, RXB1CTRL, 0);

	CEcoCAN1MCP2515Controller_writeRegister(pCMe, CANINTE, RX0IF | RX1IF | ERRIF | MERRF);

	return 0;
}


/*
 *
 * <сводка>
 *   Функция Receive
 * </сводка>
 *
 * <описание>
 *   Функция
 *    прием байтов данных через SPI
 * </описание>
 *
 */
 
int16_t CEcoCAN1MCP2515Controller_Receive(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* out */ IEcoCAN20BMessage** ppICANMsg) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }
	
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_READ);  //instruction read p68
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, BFPCTRL);   // адрес регистра 
	int8_t byte = pCMe->m_pISPI->pVTbl->Receive(pCMe->m_pISPI);   
	
    return 0;
}

/*
 *
 * <сводка>
 *   Функция set_InterruptHandler !!!!!!!!!!!!!!
 * </сводка>
 *
 * <описание>
 *   Функция инициализация доп. аппаратных прерываний
 * </описание>
 *
 */
int16_t CEcoCAN1MCP2515Controller_set_InterruptHandler(/* in */ struct IEcoCAN20BMCP2515Controller* me, void (*handler)(void)) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция readRegister
 * </сводка>
 *
 * <описание>
 *   Функция
 *		чтение регистра по адресу в MCP2515
 * </описание>
 *
 */
 
uint8_t CEcoCAN1MCP2515Controller_readRegister(/* in */ struct IEcoCAN20BMCP2515Controller* me, uint8_t address) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }
	
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_READ);
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, address);
	uint8_t byte = pCMe->m_pISPI->pVTbl->Receive(pCMe->m_pISPI);

    return byte;
}


/*
 *
 * <сводка>
 *   Функция readRegisters 
 * </сводка>
 *
 * <описание>
 *   Функция
 *		чтение регистров по адресу в MCP2515
 * </описание>
 *
 */
 
void CEcoCAN1MCP2515Controller_readRegisters(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, uint8_t values[], uint8_t n) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }
	
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_READ);
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, address);
	for (uint8_t i = 0; i < n; i++) {
		values[i] = pCMe->m_pISPI->pVTbl->Receive(pCMe->m_pISPI);
	}
}


/*
 *
 * <сводка>
 *   Функция writeRegister
 * </сводка>
 *
 * <описание>
 *   Функция
 *      запись в регистры по адресу в MCP2515
 * </описание>
 *
 */
 
void CEcoCAN1MCP2515Controller_writeRegister(/* in */ struct IEcoCAN20BMCP2515Controller* me, unsigned char address, unsigned char value) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return;
    }

	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_WRITE);
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, address);
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, value);

}


/*
 *
 * <сводка>
 *   Функция writeRegisters
 * </сводка>
 *
 * <описание>
 *   Функция
 *      запись в регистры по адресу в MCP2515
 * </описание>
 *
 */
 
void CEcoCAN1MCP2515Controller_writeRegisters(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, /* in */ uint8_t values[], uint8_t n) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return;
    }

	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_WRITE);
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, address);
	for (uint8_t i = 0; i < n; i++) {
		pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, values[i]);
	}
}


/*
 *
 * <сводка>
 *   Функция set_Mode ??????????
 * </сводка>
 *
 * <описание>
 *   Функция
 *      настройка битовой синхронизации
 * </описание>
 *
 */
int16_t CEcoCAN1MCP2515Controller_set_Mode(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t mode) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

	// BIT MOD	
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, INSTRUCTION_BITMOD)
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, CANCTRL)
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, CANCTRL_REQOP)
	pCMe->m_pISPI->pVTbl->Transmit(pCMe->m_pISPI, mode)

	uint16_t end_time = clock() + 10;         //?
	bool modeMatch = false;
	while (clock() < end_time) {
		uint8_t newmode = CEcoCAN1MCP2515Controller_readRegister(CANSTAT);
		newmode &= CANSTAT_OPMOD;

		modeMatch = newmode == mode;

		if (modeMatch) {
			break;
		}
	}
    return modeMatch ? 0 : 1;
}

/*
 *
 * <сводка>
 *   Функция set_BitTiming
 * </сводка>
 *
 * <описание>
 *   Функция
 *      настройка битовой синхронизации
 * </описание>
 *
 */
int16_t CEcoCAN1MCP2515Controller_set_BitTiming(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t rCNF1, /* in */ uint8_t rCNF2, /* in */ uint8_t rCNF3) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }
	
	int8_t flag = IEcoCAN20BMCP2515ControllerVTbl->set_Mode(pCMe->m_pISPI, CANCTRL_REQOP_CONFIG);
	if (flag != 0) {
		return 1;
	}
	
	pCMe->m_pVTblIMCP2515->writeRegister(pCMe->m_pVTblIMCP2515, CNF1, rCNF1);
	pCMe->m_pVTblIMCP2515->writeRegister(pCMe->m_pVTblIMCP2515, CNF2, rCNF2);
	pCMe->m_pVTblIMCP2515->writeRegister(pCMe->m_pVTblIMCP2515, CNF3, rCNF3);
	

    return 0;
}

/*
 *
 * <сводка>
 *   Функция set_AcceptanceCriteria !!!!!!!!!!!!!!
 * </сводка>
 *
 * <описание>
 *   Функция
 *      настройка маски приема
 * </описание>
 *
 */
 
void CEcoCAN1MCP2515Controller_set_AcceptanceCriteria(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, unsigned long criterion, /* in */ uint8_t is_ext) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return;
    }
	
}


/*
 *
 * <сводка>
 *   Функция get_SPI
 * </сводка>
 *
 * <описание>
 *   Функция - возвращает указатель на SPI интерфейс
 * </описание>
 *
 */
 
IEcoSPI1*  CEcoCAN1MCP2515Controller_get_SPI(/* in */ struct IEcoCAN20BMCP2515Controller* me) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)me;

    /* Проверка указателей */
    if (me == 0 ) {
        return 0;
    }

    return pCMe->m_pISPI;
}

/* Create Virtual Table */
IEcoCAN20BMCP2515ControllerVTbl g_x5EADB6BE90B4452FAD9261B957C0E47DVTbl = {
    CEcoCAN1MCP2515Controller_QueryInterface,
    CEcoCAN1MCP2515Controller_AddRef,
    CEcoCAN1MCP2515Controller_Release,
    CEcoCAN1MCP2515Controller_Init,
    CEcoCAN1MCP2515Controller_Transmit,
    CEcoCAN1MCP2515Controller_Receive,
    CEcoCAN1MCP2515Controller_Reset,
    CEcoCAN1MCP2515Controller_set_InterruptHandler,
    CEcoCAN1MCP2515Controller_readRegister,
	CEcoCAN1MCP2515Controller_readRegisters,
    CEcoCAN1MCP2515Controller_writeRegister,
	CEcoCAN1MCP2515Controller_writeRegisters,
    CEcoCAN1MCP2515Controller_set_Mode,
    CEcoCAN1MCP2515Controller_set_BitTiming,
    CEcoCAN1MCP2515Controller_set_AcceptanceCriteria,
    CEcoCAN1MCP2515Controller_get_SPI
};

/* Выделяем память под один экземпляр */
CEcoCAN1MCP2515Controller g_x5EADB6BE90B4452FAD9261B957C0E47DVTblMCP2515 = {
    &g_x5EADB6BE90B4452FAD9261B957C0E47DVTbl,
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
int16_t createCEcoCAN1MCP2515Controller(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCAN20BMCP2515Controller** ppICAN) {
    int16_t result = -1;
    CEcoCAN1MCP2515Controller* pCMe = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;

    /* Проверка указателей */
    if (ppICAN == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_x5EADB6BE90B4452FAD9261B957C0E47DVTblMCP2515;

    if (pCMe->m_cRef > 1) {
        pCMe->m_cRef++;
    } else {
        /* Установка счетчика ссылок на компонент */
        pCMe->m_cRef = 1;

        /* Инициализация данных */
        result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 || pISys == 0) {
            /* Освобождение системного интерфейса в случае ошибки */
            return result;
        }
        /* Получение интерфейса для работы с интерфейсной шиной */
        result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
        if (result != 0 || pIBus == 0) {
            /* Освобождение в случае ошибки */
            pISys->pVTbl->Release(pISys);
            return result;
        }

        /* Получение тестируемого интерфейса */
        pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoSPI1, 0, &IID_IEcoSPI1, (void**) &pCMe->m_pISPI);
        /* Освобождение */
        pIBus->pVTbl->Release(pIBus);
        pISys->pVTbl->Release(pISys);
        if (result != 0 || pCMe->m_pISPI == 0) {
            /* Возврат в случае ошибки */
            return result;
        }
    }
    /* Возврат указателя на интерфейс */
    *ppICAN = (IEcoCAN20BMCP2515Controller*)pCMe;

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
void deleteCEcoCAN1MCP2515Controller(/* in */ IEcoCAN20BMCP2515Controller* pICAN) {
    CEcoCAN1MCP2515Controller* pCMe = (CEcoCAN1MCP2515Controller*)pICAN;

    if (pICAN != 0 ) {
    }
}
