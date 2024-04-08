/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Muhammad Ali
 * @brief          : LED Toggle Address using Structers (L073RZ)
 ******************************************************************************
 * @attention
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define __IO volatile
// Where is LED connected?
// Port: A
// Pin:  5

#define PERIPH_BASE           (0x40000000UL)

#define AHBPERIPH_OFFSET      (0x00020000UL)
#define AHBPERIPH_BASE        (PERIPH_BASE + AHBPERIPH_OFFSET)

#define IOPORT_OFFSET         (0x10000000UL)
#define IOPORT_BASE           (PERIPH_BASE + IOPORT_OFFSET)
#define GPIOA_OFFSET          (0x00000000UL)

#define GPIOA_BASE            (IOPORT_BASE + GPIOA_OFFSET)

#define RCC_OFFSET            (0x00001000UL)
#define RCC_BASE 			  (AHBPERIPH_BASE + RCC_OFFSET)

#define IOPAEN                (1U << 0)     // 0b 0000 0000 0000 0000 0000 0000 0000 0001


#define PIN5                  (1U << 5)

/**
 * @brief :	Structure for RCC register map
 */
typedef struct {
	__IO uint32_t CR;			/*Clock control register,								Address Offset: 0x00*/
	__IO uint32_t ICSCR;		/*Internal clock sources calibration register,			Address Offset: 0x04*/
	__IO uint32_t CRRCR;		/*Clock recovery RC register,							Address Offset: 0x08*/
	__IO uint32_t CFGR;			/*Clock configuration register,							Address Offset: 0x0C*/
	__IO uint32_t CIER;			/*Clock interrupt enable register,						Address Offset: 0x10*/
	__IO uint32_t CIFR;			/*Clock interrupt flag register,						Address Offset:	0x14*/
	__IO uint32_t CICR;			/*Clock interrupt clear register,						Address Offset: 0x18*/
	__IO uint32_t IOPRSTR;		/*GPIO reset register,									Address Offset: 0x1C*/
	__IO uint32_t AHBRSTR;		/*AHB peripheral reset register,						Address Offset: 0x20*/
	__IO uint32_t APB2RSTR;		/*APB2 peripheral reset register,						Address Offset: 0x24*/
	__IO uint32_t APB1RSTR;		/*APB1 peripheral reset register,						Address Offset: 0x28*/
	__IO uint32_t IOPENR;		/*GPIO clock enable register,							Address Offset: 0x2C*/
	__IO uint32_t AHBENR;		/*AHB peripheral clock enable register,					Address Offset: 0x30*/
	__IO uint32_t APB2ENR;		/*APB2 peripheral clock enable register,				Address Offset: 0x34*/
	__IO uint32_t APB1ENR;		/*APB1 peripheral clock enable register,				Address Offset: 0x38*/
	__IO uint32_t IOPSMEN;		/*GPIO clock enable in Sleep mode register,				Address Offset: 0x3C*/
	__IO uint32_t AHBSMENR;		/*AHB peripheral clock enable in Sleep mode register,	Address Offset: 0x40*/
	__IO uint32_t APB2SMENR;	/*APB2 peripheral clock enable in Sleep mode register,	Address Offset: 0x44*/
	__IO uint32_t APB1SMENR;	/*APB1 peripheral clock enable in Sleep mode register,	Address Offset: 0x48*/
	__IO uint32_t CCIPR;		/*Clock configuration register,							Address Offset: 0x4C*/
	__IO uint32_t CSR;			/*Clock Control/status register,						Address Offset: 0x50*/

} RCC_TypeDef;

/*******************************************************************************************************************/
/*******************************************************************************************************************/
/**
 * @brief :	Structure for GPIO register map
 */

typedef struct {
	__IO uint32_t MODER;		/*GPIO port mode register,					Address Offset: 0x00*/
	__IO uint32_t OTYPER;		/*GPIO port output type register,			Address Offset: 0x04*/
	__IO uint32_t OSPEEDR;		/*GPIO port output speed register,			Address Offset: 0x08*/
	__IO uint32_t PUPDR;		/*GPIO port pull-up/pull-down register,		Address Offset: 0x0C*/
	__IO uint32_t IDR;			/*GPIO port input data register,			Address Offset: 0x10*/
	__IO uint32_t ODR;			/*GPIO port output data register,			Address Offset:	0x14*/
	__IO uint32_t BSRR;			/*GPIO port bit set/reset register,			Address Offset: 0x18*/
	__IO uint32_t LCKR;			/*GPIO port configuration lock register,	Address Offset: 0x1C*/
	__IO uint32_t AFRL;			/*GPIO alternate function low register,		Address Offset: 0x20*/
	__IO uint32_t AFRH;			/*GPIO alternate function high register		Address Offset: 0x24*/
	__IO uint32_t BRR;			/*GPIO port bit reset register,				Address Offset: 0x28*/

} GPIO_TypeDef;
/********************************************************************************************************************/
/********************************************************************************************************************/

#define RCC		((RCC_TypeDef*) RCC_BASE)
#define GPIOA	((GPIO_TypeDef*) GPIOA_BASE)

void delay_ms(long delay)
{
	for (int i = 0; i < (delay * 100); i++) {}
}

int main(void)
{
	/*1. Enable clock access to GPIOA */
	RCC->IOPENR |= IOPAEN;
	/*2. Set PA5 as output pin */
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while(1)
	{
		/*3. Toggle PA5 */
		GPIOA->ODR |= PIN5;
		delay_ms(500);
		GPIOA->ODR &= ~PIN5;
		delay_ms(1500);

	}

}
