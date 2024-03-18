#ifndef PORT_H
#define PORT_H

typedef struct
{
	volatile unsigned int PORT_PCR0;
	volatile unsigned int PORT_PCR1;
	volatile unsigned int PORT_PCR2;
	volatile unsigned int PORT_PCR3;
	volatile unsigned int PORT_PCR4;
	volatile unsigned int PORT_PCR5;
	volatile unsigned int PORT_PCR6;
	volatile unsigned int PORT_PCR7;
	volatile unsigned int PORT_PCR8;
	volatile unsigned int PORT_PCR9;
	volatile unsigned int PORT_PCR10;
	volatile unsigned int PORT_PCR11;
	volatile unsigned int PORT_PCR12;
	volatile unsigned int PORT_PCR13;
	volatile unsigned int PORT_PCR14;
	volatile unsigned int PORT_PCR15;
	volatile unsigned int PORT_PCR16;
	volatile unsigned int PORT_PCR17;
	volatile unsigned int PORT_PCR18;
	volatile unsigned int PORT_PCR19;
	volatile unsigned int PORT_PCR20;
	volatile unsigned int PORT_PCR21;
	volatile unsigned int PORT_PCR22;
	volatile unsigned int PORT_PCR23;
	volatile unsigned int PORT_PCR24;
	volatile unsigned int PORT_PCR25;
	volatile unsigned int PORT_PCR26;
	volatile unsigned int PORT_PCR27;
	volatile unsigned int PORT_PCR28;
	volatile unsigned int PORT_PCR29;
	volatile unsigned int PORT_PCR30;
	volatile unsigned int PORT_PCR31;
	volatile unsigned int PORT_GPCLR;
	volatile unsigned int PORT_GPCHR;
	volatile unsigned int PORT_GICLR;
	volatile unsigned int PORT_GICHR;
	volatile unsigned int RESERVED_1[4];
	volatile unsigned int PORT_ISFR;
	volatile unsigned int RESERVED_2[7];
	volatile unsigned int PORT_DFER;
	volatile unsigned int PORT_DFCR;
	volatile unsigned int PORT_DFWR;
}PCR_TYPE;

#define PORTA_PCR_BASE (0x40049000u)
#define PORTA_PCR ((PCR_TYPE*)PORTA_PCR_BASE)

#define PORTB_PCR_BASE (0x4004A000u)
#define PORTB_PCR ((PCR_TYPE*)PORTB_PCR_BASE)

#define PORTC_PCR_BASE (0x4004B000u)
#define PORTC_PCR ((PCR_TYPE*)PORTC_PCR_BASE)

#define PORTD_PCR_BASE (0x4004C000u)
#define PORTD_PCR ((PCR_TYPE*)PORTD_PCR_BASE)

#define PORTE_PCR_BASE (0x4004D000u)
#define PORTE_PCR ((PCR_TYPE*)PORTE_PCR_BASE)

#endif
