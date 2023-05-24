//Where is the led connected?
//Port: A
//Pin:  5

#define  PERIPH_BASE       (0x40000000UL)
#define  AHB1PERIPH_OFFSET (0x00020000UL)
#define  AHB1PERIPH_BASE   (PERIPH_BASE+AHB1PERIPH_OFFSET)
#define  GPIOA_OFFSET      (0x0000UL) //number of 0's doesn't matter

#define  GPIOA_BASE        (AHB1PERIPH_BASE+GPIOA_OFFSET)

#define  RCC_OFFSET        (0x3830UL)
#define  RCC_BASE          (AHB1PERIPH_BASE+RCC_OFFSET)

#define  AHB1EN_R_OFFSET   (0x30UL)
#define  RCC_AHB1ENR       (*(volatile unsigned int *)(0x40023830UL)) //It's an address so we need to use pointers

#define  MODE_R_OFFSET     (0x0UL)
#define  GPIOA_MODE_R      (*(volatile unsigned int *)(0x40020000UL))

#define  OD_R_OFFSET       (0x14UL)
#define  GPIOA_OD_R        (*(volatile unsigned int *)(0x40020014UL))

#define  GPIOAEN           (1U<<0)

#define  PIN5              (0x1U<<5)
#define  LED_PIN           (PIN5)

#include <stdint.h>

/*#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/
int main(void)
{
    /* 1. Enable clock access to GPIO A */
	RCC_AHB1ENR |= GPIOAEN;
	/* 2. Set PA5 as output pin */
	GPIOA_MODE_R |= (1U<<10); //same as (0x1UL<<10)
	GPIOA_MODE_R &= ~(1U<<11); //clear bit 11

	while(1){
		GPIOA_OD_R ^= LED_PIN;
	}

}
