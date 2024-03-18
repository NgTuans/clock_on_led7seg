#include "main.h"

	int main(){

	setClock_72MHz();
	
	//	************ SET LPUART1  Pin C6, C7 	 Baud rate: 38400, 8-bits data, even parity, 1-bit stop ***************
	PCC->PCC_PORTC |= (0x1 << 30);					// Enable CGC PortC
	PCC->PCC_LPUART1 |= (0x6u << 24);				// PCS (Peripheral Clock Source Select)		Clock display 6
	PCC->PCC_LPUART1 |= (0x1u << 30);				// Enable CGC LPUART1
	
	PORTC_PCR->PORT_PCR6 |= (0x2 << 8);			// MUX Alternative 2
	PORTC_PCR->PORT_PCR7 |= (0x2 << 8);
	NVIC->NVIC_ISER[LPUART1_Interrupt/32] |= (0x1u << LPUART1_Interrupt%32);
	
	// Set BAUD
	setBAUD(&(LPUART1->BAUD), 0xEu, 0x0u, 0x3Eu); 
	// OSR (Oversampling ratio) 01110 (Oversampling ratio of 15)
	// SBNS (Stop bit number select) = 0 (One stop bit)
	// Set SBR (62)	Baud rate 38400
	
	// Set CTRL
	setCTRL(&(LPUART1->CTRL), 0x0u, 0x1u, 0x1u, 0x1u, 0x1u, 0x1u, 0x1u, 0x0u);
	// Transmit Interrupt Disable
	// Receiver Interrupt Enable
	// Idle Line Interrupt Enable
	// Transmitter enabled
	// Receiver enabled
	// Receiver and transmitter use 9-bit data characters.
	// Parity enable
	// Even parity
	
	
	//  ****************** SET LPSPI0 using Pin E0, E1, E2, E6 **********************
	PCC->PCC_PORTE |= (0x1u << 30);					// Enable CGC PortE
	PCC->PCC_LPSPI0 |= (0x6u << 24);				// PCS (Peripheral Clock Source Select)		Clock display 6
	PCC->PCC_LPSPI0 |= (0x1u << 30);				// Enable CGC	LPSPI0
	
	// MUX 	Alternative 2
	PORTE_PCR->PORT_PCR6 |= (0x2u << 8);			//LPSPI0_PCS2		
	PORTE_PCR->PORT_PCR2 |= (0x2u << 8);			//LPSPI0_SOUT
	PORTE_PCR->PORT_PCR1 |= (0x2u << 8);			//LPSPI0_SIN
	PORTE_PCR->PORT_PCR0 |= (0x2u << 8);			//LPSPI0_SCK

	setCCR(LPSPI0, 0x2u, 0x2u, 0x1u, 0x1u);		// Clock configuration register.
	// Set SCKPCS = 2			// SCKPCS		  = 36/(4*(2+1))  = 3
	// Set PCSSCK = 2			// PCSSCK     = 36/(4*(2+1))  = 3
	// Set DBT = 1				// DBT	  	 	= 36/(4*(1+2)) 	= 3
	// Set SCKDIV = 1			// SCK Clock 	= 36/(4*(1+2))  = 3	
	
	// Configures clock phase and polarity
	setTCR(LPSPI0, 0x0u, 0x0u, 0x2u, 0x2u, 0x0u, 0xFu);			// Transmit command register.
	// CPOL = 0		 CPHA = 0
	// PRESCALE Prescaler Value		Divide by 4
	// PCS (Peripheral Chip Select) = 2
	// LSBF = 0	(Data is transferred MSB first)
	// FRAMESZ 16 bit
	
	// Set receive FIFO
	setFCR(LPSPI0, 0x0u, 0x0u);				// FIFO control register
	// Receive FIFO Watermark = 0
	// Transmit FIFO Watermark = 0
	
	// Set CFGR1
	setCFGR1(LPSPI0, 0x1u, 0x1u);			// Configuration register 1
	// Set FIFO underrun CFGR1(NOSTALL)
	// Master mode

	LPSPI0->CR |= (0x1u);	// Control register // Enable LPSPI0 module
	
	setPIN(GREEN_LED);
	setLED7SEG(LPSPI0);		
	setSW(0x9u);					// SW2 SW3							//	1001 ISF flag and Interrupt on rising-edge.
	setSYSTICK((CORE_CLOCK/10), 0x1u, 0x1u);	// Reload value (7200000) 	CLKSOURCE (processor clock)		TICKINT enable
	
	while(1){	

		if(compare() || alarmFlag == 1){						// Compare time and alarm.
			alarmFlag = 1;		
			blinkLed();
		}

		if(received == 1){
			if(checkFormat(data, i) >= 1){						// Check format true -> display wrong format
				displayError();													
			}
			else{																			// If true
				if(dateOrClock == 1){
					getTime(date);												// Set date
				}
				else{
					if(display != 4){
						getTime(clock);											// Set time
					}
					else{
						getTime(alarm);											// Set alarm
					}
				}
			}	
			i = 0;
			dateOrClock = 0;
			received = 0;
			time1 = 0;																// Renew variable
			time2 = 0;
			time3 = 0;
		}
	}
}

void LPUART1_RxTx_IRQHandler(void){ 
	if(LPUART1->STAT & (1u << RDRF)){						 // Receive data buffer full
		data[i] = (char)LPUART1->DATA;
		if(data[i] == ' '){												 // Ignore space
			i--;
		}
		i++;
	}
	if(LPUART1->STAT & (1u << IDLE)){						 // End of receiving
		received = 1;
		LPUART1->STAT |= (1u << IDLE);						 // W1C
	}
}

void PORTC_IRQHandler(void){
	if(PORTC_PCR->PORT_PCR12 & (1u << ISF)){		 // Interrupt Status Flag. 1 - Configured interrupt is detected.
		PORTC_PCR->PORT_PCR12 |= (1u << ISF);			 // W1C
		if(alarmFlag == 1){
			GPIOD->PDOR |= (1u << GREEN_LED);			   // Turn green led off when alarm.
			timeLedBlink = 0;
			alarmFlag = 0;
		}
		else{
			display++;
			if(display > 4){													// Switch display.
				display = 1;
			}
		}
	}
	if(PORTC_PCR->PORT_PCR13 & (1u << ISF)){			// Interrupt Status Flag. 1 - Configured interrupt is detected.
		PORTC_PCR->PORT_PCR13 |= (1u << ISF);				// W1C
		if(alarmFlag == 1){
			GPIOD->PDOR |= (1u << GREEN_LED);					// Turn green led off when alarm.
			timeLedBlink = 0;
			alarmFlag = 0;
		}
		else{
			if(LEDIntensity == 0){
				temp1 = display;												// Display 5 Led7seg off.
				display = 5;
			}
			else if(LEDIntensity == 1){
				display = temp1;
				temp1 = 0;
			}
			setINTENSITY(LPSPI0, LEDIntensity);				// Decrease bright of LED 7 SEG.
			LEDIntensity++;
			if(LEDIntensity == 5){
				LEDIntensity = 0;
			}
		}
	}
}

int checkLeapYear(volatile unsigned int year){	
	if((year % 400) == 0){												// Divisible by 400.
		return 1;
	}
	if((year % 4 == 0) && (year % 100 != 0)){			// Devisible by 4 and not devisible by 100.
		return 1;
	}
	return 0;
}

void SysTick_Handler(void){
	count++;
	if(count > 9){
		clock[2]++;
		count = 0;
	}
	if(alarmFlag == 1){
		count2++;
		if(count2 > 9){							// Green led blink 10s.
			timeLedBlink++;
			count2 = 0;
		}
		if(timeLedBlink > 11){
			timeLedBlink = 0;
		}
	}
	if(clock[2] > 59){
		clock[2] = 0;
		clock[1]++;
	}
	if(clock[1] > 59){
		clock[1] = 0;
		clock[0]++;
	}
	if(clock[0] > 23){
		clock[0] = 0;
		date[0]++;
	}
	if(date[1] == 2){											
		if(checkLeapYear(date[2])){				// Leap year, Feb has 29 days.
			if(date[0] > 29){
				date[0] = 1;
				date[1]++;
			}
		}
		else{
			if(date[0] > 28){
				date[0] = 1;
				date[1]++;
			}
		}
	}
	if((date[1] == 4) || (date[1] == 6) || (date[1] == 9) || (date[1] == 11)){			// Apr, June, Sep, Nov have 30 days.
		daysOfMonth = 30;
	}
	if((date[1] == 1) || (date[1] == 3) || (date[1] == 5) || (date[1] == 7) || (date[1] == 8) || (date[1] == 10) || (date[1] == 12)){
		daysOfMonth = 31;																															// Jan, Mar, May, July, Aug, Oct, Dec have 31 days.
	}
	if((date[0] > 30) && (daysOfMonth == 30)){
		date[0] = 1;
		date[1]++;
	}
	if((date[0] > 31 && (daysOfMonth == 31))){
		date[0] = 1;
		date[1]++;
	}
	if(date[1] > 12){
		date[1] = 1;
		date[2]++;
	}
	if(display == 1){
		count1++;
		if(count1 > 9){																					// Auto date 3s, time 5s
			temp2++;
			count1 = 0;
		}
		if(temp2 > 8){
			temp2 = 0;
		}
	}
	displayTime();
}

void getTime(volatile unsigned  int* arr){
	for(volatile unsigned int k = 0; k < i; k++){		
		if((data[k] == '.') || (data[k] == '-')){								// Take number when (.) or (-) appear.
			if(countSign == 0){
				time1 = time3;
				time3 = 0;
				countSign++;
			}
			else if(countSign == 1){
				time2 = time3;
				time3 = 0;
				countSign++;
			}
		}
		if((data[k] <= '9') && (data[k] >= '0')){
			time3 = (time3 * 10) + (data[k] - 48);
		}
		data[k] = 0;
	}
	countSign = 0;
	arr[0] = time1;
	arr[1] = time2;									// Assign time.
	arr[2] = time3;
}

int checkFormat(volatile unsigned char *DATA, volatile unsigned int sum){		// Check Format.
	volatile int check = 0;
	for(volatile unsigned int k = 0; k < sum; k++){
		if((DATA[k] > '9') || (DATA[k] < '0')){								// Do not take letters.
			check++;
			if((DATA[k] == '.') || (DATA[k] == '-')){
				check--;
			}
		}
		if(DATA[k] == '-'){										//  (-) time.
			dateOrClock = 2;										// dateOrClock != 1 clock.
		}
		if(DATA[k] == '.'){										//  (.) date.
			dateOrClock = 1;										// dateOrClock = 1 date.
		}
	}
	return check;
}

void displayError(void){
	for(volatile int y = 0; y < 12; y++){
		while(!(LPUART1->STAT &(1u << TDRE)));					// Wait until TDRE = 1				
		LPUART1->DATA = er[y];													// Display wrong format
	}
}

int compare(void){																	// Compare time and alarm.
	for(volatile unsigned int k = 0; k < 3; k++){
		if(clock[k] != alarm[k]){									
			return 0;
		}
	}
	return 1;
}

void blinkLed(void){
	if(count2 < 5){
		GPIOD->PDOR &= ~(1u << GREEN_LED);
	}
	else{
		GPIOD->PDOR |= (1u << GREEN_LED);				 // The LED Green blink with period 0.5 (s) in alarm time 10 (s).
	}
	if(timeLedBlink > 10){
		GPIOD->PDOR |= (1u << GREEN_LED);
		timeLedBlink = 0;
		alarmFlag = 0;
	}
}

void displayTime(void){
	switch(display){
		case 0:
			setLEDhour(LPSPI0, clock[0], clock[1], clock[2]);						// After power on, display the time: 18-00-00(date: 01.01.1991).
			break;
		case 1:																												// Press button 1.
			if(temp2 <= 5){
				setLEDhour(LPSPI0, clock[0], clock[1], clock[2]);					// Auto display mode: Repeat display the time (5s).
			}
			else if(temp2 > 5){
				setLEDday(LPSPI0, date[0], date[1], date[2]);							// -> Display the date (3s).
			}
			break;
		case 2:
			setLEDday(LPSPI0, date[0], date[1], date[2]);								// Display the date.
			break;
		case 3:
			setLEDhour(LPSPI0, clock[0], clock[1], clock[2]);						// Display the time.
			break;
		case 4:
			setLEDhour(LPSPI0, alarm[0], alarm[1], alarm[2]);						// Display the alarm.
			break;
		case 5:
			ledOff(LPSPI0);																							// LED7SEG OFF.
			break;
		default:
			break;
	}
}

void setSW(volatile unsigned int IRQC){
	PCC->PCC_PORTC |= (1u << 30);								// CGC
	PORTC_PCR->PORT_PCR12 |= (1u << 8);					// MUX   GPIO
	PORTC_PCR->PORT_PCR13 |= (1u << 8);
	PORTC_PCR->PORT_PCR12 |= (IRQC << 16);			// IRQC
	PORTC_PCR->PORT_PCR13 |= (IRQC << 16);
//	1000 ISF flag and Interrupt when logic 0.
//	1001 ISF flag and Interrupt on rising-edge.
//	1010 ISF flag and Interrupt on falling-edge.
//	1011 ISF flag and Interrupt on either edge.
//	1100 ISF flag and Interrupt when logic 1.
	NVIC->NVIC_ISER[PORTC_Interrupt/32] |= (1u << (PORTC_Interrupt%32));
}

void setPIN(volatile unsigned int LED){
	PCC->PCC_PORTD |= (0x1u << 30);										// CGC
	if(LED == 0){
		PORTD_PCR->PORT_PCR0 |= (0x1u << 8);
	}
	if(LED == 15){
		PORTD_PCR->PORT_PCR15 |= (0x1u << 8);						// MUX 001 (GPIO)
	}
	if(LED == 16){
		PORTD_PCR->PORT_PCR16 |= (0x1u << 8);
		
	}
	GPIOD->PDDR |= (0x1u << LED);
	GPIOD->PDOR |= (0x1u << LED);
}

void setClock_72MHz(void){
	disable_SCR(&(SCG->SCG_SOSCCSR));
	setSOSCCFG(0x3u, 0x1u, 0x1u);
	// RANGE 11 High frequency range selected for the crystal oscillator
	// HGO  High gain oscillator select
	// EREFS	Internal crystal oscillator of OSC selected
	enable_SCR(&(SCG->SCG_SOSCCSR));
	while(!(SCG->SCG_SOSCCSR & (1u << 24)));		// Wait until SOSCVLD == 1
	disable_SCR(&(SCG->SCG_SPLLCSR));
	setSPLLCFG(0x2u, 0x0u, 0x0u);	
	// MULT = 18			// PREDIV = 0 		// SOURE SOSC
	// 8 * 18 / 2 = 72MHz
	setDIV(&(SCG->SCG_SPLLDIV), 0x2u, 0x0u);				// DIV2 2 (36MHz)	 DIV1 dis	
	enable_SCR(&(SCG->SCG_SPLLCSR));
	set_RCCR(&(SCG->SCG_SPLLCSR), 0x6u, 0x0u, 0x1u, 0x3u);
	// SCS SPLL		// DIVCORE 1		// DIVBUS 2 (36MHz)		// DIVSLOW 4
}
