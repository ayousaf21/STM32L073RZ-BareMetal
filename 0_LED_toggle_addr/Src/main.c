/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Muhammad Ali
 * @brief          : LED Toggle Address (L073RZ)
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

#define RCC_IOPENR_OFFSET     (0x2CUL)
#define RCC_IOPENR            (*(volatile unsigned int *)(RCC_BASE + RCC_IOPENR_OFFSET))

#define IOPAEN                (1U << 0)     // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define GPIOx_MODER_OFFSET    (0x00UL)
#define GPIOA_MODER           (*(volatile unsigned int *)(GPIOA_BASE + GPIOx_MODER_OFFSET))

#define GPIOx_ODR_OFFSET      (0x14UL)
#define GPIOA_ODR			  (*(volatile unsigned int *)(GPIOA_BASE + GPIOx_ODR_OFFSET))

#define PIN5                  (1U << 5)

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay_ms(long delay)
{
	for (int i = 0; i < (delay * 100); i++) {}
}

int main(void)
{
	/*1. Enable clock access to GPIOA */
	RCC_IOPENR |= IOPAEN;
	/*2. Set PA5 as output pin */
	GPIOA_MODER |= (1U << 10);
	GPIOA_MODER &= ~(1U << 11);

	while(1)
	{
		/*3. Set PA5 high */
//		GPIOA_ODR |= PIN5;
		/*4. Toggle PA5 */
		GPIOA_ODR ^= PIN5;
//		for (int i = 0; i < 200000; i++){}
		delay_ms(1000);

	}

}
