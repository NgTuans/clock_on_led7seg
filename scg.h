#ifndef SCG_H
#define SCG_H
#include "main.h"

typedef struct {
	volatile unsigned int SCG_VERID;
	volatile unsigned int SCG_PARAM;
	volatile unsigned int RESERVED_1[2];
	volatile unsigned int SCG_CSR;
	volatile unsigned int SCG_RCCR;
	volatile unsigned int SCG_VCCR;
	volatile unsigned int SCG_HCCR;
	volatile unsigned int SCG_CLKOUTCNFG;
	volatile unsigned int RESERVED_2[55];
	volatile unsigned int SCG_SOSCCSR;
	volatile unsigned int SCG_SOSCDIV;
	volatile unsigned int SCG_SOSCCFG;
	volatile unsigned int RESERVED_3[61];
	volatile unsigned int SCG_SIRCCSR;
	volatile unsigned int SCG_SIRCDIV;
	volatile unsigned int SCG_SIRCCFG;
	volatile unsigned int RESERVED_4[61];
	volatile unsigned int SCG_FIRCCSR;
	volatile unsigned int SCG_FIRCDIV;
	volatile unsigned int SCG_FIRCCFG;
	volatile unsigned int RESERVED_5[189];
	volatile unsigned int SCG_SPLLCSR;
	volatile unsigned int SCG_SPLLDIV;
	volatile unsigned int SCG_SPLLCFG;
}SCG_TYPE;

void disable_SCR(volatile unsigned int* reg);
void enable_SCR(volatile unsigned int* reg);
void set_RCCR(volatile unsigned int *csr, volatile unsigned int SCS, volatile unsigned int DIVCORE, volatile unsigned int DIVBUS, volatile unsigned int DIVSLOW);
void setDIV(volatile unsigned int *reg, volatile unsigned int DIV2, volatile unsigned int DIV1);
void setSOSCCFG(volatile unsigned int RANGE, volatile unsigned int HGO, volatile unsigned int EREFS);
void setSIRCCFG(volatile unsigned int RANGE);
void setSPLLCFG(volatile unsigned int MULT, volatile unsigned int PREDIV, volatile unsigned int SOURCE);
#define SCG_BaseAddress 		(0x40064000u)
#define SCG 								((SCG_TYPE*)SCG_BaseAddress)
#endif 
