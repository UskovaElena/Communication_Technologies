/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoCAN20BMCP2515Controller
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoCAN20BMCP2515Controller
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

#ifndef __I_ECO_CAN_2_0_B_MCP2515_CONTROLLER_H__
#define __I_ECO_CAN_2_0_B_MCP2515_CONTROLLER_H__

#include "IEcoBase1.h"
#include "IEcoCAN20B.h"
#include "IEcoSPI1.h"

/*  Instructions  */

#define INSTRUCTION_WRITE       0x02
#define INSTRUCTION_READ        0x03
#define INSTRUCTION_BITMOD      0x05
#define INSTRUCTION_LOAD_TX_B0S 0x40
#define INSTRUCTION_LOAD_TX_B0D 0x41
#define INSTRUCTION_LOAD_TX_B1S 0x42
#define INSTRUCTION_LOAD_TX_B1D 0x43
#define INSTRUCTION_LOAD_TX_B2S 0x44
#define INSTRUCTION_LOAD_TX_B2D 0x45
#define INSTRUCTION_RTS_TX0     0x81
#define INSTRUCTION_RTS_TX1     0x82
#define INSTRUCTION_RTS_TX2     0x84
#define INSTRUCTION_RTS_TXALL   0x87
#define INSTRUCTION_READ_RX_B0S 0x90
#define INSTRUCTION_READ_RX_B0D 0x92
#define INSTRUCTION_READ_RX_B1S 0x94
#define INSTRUCTION_READ_RX_B1D 0x96
#define INSTRUCTION_READ_STATUS 0xA0
#define INSTRUCTION_RX_STATUS   0xB0
#define INSTRUCTION_RESET       0xC0



/*  Registers  */

#define		RXF0SIDH	0x00
#define		RXF0SIDL	0x01
#define		RXF0EID8	0x02
#define		RXF0EID0	0x03
#define		RXF1SIDH	0x04
#define		RXF1SIDL	0x05
#define		RXF1EID8	0x06
#define		RXF1EID0	0x07
#define		RXF2SIDH	0x08
#define		RXF2SIDL	0x09
#define		RXF2EID8	0x0A
#define		RXF2EID0	0x0B
#define		BFPCTRL		0x0C
#define		TXRTSCTRL	0x0D
#define		CANSTAT     0x0E
#define		CANCTRL     0x0F

#define		RXF3SIDH	0x10
#define		RXF3SIDL	0x11
#define		RXF3EID8	0x12
#define		RXF3EID0	0x13
#define		RXF4SIDH	0x14
#define		RXF4SIDL	0x15
#define		RXF4EID8	0x16
#define		RXF4EID0	0x17
#define		RXF5SIDH	0x18
#define		RXF5SIDL	0x19
#define		RXF5EID8	0x1A
#define		RXF5EID0	0x1B
#define		TEC	     	0x1C
#define		REC	    	0x1D

#define		RXM0SIDH	0x20
#define		RXM0SIDL	0x21
#define		RXM0EID8	0x22
#define		RXM0EID0	0x23
#define		RXM1SIDH	0x24
#define		RXM1SIDL	0x25
#define		RXM1EID8	0x26
#define		RXM1EID0	0x27
#define		CNF3		0x28
#define		CNF2		0x29
#define		CNF1		0x2A
#define		CANINTE		0x2B // Установка флагов прерываний
#define		CANINTF		0x2C // INTERRUPT FLAG
#define		EFLG		0x2D

#define		TXB0CTRL	0x30
#define		TXB0SIDH	0x31 // Идентификатор стандартного сообщения приемного буфера 0, старший байт
#define		TXB0SIDL	0x32 // Идентификатор стандартного сообщения приемного буфера 0, младший байт
#define		TXB0EID8	0x33 // Идентификатор расширенного сообщения приемного буфера 0, старший байт
#define		TXB0EID0	0x34 // Идентификатор расширенного сообщения приемного буфера 0, младший байт
#define		TXB0DLC		0x35
#define		TXB0D0		0x36 // Байт данных 0 передающего буфера 0, data
#define		TXB0D1		0x37
#define		TXB0D2		0x38
#define		TXB0D3		0x39
#define		TXB0D4		0x3A
#define		TXB0D5		0x3B
#define		TXB0D6		0x3C
#define		TXB0D7		0x3D // Байт данных 7 передающего буфера 0

#define		TXB1CTRL	0x40
#define		TXB1SIDH	0x41 // Идентификатор стандартного сообщения приемного буфера 0, СТАРШИЙ байт
#define		TXB1SIDL	0x42 // Идентификатор стандартного сообщения приемного буфера 0, МЛАДШИЙ байт
#define		TXB1EID8	0x43 // Идентификатор расширенного сообщения приемного буфера 0, СТАРШИЙ байт
#define		TXB1EID0	0x44 // Идентификатор расширенного сообщения приемного буфера 0, МЛАДШИЙ байт
#define		TXB1DLC		0x45
#define		TXB1D0		0x46  // Data start
#define		TXB1D1		0x47
#define		TXB1D2		0x48
#define		TXB1D3		0x49
#define		TXB1D4		0x4A
#define		TXB1D5		0x4B
#define		TXB1D6		0x4C
#define		TXB1D7		0x4D // Data end

#define		TXB2CTRL	0x50
#define		TXB2SIDH	0x51 // Идентификатор стандартного сообщения приемного буфера 0, СТАРШИЙ байт
#define		TXB2SIDL	0x52 // Идентификатор стандартного сообщения приемного буфера 0, МЛАДШИЙ байт
#define		TXB2EID8	0x53 // Идентификатор расширенного сообщения приемного буфера 0, СТАРШИЙ байт
#define		TXB2EID0	0x54 // Идентификатор расширенного сообщения приемного буфера 0, МЛАДШИЙ байт
#define		TXB2DLC		0x55
#define		TXB2D0		0x56  // Data start
#define		TXB2D1		0x57
#define		TXB2D2		0x58
#define		TXB2D3		0x59
#define		TXB2D4		0x5A
#define		TXB2D5		0x5B
#define		TXB2D6		0x5C
#define		TXB2D7		0x5D  // Data end

#define		RXB0CTRL	0x60
#define		RXB0SIDH	0x61 // Идентификатор стандартного сообщения приемного буфера 0, СТАРШИЙ байт
#define		RXB0SIDL	0x62 // Идентификатор стандартного сообщения приемного буфера 0, МЛАДШИЙ байт
#define		RXB0EID8	0x63 // Идентификатор расширенного сообщения приемного буфера 0, СТАРШИЙ байт
#define		RXB0EID0	0x64 // Идентификатор расширенного сообщения приемного буфера 0, МЛАДШИЙ байт
#define		RXB0DLC		0x65
#define		RXB0D0		0x66  // Data start
#define		RXB0D1		0x67
#define		RXB0D2		0x68
#define		RXB0D3		0x69
#define		RXB0D4		0x6A
#define		RXB0D5		0x6B
#define		RXB0D6		0x6C
#define		RXB0D7		0x6D // Data end

#define		RXB1CTRL	0x70
#define		RXB1SIDH	0x71
#define		RXB1SIDL	0x72
#define		RXB1EID8	0x73
#define		RXB1EID0	0x74
#define		RXB1DLC		0x75
#define		RXB1D0		0x76  // Data start
#define		RXB1D1		0x77
#define		RXB1D2		0x78
#define		RXB1D3		0x79
#define		RXB1D4		0x7A
#define		RXB1D5		0x7B
#define		RXB1D6		0x7C
#define		RXB1D7		0x7D  // Data end



#define CANSTAT_OPMOD  0xE0

#define CANCTRL_REQOP  0xE0
#define CANCTRL_ABAT   0x10
#define CANCTRL_OSM    0x08
#define CANCTRL_CLKEN  0x04
#define CANCTRL_CLKPRE 0x03


#define RX0IF  0x01
#define RX1IF  0x02
#define TX0IF  0x04
#define TX1IF  0x08
#define TX2IF  0x10
#define ERRIF  0x20
#define WAKIF  0x40
#define MERRF  0x80

 /*   CANCTRL_REQOP MODE  */
#define	CANCTRL_REQOP_NORMAL     = 0x00,
#define	CANCTRL_REQOP_SLEEP      = 0x20,
#define	CANCTRL_REQOP_LOOPBACK   = 0x40,
#define	CANCTRL_REQOP_LISTENONLY = 0x60,
#define	CANCTRL_REQOP_CONFIG     = 0x80,
#define	CANCTRL_REQOP_POWERUP    = 0xE0




/*
 *  Speed 8M
 */
#define MCP_8MHz_1000kBPS_CFG1 (0x00)
#define MCP_8MHz_1000kBPS_CFG2 (0x80)
#define MCP_8MHz_1000kBPS_CFG3 (0x80)

#define MCP_8MHz_500kBPS_CFG1 (0x00)
#define MCP_8MHz_500kBPS_CFG2 (0x90)
#define MCP_8MHz_500kBPS_CFG3 (0x82)

#define MCP_8MHz_250kBPS_CFG1 (0x00)
#define MCP_8MHz_250kBPS_CFG2 (0xB1)
#define MCP_8MHz_250kBPS_CFG3 (0x85)

#define MCP_8MHz_200kBPS_CFG1 (0x00)
#define MCP_8MHz_200kBPS_CFG2 (0xB4)
#define MCP_8MHz_200kBPS_CFG3 (0x86)

#define MCP_8MHz_125kBPS_CFG1 (0x01)
#define MCP_8MHz_125kBPS_CFG2 (0xB1)
#define MCP_8MHz_125kBPS_CFG3 (0x85)

#define MCP_8MHz_100kBPS_CFG1 (0x01)
#define MCP_8MHz_100kBPS_CFG2 (0xB4)
#define MCP_8MHz_100kBPS_CFG3 (0x86)

#define MCP_8MHz_80kBPS_CFG1 (0x01)
#define MCP_8MHz_80kBPS_CFG2 (0xBF)
#define MCP_8MHz_80kBPS_CFG3 (0x87)

#define MCP_8MHz_50kBPS_CFG1 (0x03)
#define MCP_8MHz_50kBPS_CFG2 (0xB4)
#define MCP_8MHz_50kBPS_CFG3 (0x86)

#define MCP_8MHz_40kBPS_CFG1 (0x03)
#define MCP_8MHz_40kBPS_CFG2 (0xBF)
#define MCP_8MHz_40kBPS_CFG3 (0x87)

#define MCP_8MHz_33k3BPS_CFG1 (0x47)
#define MCP_8MHz_33k3BPS_CFG2 (0xE2)
#define MCP_8MHz_33k3BPS_CFG3 (0x85)

#define MCP_8MHz_31k25BPS_CFG1 (0x07)
#define MCP_8MHz_31k25BPS_CFG2 (0xA4)
#define MCP_8MHz_31k25BPS_CFG3 (0x84)

#define MCP_8MHz_20kBPS_CFG1 (0x07)
#define MCP_8MHz_20kBPS_CFG2 (0xBF)
#define MCP_8MHz_20kBPS_CFG3 (0x87)

#define MCP_8MHz_10kBPS_CFG1 (0x0F)
#define MCP_8MHz_10kBPS_CFG2 (0xBF)
#define MCP_8MHz_10kBPS_CFG3 (0x87)

#define MCP_8MHz_5kBPS_CFG1 (0x1F)
#define MCP_8MHz_5kBPS_CFG2 (0xBF)
#define MCP_8MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 16M
 */
#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xF0)
#define MCP_16MHz_500kBPS_CFG3 (0x86)

#define MCP_16MHz_250kBPS_CFG1 (0x41)
#define MCP_16MHz_250kBPS_CFG2 (0xF1)
#define MCP_16MHz_250kBPS_CFG3 (0x85)

#define MCP_16MHz_200kBPS_CFG1 (0x01)
#define MCP_16MHz_200kBPS_CFG2 (0xFA)
#define MCP_16MHz_200kBPS_CFG3 (0x87)

#define MCP_16MHz_125kBPS_CFG1 (0x03)
#define MCP_16MHz_125kBPS_CFG2 (0xF0)
#define MCP_16MHz_125kBPS_CFG3 (0x86)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xFA)
#define MCP_16MHz_100kBPS_CFG3 (0x87)

#define MCP_16MHz_80kBPS_CFG1 (0x03)
#define MCP_16MHz_80kBPS_CFG2 (0xFF)
#define MCP_16MHz_80kBPS_CFG3 (0x87)

#define MCP_16MHz_83k3BPS_CFG1 (0x03)
#define MCP_16MHz_83k3BPS_CFG2 (0xBE)
#define MCP_16MHz_83k3BPS_CFG3 (0x07)

#define MCP_16MHz_50kBPS_CFG1 (0x07)
#define MCP_16MHz_50kBPS_CFG2 (0xFA)
#define MCP_16MHz_50kBPS_CFG3 (0x87)

#define MCP_16MHz_40kBPS_CFG1 (0x07)
#define MCP_16MHz_40kBPS_CFG2 (0xFF)
#define MCP_16MHz_40kBPS_CFG3 (0x87)

#define MCP_16MHz_33k3BPS_CFG1 (0x4E)
#define MCP_16MHz_33k3BPS_CFG2 (0xF1)
#define MCP_16MHz_33k3BPS_CFG3 (0x85)

#define MCP_16MHz_20kBPS_CFG1 (0x0F)
#define MCP_16MHz_20kBPS_CFG2 (0xFF)
#define MCP_16MHz_20kBPS_CFG3 (0x87)

#define MCP_16MHz_10kBPS_CFG1 (0x1F)
#define MCP_16MHz_10kBPS_CFG2 (0xFF)
#define MCP_16MHz_10kBPS_CFG3 (0x87)

#define MCP_16MHz_5kBPS_CFG1 (0x3F)
#define MCP_16MHz_5kBPS_CFG2 (0xFF)
#define MCP_16MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 20M
 */
#define MCP_20MHz_1000kBPS_CFG1 (0x00)
#define MCP_20MHz_1000kBPS_CFG2 (0xD9)
#define MCP_20MHz_1000kBPS_CFG3 (0x82)

#define MCP_20MHz_500kBPS_CFG1 (0x00)
#define MCP_20MHz_500kBPS_CFG2 (0xFA)
#define MCP_20MHz_500kBPS_CFG3 (0x87)

#define MCP_20MHz_250kBPS_CFG1 (0x41)
#define MCP_20MHz_250kBPS_CFG2 (0xFB)
#define MCP_20MHz_250kBPS_CFG3 (0x86)

#define MCP_20MHz_200kBPS_CFG1 (0x01)
#define MCP_20MHz_200kBPS_CFG2 (0xFF)
#define MCP_20MHz_200kBPS_CFG3 (0x87)

#define MCP_20MHz_125kBPS_CFG1 (0x03)
#define MCP_20MHz_125kBPS_CFG2 (0xFA)
#define MCP_20MHz_125kBPS_CFG3 (0x87)

#define MCP_20MHz_100kBPS_CFG1 (0x04)
#define MCP_20MHz_100kBPS_CFG2 (0xFA)
#define MCP_20MHz_100kBPS_CFG3 (0x87)

#define MCP_20MHz_83k3BPS_CFG1 (0x04)
#define MCP_20MHz_83k3BPS_CFG2 (0xFE)
#define MCP_20MHz_83k3BPS_CFG3 (0x87)

#define MCP_20MHz_80kBPS_CFG1 (0x04)
#define MCP_20MHz_80kBPS_CFG2 (0xFF)
#define MCP_20MHz_80kBPS_CFG3 (0x87)

#define MCP_20MHz_50kBPS_CFG1 (0x09)
#define MCP_20MHz_50kBPS_CFG2 (0xFA)
#define MCP_20MHz_50kBPS_CFG3 (0x87)

#define MCP_20MHz_40kBPS_CFG1 (0x09)
#define MCP_20MHz_40kBPS_CFG2 (0xFF)
#define MCP_20MHz_40kBPS_CFG3 (0x87)

#define MCP_20MHz_33k3BPS_CFG1 (0x0B)
#define MCP_20MHz_33k3BPS_CFG2 (0xFF)
#define MCP_20MHz_33k3BPS_CFG3 (0x87)

enum CAN_FREQUENCY {
	MCP_20MHZ,
	MCP_16MHZ,
	MCP_8MHZ
};

enum CAN_SPEED {
	CAN_5KBPS,
	CAN_10KBPS,
	CAN_20KBPS,
	CAN_31K25BPS,
	CAN_33KBPS,
	CAN_40KBPS,
	CAN_50KBPS,
	CAN_80KBPS,
	CAN_83K3BPS,
	CAN_95KBPS,
	CAN_100KBPS,
	CAN_125KBPS,
	CAN_200KBPS,
	CAN_250KBPS,
	CAN_500KBPS,
	CAN_1000KBPS
};


/* IEcoCAN20BMCP2515Controller IID = {5EADB6BE-90B4-452F-AD92-61B957C0E47D} */
#ifndef __IID_IEcoCAN20BMCP2515Controller
static const UGUID IID_IEcoCAN20BMCP2515Controller = {0x01, 0x10, 0x5E, 0xAD, 0xB6, 0xBE, 0x90, 0xB4, 0x45, 0x2F, 0xAD, 0x92, 0x61, 0xB9, 0x57, 0xC0, 0xE4, 0x7D};
#endif /* __IID_IEcoCAN20BMCP2515Controller */

typedef struct IEcoCAN20BMCP2515ControllerVTbl {

    /* IEcoUnknown */
    int16_t (*QueryInterface)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (*AddRef)(/* in */ struct IEcoCAN20BMCP2515Controller* me);
    uint32_t (*Release)(/* in */ struct IEcoCAN20BMCP2515Controller* me);

    /* IEcoCAN20BMCP2515Controller */
    int16_t (*Init)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ int8_t pinChipSelect);
    int16_t (*Transmit)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ IEcoCAN20BMessage* pICANMsg);
    int16_t (*Receive)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* out */ IEcoCAN20BMessage** ppICANMsg);
    void (*Reset)(/* in */ struct IEcoCAN20BMCP2515Controller* me);
    int16_t (*set_InterruptHandler)(/* in */ struct IEcoCAN20BMCP2515Controller* me, void (*handler)(void));
    uint8_t (*readRegister)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address);
	void (*readRegisters)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, uint8_t values[], uint8_t n);
    void (*writeRegister)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, /* in */ uint8_t value);
	void (*writeRegisters)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, /* in */ uint8_t values[], uint8_t n);
    int16_t (*set_Mode)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t mode);
    int16_t (*set_BitTiming)(/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t rCNF1, /* in */ uint8_t rCNF2, /* in */ uint8_t rCNF3); // настройка битовой синхронизации
    void (*set_AcceptanceCriteria) (/* in */ struct IEcoCAN20BMCP2515Controller* me, /* in */ uint8_t address, unsigned long criterion, /* in */ uint8_t is_ext); // настройка маски приема
    IEcoSPI1* (*get_SPI) (/* in */ struct IEcoCAN20BMCP2515Controller* me);

} IEcoCAN20BMCP2515ControllerVTbl, *IEcoCAN20BMCP2515ControllerVTblPtr;

interface IEcoCAN20BMCP2515Controller {
    struct IEcoCAN20BMCP2515ControllerVTbl *pVTbl;
} IEcoCAN20BMCP2515Controller;


#endif /* __I_ECO_CAN_2_0_B_MCP2515_CONTROLLER_H__ */
