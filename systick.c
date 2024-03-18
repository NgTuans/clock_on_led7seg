#include "systick.h"
#include "main.h"

void setSYSTICK(volatile unsigned int RELOADVALUE, volatile unsigned int CLKSOURCE, volatile unsigned int TICKINT){
	SYSTICK->SYST_CSR &= ~(1u);							// DISABLE SYSTICK
	SYSTICK->SYST_CSR |= TICKINT << 1; 			// INTERRUPT SYS 	1 enable , 0 disable
	SYSTICK->SYST_CSR	|= CLKSOURCE << 2;		// CLKSOURCE			1 processor clock, 0 external clock
	SYSTICK->SYST_RVR = RELOADVALUE - 1u;		// RELOAD VALUE
	SYSTICK->SYST_CVR = 0;									// CURRENT VALUE	reset current value
	SYSTICK->SYST_CSR |= (1u);							// SYSTICK
}
