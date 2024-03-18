#ifndef SPI_H
#define SPI_H

typedef struct {
  volatile unsigned int VERID;                             /**< Version ID Register, offset: 0x0 */
  volatile unsigned int PARAM;                             /**< Parameter Register, offset: 0x4 */
  volatile unsigned char RESERVED_0[8];
  volatile unsigned int CR;                                /**< Control Register, offset: 0x10 */
  volatile unsigned int SR;                                /**< Status Register, offset: 0x14 */
  volatile unsigned int IER;                               /**< Interrupt Enable Register, offset: 0x18 */
  volatile unsigned int DER;                               /**< DMA Enable Register, offset: 0x1C */
  volatile unsigned int CFGR0;                             /**< Configuration Register 0, offset: 0x20 */
  volatile unsigned int CFGR1;                             /**< Configuration Register 1, offset: 0x24 */
  volatile unsigned char RESERVED_1[8];
  volatile unsigned int DMR0;                              /**< Data Match Register 0, offset: 0x30 */
  volatile unsigned int DMR1;                              /**< Data Match Register 1, offset: 0x34 */
  volatile unsigned char RESERVED_2[8];
  volatile unsigned int CCR;                               /**< Clock Configuration Register, offset: 0x40 */
  volatile unsigned char RESERVED_3[20];
  volatile unsigned int FCR;                               /**< FIFO Control Register, offset: 0x58 */
  volatile unsigned int FSR;                               /**< FIFO Status Register, offset: 0x5C */
  volatile unsigned int TCR;                               /**< Transmit Command Register, offset: 0x60 */
  volatile unsigned int TDR;                               /**< Transmit Data Register, offset: 0x64 */
  volatile unsigned char RESERVED_4[8];
  volatile unsigned int RSR;                               /**< Receive Status Register, offset: 0x70 */
  volatile unsigned int RDR;                               /**< Receive Data Register, offset: 0x74 */
} LPSPI_Type;

/* LPSPI - Peripheral instance base addresses */
/** Peripheral LPSPI0 base address */
#define LPSPI0_BASE                              (0x4002C000u)
/** Peripheral LPSPI0 base pointer */
#define LPSPI0                                   ((LPSPI_Type *)LPSPI0_BASE)
/** Peripheral LPSPI1 base address */
#define LPSPI1_BASE                              (0x4002D000u)
/** Peripheral LPSPI1 base pointer */
#define LPSPI1                                   ((LPSPI_Type *)LPSPI1_BASE)
/** Peripheral LPSPI2 base address */
#define LPSPI2_BASE                              (0x4002E000u)
/** Peripheral LPSPI2 base pointer */
#define LPSPI2                                   ((LPSPI_Type *)LPSPI2_BASE)

void setCCR(LPSPI_Type *reg, volatile unsigned int SCKPCS, volatile unsigned int PCSSCK, volatile unsigned int DBT, volatile unsigned int SCKDIV);
void setTCR(LPSPI_Type *reg, volatile unsigned int CPOL, volatile unsigned int CPHA, volatile unsigned int PRESCALE, volatile unsigned int PCS, volatile unsigned int LSBF, volatile unsigned int FRAMESZ);
void setFCR(LPSPI_Type *reg, volatile unsigned int RXWATER, volatile unsigned int TXWATER);
void setCFGR1(LPSPI_Type *reg, volatile unsigned int NOSTALL, volatile unsigned int MASTER);
#endif
