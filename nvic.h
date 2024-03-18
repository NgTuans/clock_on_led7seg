#ifndef NVIC_H
#define NVIC_H

#define PORTA_Interrupt 	59
#define PORTB_Interrupt 	60
#define PORTC_Interrupt 	61
#define PORTD_Interrupt 	62
#define PORTE_Interrupt 	63
#define LPUART1_Interrupt 33

typedef struct {
	volatile unsigned int NVIC_ISER[8];				// Interrupt Set-enable Register.
	volatile unsigned int RESERVED_1[24];	
	volatile unsigned int NVIC_ICER[8];				// Interrupt Clear-enable Register.
	volatile unsigned int RESERVED_2[24];	
	volatile unsigned int NVIC_ISPR[8];				// Interrupt Set-pending Register.
	volatile unsigned int RESERVED_3[24];			
	volatile unsigned int NVIC_ICPR[8];				// Interrupt Clear-pending Register.
	volatile unsigned int RESERVED_4[24];			
	volatile unsigned int NVIC_IABR[8];				// Interrupt Active Bit Register.
	volatile unsigned int RESERVED_5[56];			
	volatile unsigned int NVIC_IPR[60];				// Interrupt Priority Register.
	unsigned int RESERVED_6[644];
	volatile unsigned int STIR;								// Software Trigger Interrupt Register.

}NVIC_TYPE;

#define NVIC 		((NVIC_TYPE*)(0xE000E100))

#endif
