/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Muhammad Ali
 * @brief          : GPIO Toggle via BSRR
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
#include <stm32l073xx.h>

#define GPIOAEN 		(1U << 0)
#define PIN5_SET        (1U << 5)
#define PIN5_RESET      (1U << 21)

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay_ms(long delay)
{
	for (int i = 0; i < (delay * 100); i++) {}
}


int main(void)
{
	RCC->IOPENR |= GPIOAEN;
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
    /* Loop forever */
	while(1)
	{
		GPIOA->BSRR |= PIN5_SET;
		delay_ms(500);
		GPIOA->BSRR |= PIN5_RESET;
		delay_ms(500);

	}
}
