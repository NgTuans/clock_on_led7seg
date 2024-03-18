#include "scg.h"

void disable_SCR(volatile unsigned int* reg){
	while((*reg & (1u << 23)));				// Wait until LK(Lock Register) = 0 | Can be written
	temp = 0;
	temp = *reg;
	temp &= ~(1u);
	*reg = temp;
}

void enable_SCR(volatile unsigned int* reg){
	while((*reg & (1u << 23)));				// Wait until LK(Lock Register) = 0 | Can be written
	temp = 0;
	temp = *reg;
	temp |= (1u);
	*reg = temp;
}
void set_RCCR(volatile unsigned int *csr, volatile unsigned int SCS, volatile unsigned int DIVCORE, volatile unsigned int DIVBUS, volatile unsigned int DIVSLOW){
	while(!(*csr & (1u << 24)));				// Wait until output clock is valid = 1.
	temp = 0;
	temp = SCG->SCG_RCCR;
	temp &= ~(0xFu << 24);
	temp |= (SCS << 24);
	temp |= (DIVCORE << 16);
	temp |= (DIVBUS << 4);
	temp |= (DIVSLOW << 0);
	SCG->SCG_RCCR = temp;
	while((SCG->SCG_CSR) != (SCG->SCG_RCCR));
}

void setDIV(volatile unsigned int *reg, volatile unsigned int DIV2, volatile unsigned int DIV1){
	temp = 0;
	temp = *reg;
	temp |= (DIV2 << 8);
	temp |= (DIV1);	
	*reg = temp;
}

void setSOSCCFG(volatile unsigned int RANGE, volatile unsigned int HGO, volatile unsigned int EREFS){
	temp = 0;
	temp = SCG->SCG_SOSCCFG;
	temp &= ~(1u << 4);
	temp |= (RANGE << 4);
	temp |= (HGO << 3);
	temp |= (EREFS << 2);
	SCG->SCG_SOSCCFG = temp;
}

void setSIRCCFG(volatile unsigned int RANGE){
	temp = 0;
	temp = SCG->SCG_SIRCCFG;
	temp |= (RANGE);
	SCG->SCG_SIRCCFG = temp;
}

void setSPLLCFG(volatile unsigned int MULT, volatile unsigned int PREDIV, volatile unsigned int SOURCE){
	temp = 0;
	temp = SCG->SCG_SPLLCFG;
	temp |= (MULT << 16);
	temp |= (PREDIV << 8);
	temp |= (SOURCE);
	SCG->SCG_SPLLCFG = temp;
}
