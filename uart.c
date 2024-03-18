#include "uart.h"

void setCTRL(volatile unsigned int *reg, volatile unsigned int TIE, volatile unsigned int RIE, volatile unsigned int ILIE, volatile unsigned int TE, volatile unsigned int RE, volatile unsigned int Mode, volatile unsigned int PE, volatile unsigned int PT){
	temp = 0;
	temp = *reg;
	temp |= (TIE << 23);				// Transmit Interrupt 1 Enable 0 Disable
	temp |= (RIE << 21);				// Receiver Interrupt 1 Enable 0 Disable
	temp |= (ILIE << 20);				// Idle Line Interrupt 1 Enable 0 Disable
	temp |= (TE << 19);					// Transmitter enabled.
	temp |= (RE << 18);					// Receiver enabled
	temp |= (Mode << 4);				// Receiver and transmitter use (1) 9-bit data characters (0) 8-bit data characters.
	temp |= (PE << 1);					// 1 Parity enable 0 Disable
	temp |= (PT);								// 1 Odd parity 0 Even parity
	*reg = temp;
}

void setBAUD(volatile unsigned int *reg, volatile unsigned int OSR, volatile unsigned int SBNS, volatile unsigned int SBR){
	temp = 0;
	temp = *reg;				
	temp &= ~(0xFu << 24);
	temp |= (OSR << 24);				// OSR (Oversampling ratio) 8 - 32
	temp |= (SBNS << 13);				// SBNS (Stop bit number select)
	temp &= ~(1u << 2);
	temp |= (SBR);						
	*reg = temp;
	// SBR = fLPUART / baud rate * oversampling ratio
}
