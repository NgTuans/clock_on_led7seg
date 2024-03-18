#include "led7seg.h"

void setLED7SEG(LPSPI_Type *reg){
	while(!(reg->SR & (1u)));		// Wait Transmit Data Flag = 1 - Transmit data is requested
	reg->TDR = 0xC11;										// Normal Operation			
	while(!(reg->SR & (1u)));
	reg->TDR = 0xB17;										// Scan Limit 
	while(!(reg->SR & (1u)));
	reg->TDR = 0x9FF;										// DeCode Mode
	while(!(reg->SR & (1u)));
	reg->TDR = 0xA1F;										// INTENSITY
	while(!(reg->SR & (1u)));
	reg->TDR = 0xF00;										// Display Mode
}

void setLEDs(LPSPI_Type *reg, volatile unsigned int STT, volatile unsigned int DOT, volatile unsigned int NUM){
	while(!(reg->SR & (1u)));			// Wait Transmit Data Flag = 1 - Transmit data is requested
	reg->TDR = (STT << 8) + (DOT << 4) + (NUM);
	// STT 1 -> 8
	// DOT = 8 (dots)  DOT = 0 (disable)
	// NUM 1->9 (number)		A (-)  F (off)
}

void setLEDhour(LPSPI_Type *reg, volatile unsigned int HOUR, volatile unsigned int MINUTE, volatile unsigned int SECOND){
	setLEDs(reg, 6, 0, 10);						// 3rd and 6th is (-).
	setLEDs(reg, 3, 0, 10);
	if(HOUR > 9){
		setLEDs(reg, 8, 0, (HOUR / 10));
		setLEDs(reg, 7, 0, (HOUR % 10));
	}
	else{
		setLEDs(reg, 8, 0, 0);
		setLEDs(reg, 7, 0, HOUR);
	}
	if(MINUTE > 9){
		setLEDs(reg, 5, 0, (MINUTE / 10));
		setLEDs(reg, 4, 0, (MINUTE % 10));
	}
	else {
		setLEDs(reg, 5, 0, 0);
		setLEDs(reg, 4, 0, MINUTE );
	}
	if(SECOND > 9){
		setLEDs(reg, 2, 0, (SECOND / 10));
		setLEDs(reg, 1, 0, (SECOND % 10));
	}
	else {
		setLEDs(reg, 2, 0, 0);
		setLEDs(reg, 1, 0, SECOND);
	}
}

void setLEDday(LPSPI_Type *reg, volatile unsigned int DAY, volatile unsigned int MONTH, volatile unsigned int YEAR){
	if(DAY > 9){
		setLEDs(reg, 8, 0, (DAY / 10));
		setLEDs(reg, 7, 8, (DAY % 10));
	}
	else {
		setLEDs(reg, 8, 0, 0);
		setLEDs(reg, 7, 8, DAY);
	}
	if(MONTH > 9){
		setLEDs(reg, 6, 0, (MONTH / 10));
		setLEDs(reg, 5, 8, (MONTH % 10));
	}
	else {
		setLEDs(reg, 6, 0, 0);
		setLEDs(reg, 5, 8, MONTH);
	}
	setLEDs(reg, 4, 0, (YEAR / 1000));
	setLEDs(reg, 3, 0, (YEAR / 100) % 10);
	setLEDs(reg, 2, 0, (YEAR / 10) % 10);
	setLEDs(reg, 1, 0, (YEAR % 10));
}

void setINTENSITY(LPSPI_Type *reg, volatile unsigned int INT){
	
	// INTENSITY 1 -> 5 (min -> max)
	if(INT == 1){
		setLEDs(reg, 0xAu, 0x0u, 0x1u);
	}
	else if(INT == 2){
		setLEDs(reg, 0xAu, 0x0u, 0x4u);
	}
	else if(INT == 3){
		setLEDs(reg, 0xAu, 0x0u, 0x8u);
	}
	else if(INT == 4){
		setLEDs(reg, 0xAu, 0x0u, 0xDu);
	}
}

void ledOff(LPSPI_Type *reg){
	setLEDs(reg, 8, 0, 0xF);
	setLEDs(reg, 7, 0, 0xF);
	setLEDs(reg, 6, 0, 0xF);
	setLEDs(reg, 5, 0, 0xF);
	setLEDs(reg, 4, 0, 0xF);
	setLEDs(reg, 3, 0, 0xF);
	setLEDs(reg, 2, 0, 0xF);
	setLEDs(reg, 1, 0, 0xF);
}
