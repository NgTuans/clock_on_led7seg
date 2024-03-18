#ifndef GPIO_H
#define GPIO_H

typedef struct
{
	volatile unsigned int PDOR;
	volatile unsigned int PSOR;
	volatile unsigned int PCOR;
	volatile unsigned int PTOR;
	volatile unsigned int PDIR;
	volatile unsigned int PDDR;
	volatile unsigned int PIDR;
} GPIO_TYPE;
#define GPIOA_BASE_ADDRESS (0x400FF000u)
#define GPIOA ((GPIO_TYPE*)GPIOA_BASE_ADDRESS)

#define GPIOB_BASE_ADDRESS (0x400FF040u)
#define GPIOB ((GPIO_TYPE*)GPIOB_BASE_ADDRESS)

#define GPIOC_BASE_ADDRESS (0x400FF080u)
#define GPIOC ((GPIO_TYPE*)GPIOC_BASE_ADDRESS)

#define GPIOD_BASE_ADDRESS (0x400FF0C0u)
#define GPIOD ((GPIO_TYPE*)GPIOD_BASE_ADDRESS)

#define GPIOE_BASE_ADDRESS (0x400FF100u)
#define GPIOE ((GPIO_TYPE*)GPIOE_BASE_ADDRESS)

#endif
