#ifndef PCC_H
#define PCC_H

typedef struct
{
	volatile unsigned int PCC_FTFC;
	volatile unsigned int PCC_DMAMUX;
	volatile unsigned int RESERVED_1[2];
	volatile unsigned int PCC_FlexCAN0;
	volatile unsigned int PCC_FlexCAN1;
	volatile unsigned int PCC_FTM3;
	volatile unsigned int PCC_ADC1;
	volatile unsigned int RESERVED_2[3];
	volatile unsigned int PCC_FlexCAN2;
	volatile unsigned int PCC_LPSPI0;
	volatile unsigned int PCC_LPSPI1;
	volatile unsigned int PCC_LPSPI2;
	volatile unsigned int RESERVED_3[2];
	volatile unsigned int PCC_PDB1;
	volatile unsigned int PCC_CRC;
	volatile unsigned int RESERVED_4[3];
	volatile unsigned int PCC_PDB0;
	volatile unsigned int PCC_LPIT;
	volatile unsigned int PCC_FTM0;
	volatile unsigned int PCC_FTM1;
	volatile unsigned int PCC_FTM2;
	volatile unsigned int PCC_ADC0;
	volatile unsigned int RESERVED_5[1];
	volatile unsigned int PCC_RTC;
	volatile unsigned int RESERVED_6[2];
	volatile unsigned int PCC_LPTMR0;
	volatile unsigned int RESERVED_7[8];
	volatile unsigned int PCC_PORTA;
	volatile unsigned int PCC_PORTB;
	volatile unsigned int PCC_PORTC;
	volatile unsigned int PCC_PORTD;
	volatile unsigned int PCC_PORTE;
	volatile unsigned int RESERVED_8[6];
	volatile unsigned int PCC_SAI0;
	volatile unsigned int PCC_SAI1;
	volatile unsigned int RESERVED_9[4];
	volatile unsigned int PCC_FlexIO;
	volatile unsigned int RESERVED_10[6];
	volatile unsigned int PCC_EWM;
	volatile unsigned int RESERVED_11[4];
	volatile unsigned int PCC_LPI2C0;
	volatile unsigned int PCC_LPI2C1;
	volatile unsigned int RESERVED_12[2];
	volatile unsigned int PCC_LPUART0;
	volatile unsigned int PCC_LPUART1;
	volatile unsigned int PCC_LPUART2;
	volatile unsigned int RESERVED_13[1];
	volatile unsigned int PCC_FTM4;
	volatile unsigned int PCC_FTM5;
	volatile unsigned int PCC_FTM6;
	volatile unsigned int PCC_FTM7;
	volatile unsigned int RESERVED_14[1];
	volatile unsigned int PCC_CMP0;
	volatile unsigned int RESERVED_15[2];
	volatile unsigned int PCC_QSPI;
	volatile unsigned int RESERVED_16[2];
	volatile unsigned int PCC_ENET;
}PCC_TYPE;

#define PCC_BASE_ADDRESS (0x40065000u + 0x80u)
#define PCC ((PCC_TYPE*)PCC_BASE_ADDRESS)

#endif
