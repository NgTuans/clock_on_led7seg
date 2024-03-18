#include "spi.h"

void setLED7SEG(LPSPI_Type *reg);
void setLEDs(LPSPI_Type *reg, volatile unsigned int STT, volatile unsigned int DOT, volatile unsigned int NUM);
void setLEDhour(LPSPI_Type *reg, volatile unsigned int HOUR, volatile unsigned int MINUTE, volatile unsigned int SECOND);
void setLEDday(LPSPI_Type *reg, volatile unsigned int DAY, volatile unsigned int MONTH, volatile unsigned int YEAR);
void setINTENSITY(LPSPI_Type *reg, volatile unsigned int INT);
void ledOff(LPSPI_Type *reg);
