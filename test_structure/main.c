#include <stdint.h>

#define  PERIPH_BASE       (0x40000000UL) //UL : unsigned long
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

#define  GPIOAEN           (1UL<<0)

#define  PIN5              (0x1UL<<5)
#define  LED_PIN           (PIN5)

#define __IO volatile //MISRA standard

typedef struct
{
  __IO uint32_t DUMMY[12];
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
} RCC_TypeDef;

#define RCC     ((RCC_TypeDef*)RCC_BASE) // RCC_BASE is a valid memory adress, in this line we are typecasting it into a pointer, to tell the compiler to handl it as memory adress, it points into a structure so RCC is a structure with beginning addres RCC_BASE
// Note : for instance if RCC_BASE is not a valid memory adress, then it's not meaningful to do this
typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t DUMMY[4];
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
} GPIO_TypeDef;

#define RCC       ((RCC_TypeDef*)RCC_BASE)
#define GPIOA     ((GPIO_TypeDef*)GPIO_BASE)
#include <stdio.h>
/*#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/
int main(void)
{
    /* 1. Enable clock access to GPIO A */
	RCC->AHB1ENR|=GPIOAEN;
	/* 2. Set PA5 as output pin */
	GPIOA_MODE_R |= (1U<<10); //same as (0x1UL<<10)
	GPIOA_MODE_R &= ~(1U<<11); //clear bit 11
	int a=2;
	printf("Value of GPIOEN %d",a);

}
