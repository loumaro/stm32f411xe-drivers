//Where is the led connected?
//Port: A
//Pin:  5
#include <stdint.h>
//#define  GPIOA_OFFSET      (0x0000UL) //number of 0's doesn't matter

#define  GPIOA_BASE        (0x40020000UL)

#define  RCC_BASE          (0x40023800UL)

//#define  RCC_AHB1ENR       (*(volatile unsigned int *)(0x40023830UL)) //It's an address so we need to use pointers : RCC_AHB1ENR has the value of the adress

#define  GPIOAEN           (1U<<0)

#define  PIN5              (1U<<5)
#define  LED_PIN           (PIN5)

#define __IO volatile //MISRA standard

typedef struct
{
  __IO uint32_t DUMMY[12];
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
} RCC_TypeDef;

#define RCC     ((RCC_TypeDef*)RCC_BASE) // Astuce : On veut que l'adresse de la structure RCC soit celle de RCC_BASE,
// typecasting RCC_BASE into a pointer to the structure RCC_TypeDef and assigned it to RCC allows to set the beggining address of RCC to RCC_BASE

typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t DUMMY[4];
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
} GPIO_TypeDef;

#define RCC       ((RCC_TypeDef*)RCC_BASE)
#define GPIOA     ((GPIO_TypeDef*)GPIOA_BASE)

/*#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
*/
int main(void)
{
    /* 1. Enable clock access to GPIO A */
	RCC->AHB1ENR|=GPIOAEN;
	/* 2. Set PA5 as output pin */
	GPIOA->MODER |= (1U<<10); //same as (0x1UL<<10)
	GPIOA->MODER &= ~(1U<<11); //clear bit 11

	while(1){
		GPIOA->ODR ^= LED_PIN;
	}

}
