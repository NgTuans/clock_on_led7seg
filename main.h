#ifndef MAIN_H
#define MAIN_H

#include "port.h"
#include "gpio.h"
#include "pcc.h"
#include "nvic.h"
#include "scg.h"
#include "uart.h"
#include "spi.h"
#include "systick.h"
#include "led7seg.h"

#define BLUE_LED 				 0
#define RED_LED 			 	 15
#define GREEN_LED 			 16
#define ISF              24			// Interrupt status flag
#define TDRE						 23			// Transmit Data Register Empty Flag
#define RDRF             21			// Receive Data Register Full Flag
#define IDLE             20			// Idle line flag
#define CORE_CLOCK			 72000000

volatile static unsigned int temp = 0;
volatile static unsigned int temp1 = 0;
volatile static unsigned int temp2 = 0;
volatile static unsigned int daysOfMonth = 0;
volatile static unsigned int dateOrClock = 0;
volatile static unsigned int timeLedBlink = 1;
volatile static unsigned int LEDIntensity = 0;
volatile static unsigned int received = 0;
volatile static unsigned int countSign = 0;
volatile static unsigned int alarmFlag = 0;
volatile static unsigned int count = 0;
volatile static unsigned int count1 = 0;
volatile static unsigned int count2 = 0;
volatile static unsigned int i = 0;
volatile static unsigned int display = 0;
volatile static unsigned int clock[3] = {18, 0, 0};
volatile static unsigned int date[3] = {1, 1, 1991};
volatile static unsigned int alarm[3] = {0};
volatile static unsigned char data[15] = {0};
volatile static unsigned char er[12] = "wrong format";
volatile static unsigned int time1 = 0;
volatile static unsigned int time2 = 0;
volatile static unsigned int time3 = 0;
void setClock_72MHz(void);
void SysTick_Handler(void);
void setSW(volatile unsigned int IRQC);									// Set SW2, SW3
void setPIN(volatile unsigned int LED);									// Set LED
void getTime(volatile unsigned  int* arr);							// 
int checkFormat(volatile unsigned char *data, volatile unsigned int sum);
void displayError(void);
void displayTime(void);
int checkLeapYear(volatile unsigned int year);
int compare(void);
void blinkLed(void);
void LPUART1_RxTx_IRQHandler(void);
void PORTC_IRQHandler(void);
void SysTick_Handler(void);

#endif
