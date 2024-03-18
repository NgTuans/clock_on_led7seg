#include "spi.h"
#include "main.h"

void setCCR(LPSPI_Type *reg, volatile unsigned int SCKPCS, volatile unsigned int PCSSCK, volatile unsigned int DBT, volatile unsigned int SCKDIV){
	temp = 0;
	temp = reg->CCR;
	// SCK to PCS delay
	temp |= (SCKPCS << 24);													// SCKPCS 	 = Functional Clock  / (Prescale * (SCKPCS + 1)
	// PCS to SCK delay
	temp |= (PCSSCK << 16);													// PCSSCK		 = Functional Clock  / (Prescale * (PCSSCK + 1)
	// Delay between transfers 
	temp |= (DBT << 8);														  // DBT	     = Functional Clock  / (Prescale * (DBT + 2))
	// SCK Divider
	temp |= (SCKDIV);																// SCK Clock = Functional Clock  / (Prescale * (SCKDIV + 1))
	reg->CCR = temp;								
}

void setTCR(LPSPI_Type *reg, volatile unsigned int CPOL, volatile unsigned int CPHA, volatile unsigned int PRESCALE, volatile unsigned int PCS, volatile unsigned int LSBF, volatile unsigned int FRAMESZ){
	temp = 0;
	temp = reg->TCR;
	temp |= (CPOL << 31);									// The inactive state value of SCK is low (0), high (1).
	temp |= (CPHA << 30);									// Data is captured on the leading edge of SCK and changed on the following edge of SCK (0).
																				// Data is changed on the leading edge of SCK and captured on the following edge of SCK (1).
	temp |= (PRESCALE << 27);							// PRESCALE 
	temp |= (PCS << 24);									// PCS (Peripheral Chip Select).
	temp |= (LSBF << 23);									// LSBF = 0	(Data is transferred MSB first) - LSBF = 1 (Data is transferred LSB first).
	temp = ((temp & ~(0xFFFu)) | (FRAMESZ));
	reg->TCR = temp;
}

void setFCR(LPSPI_Type *reg, volatile unsigned int RXWATER, volatile unsigned int TXWATER){
	temp = 0;
	temp = reg->FCR;
	temp |= (RXWATER << 16);									
	temp |= (TXWATER);												
	reg->FCR = temp;
}

void setCFGR1(LPSPI_Type *reg, volatile unsigned int NOSTALL, volatile unsigned int MASTER){
	temp = 0;
	temp = reg->CFGR1;
	temp |= (NOSTALL << 3);											
	temp |= (MASTER);													
	reg->CFGR1 = temp;
}
