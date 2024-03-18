#ifndef UART_H
#define UART_H
#include "main.h"

typedef struct {
  volatile unsigned int VERID;                    /**< Version ID Register */
  volatile unsigned int PARAM;                    /**< Parameter Register */
  volatile unsigned int GLOBAL;                   /**< LPUART Global Register */
  volatile unsigned int PINCFG;                   /**< LPUART Pin Configuration Register */
  volatile unsigned int BAUD;                     /**< LPUART Baud Rate Register */
  volatile unsigned int STAT;                     /**< LPUART Status Register */
  volatile unsigned int CTRL;                     /**< LPUART Control Register */
  volatile unsigned int DATA;                     /**< LPUART Data Register */
  volatile unsigned int MATCH;                    /**< LPUART Match Address Register */
  volatile unsigned int MODIR;                    /**< LPUART Modem IrDA Register */
  volatile unsigned int FIFO;                     /**< LPUART FIFO Register */
  volatile unsigned int WATER;                    /**< LPUART Watermark Register */
} LPUART_Type;

/* Peripheral LPUART0 base address */
#define LPUART0_BASE                             (0x4006A000u)
/* Peripheral LPUART0 base pointer */
#define LPUART0                                  ((LPUART_Type *)LPUART0_BASE)
/* Peripheral LPUART1 base address */
#define LPUART1_BASE                             (0x4006B000u)
/* Peripheral LPUART1 base pointer */
#define LPUART1                                  ((LPUART_Type *)LPUART1_BASE)
/* Peripheral LPUART2 base address */
#define LPUART2_BASE                             (0x4006C000u)
/* Peripheral LPUART2 base pointer */
#define LPUART2                                  ((LPUART_Type *)LPUART2_BASE)

void setCTRL(volatile unsigned int *reg, volatile unsigned int TIE, volatile unsigned int RIE, volatile unsigned int ILIE, volatile unsigned int TE, volatile unsigned int RE, volatile unsigned int Mode, volatile unsigned int PE, volatile unsigned int PT);
void setBAUD(volatile unsigned int *reg, volatile unsigned int OSR, volatile unsigned int SBNS, volatile unsigned int SBR);
#endif
