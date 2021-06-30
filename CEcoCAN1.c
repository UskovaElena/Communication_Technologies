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
#include "CEcoCAN1.h"
#include "CEcoCAN1Message.h"
#include "CEcoCAN1MCP2515Controller.h"

extern IEcoCAN20BMCP2515ControllerVTbl g_x5EADB6BE90B4452FAD9261B957C0E47DVTbl;

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoCAN20B
 * </описание>
 *
 */
int16_t CEcoCAN1_QueryInterface(/* in */ struct IEcoCAN20B* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return result;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoCAN20A) ) {
        *ppv = &pCMe->m_pVTblICAN20B;
        pCMe->m_pVTblICAN20B->AddRef((IEcoCAN20B*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCAN20B) ) {
        *ppv = &pCMe->m_pVTblICAN20B;
        pCMe->m_pVTblICAN20B->AddRef((IEcoCAN20B*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCAN20BMCP2515Controller) ) {
        // Временно 
        *ppv = pCMe->m_pIMCP2515Controller;
        pCMe->m_pVTblICAN20B->AddRef((IEcoCAN20B*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblICAN20B;
        pCMe->m_pVTblICAN20B->AddRef((IEcoCAN20B*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoCAN20B
 * </описание>
 *
 */
uint32_t CEcoCAN1_AddRef(/* in */ struct IEcoCAN20B* me) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;

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
 *   Функция Release для интерфейса IEcoCAN20B
 * </описание>
 *
 */
uint32_t CEcoCAN1_Release(/* in */ struct IEcoCAN20B* me) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoCAN1((IEcoCAN20B*)pCMe);
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
 *   Функция
 * </описание>
 *
 */
int16_t CEcoCAN1_Init(/* in */ struct IEcoCAN20B* me) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    result = createCEcoCAN1MCP2515Controller((IEcoUnknown*)pCMe->m_pISys, 0, &pCMe->m_pIMCP2515Controller);

    return result;
}

/*
 *
 * <сводка>
 *   Функция get_Message
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
IEcoCAN20BMessage* CEcoCAN1_get_Message(/* in */ struct IEcoCAN20B* me) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return 0;
    }

    result = createCEcoCAN1Message((IEcoUnknown*)pCMe->m_pISys, 0,  &pCMe->m_pICANMsg);

    return pCMe->m_pICANMsg;
}

/*
 *
 * <сводка>
 *   Функция TransmittingMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t CEcoCAN1_TransmittingMessage(/* in */ struct IEcoCAN20B* me, /* in */ IEcoCAN20BMessage* pIMsg) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    result = pCMe->m_pIMCP2515Controller->pVTbl->Transmit(pCMe->m_pIMCP2515Controller, pIMsg);

    return result;
}

/*
 *
 * <сводка>
 *   Функция ReceivingMessage
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t CEcoCAN1_ReceivingMessage(/* in */ struct IEcoCAN20B* me, /* out */ IEcoCAN20BMessage** ppIMsg) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    result = pCMe->m_pIMCP2515Controller->pVTbl->Receive(pCMe->m_pIMCP2515Controller, ppIMsg);

    return result;
}

/*
 *
 * <сводка>
 *   Функция set_Bitrate  ???
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t CEcoCAN1_set_Bitrate(/* in */ struct IEcoCAN20B* me, /* in */ CAN_FREQUENCY freq, /* in */ CAN_SPEED speed) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }
	
	int8_t flag = IEcoCAN20BMCP2515ControllerVTbl->set_Mode(CEcoCAN1MCP2515Controller->m_pISPI, CANCTRL_REQOP_CONFIG);    // ???
	if (flag != 0) {
		return 1;
	}
	
	uint8_t set, cfg1, cfg2, cfg3;
	set = 1;
	
	switch (freq)
	{
		case (MCP_8MHZ):
		switch (speed)
		{
			case (CAN_5KBPS):                                               //   5KBPS
			cfg1 = MCP_8MHz_5kBPS_CFG1;
			cfg2 = MCP_8MHz_5kBPS_CFG2;
			cfg3 = MCP_8MHz_5kBPS_CFG3;
			break;

			case (CAN_10KBPS):                                              //  10KBPS
			cfg1 = MCP_8MHz_10kBPS_CFG1;
			cfg2 = MCP_8MHz_10kBPS_CFG2;
			cfg3 = MCP_8MHz_10kBPS_CFG3;
			break;

			case (CAN_20KBPS):                                              //  20KBPS
			cfg1 = MCP_8MHz_20kBPS_CFG1;
			cfg2 = MCP_8MHz_20kBPS_CFG2;
			cfg3 = MCP_8MHz_20kBPS_CFG3;
			break;

			case (CAN_31K25BPS):                                            //  31.25KBPS
			cfg1 = MCP_8MHz_31k25BPS_CFG1;
			cfg2 = MCP_8MHz_31k25BPS_CFG2;
			cfg3 = MCP_8MHz_31k25BPS_CFG3;
			break;

			case (CAN_33KBPS):                                              //  33.333KBPS
			cfg1 = MCP_8MHz_33k3BPS_CFG1;
			cfg2 = MCP_8MHz_33k3BPS_CFG2;
			cfg3 = MCP_8MHz_33k3BPS_CFG3;
			break;

			case (CAN_40KBPS):                                              //  40Kbps
			cfg1 = MCP_8MHz_40kBPS_CFG1;
			cfg2 = MCP_8MHz_40kBPS_CFG2;
			cfg3 = MCP_8MHz_40kBPS_CFG3;
			break;

			case (CAN_50KBPS):                                              //  50Kbps
			cfg1 = MCP_8MHz_50kBPS_CFG1;
			cfg2 = MCP_8MHz_50kBPS_CFG2;
			cfg3 = MCP_8MHz_50kBPS_CFG3;
			break;

			case (CAN_80KBPS):                                              //  80Kbps
			cfg1 = MCP_8MHz_80kBPS_CFG1;
			cfg2 = MCP_8MHz_80kBPS_CFG2;
			cfg3 = MCP_8MHz_80kBPS_CFG3;
			break;

			case (CAN_100KBPS):                                             // 100Kbps
			cfg1 = MCP_8MHz_100kBPS_CFG1;
			cfg2 = MCP_8MHz_100kBPS_CFG2;
			cfg3 = MCP_8MHz_100kBPS_CFG3;
			break;

			case (CAN_125KBPS):                                             // 125Kbps
			cfg1 = MCP_8MHz_125kBPS_CFG1;
			cfg2 = MCP_8MHz_125kBPS_CFG2;
			cfg3 = MCP_8MHz_125kBPS_CFG3;
			break;

			case (CAN_200KBPS):                                             // 200Kbps
			cfg1 = MCP_8MHz_200kBPS_CFG1;
			cfg2 = MCP_8MHz_200kBPS_CFG2;
			cfg3 = MCP_8MHz_200kBPS_CFG3;
			break;

			case (CAN_250KBPS):                                             // 250Kbps
			cfg1 = MCP_8MHz_250kBPS_CFG1;
			cfg2 = MCP_8MHz_250kBPS_CFG2;
			cfg3 = MCP_8MHz_250kBPS_CFG3;
			break;

			case (CAN_500KBPS):                                             // 500Kbps
			cfg1 = MCP_8MHz_500kBPS_CFG1;
			cfg2 = MCP_8MHz_500kBPS_CFG2;
			cfg3 = MCP_8MHz_500kBPS_CFG3;
			break;

			case (CAN_1000KBPS):                                            //   1Mbps
			cfg1 = MCP_8MHz_1000kBPS_CFG1;
			cfg2 = MCP_8MHz_1000kBPS_CFG2;
			cfg3 = MCP_8MHz_1000kBPS_CFG3;
			break;

			default:
			set = 0;
			break;
		}
		break;

		case (MCP_16MHZ):
		switch (speed)
		{
			case (CAN_5KBPS):                                               //   5Kbps
			cfg1 = MCP_16MHz_5kBPS_CFG1;
			cfg2 = MCP_16MHz_5kBPS_CFG2;
			cfg3 = MCP_16MHz_5kBPS_CFG3;
			break;

			case (CAN_10KBPS):                                              //  10Kbps
			cfg1 = MCP_16MHz_10kBPS_CFG1;
			cfg2 = MCP_16MHz_10kBPS_CFG2;
			cfg3 = MCP_16MHz_10kBPS_CFG3;
			break;

			case (CAN_20KBPS):                                              //  20Kbps
			cfg1 = MCP_16MHz_20kBPS_CFG1;
			cfg2 = MCP_16MHz_20kBPS_CFG2;
			cfg3 = MCP_16MHz_20kBPS_CFG3;
			break;

			case (CAN_33KBPS):                                              //  33.333Kbps
			cfg1 = MCP_16MHz_33k3BPS_CFG1;
			cfg2 = MCP_16MHz_33k3BPS_CFG2;
			cfg3 = MCP_16MHz_33k3BPS_CFG3;
			break;

			case (CAN_40KBPS):                                              //  40Kbps
			cfg1 = MCP_16MHz_40kBPS_CFG1;
			cfg2 = MCP_16MHz_40kBPS_CFG2;
			cfg3 = MCP_16MHz_40kBPS_CFG3;
			break;

			case (CAN_50KBPS):                                              //  50Kbps
			cfg1 = MCP_16MHz_50kBPS_CFG1;
			cfg2 = MCP_16MHz_50kBPS_CFG2;
			cfg3 = MCP_16MHz_50kBPS_CFG3;
			break;

			case (CAN_80KBPS):                                              //  80Kbps
			cfg1 = MCP_16MHz_80kBPS_CFG1;
			cfg2 = MCP_16MHz_80kBPS_CFG2;
			cfg3 = MCP_16MHz_80kBPS_CFG3;
			break;

			case (CAN_83K3BPS):                                             //  83.333Kbps
			cfg1 = MCP_16MHz_83k3BPS_CFG1;
			cfg2 = MCP_16MHz_83k3BPS_CFG2;
			cfg3 = MCP_16MHz_83k3BPS_CFG3;
			break;

			case (CAN_100KBPS):                                             // 100Kbps
			cfg1 = MCP_16MHz_100kBPS_CFG1;
			cfg2 = MCP_16MHz_100kBPS_CFG2;
			cfg3 = MCP_16MHz_100kBPS_CFG3;
			break;

			case (CAN_125KBPS):                                             // 125Kbps
			cfg1 = MCP_16MHz_125kBPS_CFG1;
			cfg2 = MCP_16MHz_125kBPS_CFG2;
			cfg3 = MCP_16MHz_125kBPS_CFG3;
			break;

			case (CAN_200KBPS):                                             // 200Kbps
			cfg1 = MCP_16MHz_200kBPS_CFG1;
			cfg2 = MCP_16MHz_200kBPS_CFG2;
			cfg3 = MCP_16MHz_200kBPS_CFG3;
			break;

			case (CAN_250KBPS):                                             // 250Kbps
			cfg1 = MCP_16MHz_250kBPS_CFG1;
			cfg2 = MCP_16MHz_250kBPS_CFG2;
			cfg3 = MCP_16MHz_250kBPS_CFG3;
			break;

			case (CAN_500KBPS):                                             // 500Kbps
			cfg1 = MCP_16MHz_500kBPS_CFG1;
			cfg2 = MCP_16MHz_500kBPS_CFG2;
			cfg3 = MCP_16MHz_500kBPS_CFG3;
			break;

			case (CAN_1000KBPS):                                            //   1Mbps
			cfg1 = MCP_16MHz_1000kBPS_CFG1;
			cfg2 = MCP_16MHz_1000kBPS_CFG2;
			cfg3 = MCP_16MHz_1000kBPS_CFG3;
			break;

			default:
			set = 0;
			break;
		}
		break;

		case (MCP_20MHZ):
		switch (speed)
		{
			case (CAN_33KBPS):                                              //  33.333Kbps
			cfg1 = MCP_20MHz_33k3BPS_CFG1;
			cfg2 = MCP_20MHz_33k3BPS_CFG2;
			cfg3 = MCP_20MHz_33k3BPS_CFG3;
			break;

			case (CAN_40KBPS):                                              //  40Kbps
			cfg1 = MCP_20MHz_40kBPS_CFG1;
			cfg2 = MCP_20MHz_40kBPS_CFG2;
			cfg3 = MCP_20MHz_40kBPS_CFG3;
			break;

			case (CAN_50KBPS):                                              //  50Kbps
			cfg1 = MCP_20MHz_50kBPS_CFG1;
			cfg2 = MCP_20MHz_50kBPS_CFG2;
			cfg3 = MCP_20MHz_50kBPS_CFG3;
			break;

			case (CAN_80KBPS):                                              //  80Kbps
			cfg1 = MCP_20MHz_80kBPS_CFG1;
			cfg2 = MCP_20MHz_80kBPS_CFG2;
			cfg3 = MCP_20MHz_80kBPS_CFG3;
			break;

			case (CAN_83K3BPS):                                             //  83.333Kbps
			cfg1 = MCP_20MHz_83k3BPS_CFG1;
			cfg2 = MCP_20MHz_83k3BPS_CFG2;
			cfg3 = MCP_20MHz_83k3BPS_CFG3;
			break;

			case (CAN_100KBPS):                                             // 100Kbps
			cfg1 = MCP_20MHz_100kBPS_CFG1;
			cfg2 = MCP_20MHz_100kBPS_CFG2;
			cfg3 = MCP_20MHz_100kBPS_CFG3;
			break;

			case (CAN_125KBPS):                                             // 125Kbps
			cfg1 = MCP_20MHz_125kBPS_CFG1;
			cfg2 = MCP_20MHz_125kBPS_CFG2;
			cfg3 = MCP_20MHz_125kBPS_CFG3;
			break;

			case (CAN_200KBPS):                                             // 200Kbps
			cfg1 = MCP_20MHz_200kBPS_CFG1;
			cfg2 = MCP_20MHz_200kBPS_CFG2;
			cfg3 = MCP_20MHz_200kBPS_CFG3;
			break;

			case (CAN_250KBPS):                                             // 250Kbps
			cfg1 = MCP_20MHz_250kBPS_CFG1;
			cfg2 = MCP_20MHz_250kBPS_CFG2;
			cfg3 = MCP_20MHz_250kBPS_CFG3;
			break;

			case (CAN_500KBPS):                                             // 500Kbps
			cfg1 = MCP_20MHz_500kBPS_CFG1;
			cfg2 = MCP_20MHz_500kBPS_CFG2;
			cfg3 = MCP_20MHz_500kBPS_CFG3;
			break;

			case (CAN_1000KBPS):                                            //   1Mbps
			cfg1 = MCP_20MHz_1000kBPS_CFG1;
			cfg2 = MCP_20MHz_1000kBPS_CFG2;
			cfg3 = MCP_20MHz_1000kBPS_CFG3;
			break;

			default:
			set = 0;
			break;
		}
		break;

		default:
		set = 0;
		break;
	}
	
	 if (set) {
		 /*CEcoCAN1MCP2515Controller->m_pVTblIMCP2515->writeRegister(CEcoCAN1MCP2515Controller->m_pVTblIMCP2515, CNF1, cfg1); 
		 CEcoCAN1MCP2515Controller->m_pVTblIMCP2515->writeRegister(CEcoCAN1MCP2515Controller->m_pVTblIMCP2515, CNF2, cfg2);
		 CEcoCAN1MCP2515Controller->m_pVTblIMCP2515->writeRegister(CEcoCAN1MCP2515Controller->m_pVTblIMCP2515, CNF3, cfg3);*/
		 CEcoCAN1MCP2515Controller->m_pVTblIMCP2515->set_BitTiming(CEcoCAN1MCP2515Controller->m_pVTblIMCP2515, cfg1, cfg2, cfg3);
		 result = 0;
	 }
	 else {
		 result = 1;
	 }
	 

    return result;
}

/*
 *
 * <сводка>
 *   Функция set_MessageFiltering  !!!!!!!!!!!!!!!!!!!!
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t CEcoCAN1_set_MessageFiltering(/* in */ struct IEcoCAN20B* me, /* in */ uint32_t filter) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    return result;
}


/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра  ?????
 * </описание>
 *
 */
int16_t initCEcoCAN1(/*in*/ struct IEcoCAN20B* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoCAN1* pCMe = (CEcoCAN1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }


    return result;
}


/* Create Virtual Table */
IEcoCAN20BVTbl g_xCBA23E4B7C97440E8EAF9372DE4B644DVTbl = {
    CEcoCAN1_QueryInterface,
    CEcoCAN1_AddRef,
    CEcoCAN1_Release,
    CEcoCAN1_Init,
    CEcoCAN1_get_Message,
    CEcoCAN1_TransmittingMessage,
    CEcoCAN1_ReceivingMessage,
    CEcoCAN1_set_Bitrate,
    CEcoCAN1_set_MessageFiltering
};


/* Выделяем память под один экземпляр */
CEcoCAN1 g_xCBA23E4B7C97440E8EAF9372DE4B644DVTblCAN1 = {
    &g_xCBA23E4B7C97440E8EAF9372DE4B644DVTbl,
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
int16_t createCEcoCAN1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoCAN20B** ppICAN) {
    int16_t result = -1;
    CEcoCAN1* pCMe = 0;

    /* Проверка указателей */
    if (ppICAN == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение указателя на структуру компонента расположенной в области инициализированных данных */
    pCMe = &g_xCBA23E4B7C97440E8EAF9372DE4B644DVTblCAN1;

    pCMe->m_pISys = pIUnkSystem;
    if (pCMe->m_cRef > 1) {
        pCMe->m_cRef++;
    } else {
        /* Установка счетчика ссылок на компонент */
        pCMe->m_cRef = 1;
    }

    /* Возврат указателя на интерфейс */
    *ppICAN = (IEcoCAN20B*)pCMe;

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
void deleteCEcoCAN1(/* in */ IEcoCAN20B* pICAN) {
    CEcoCAN1* pCMe = (CEcoCAN1*)pICAN;

    if (pICAN != 0 ) {
    }
}
