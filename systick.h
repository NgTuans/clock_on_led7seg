#ifndef SYSTICK_H
#define SYSTICK_H

typedef struct {
	volatile unsigned int SYST_CSR;		// SysTick Control and Status Register
	volatile unsigned int SYST_RVR;		// SysTick Reload Value Register
	volatile unsigned int SYST_CVR;		// SysTick Current Value Register
	volatile unsigned int SYST_CALIB;	// SysTick Calibration Value Register
}SYS_TYPE;

#define SYS_BASE 		(0xE000E010u)
#define SYSTICK		((SYS_TYPE*)SYS_BASE)

void setSYSTICK(volatile unsigned int RELOADVALUE, volatile unsigned int CLKSOURCE, volatile unsigned int TICKINT);

#endif
