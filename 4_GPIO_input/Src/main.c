/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Muhammad Ali
 * @brief          : GPIO input for LED toggle
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
#define GPIOCEN			(1U << 2)

#define PIN5_SET        (1U << 5)
#define PIN5_RESET      (1U << 21)

#define PIN13_READ		(1U << 13)

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay_ms(long delay)
{
	for (int i = 0; i < (delay * 100); i++) {}
}


int main(void)
{
	// Enable GPIO clock for Port A and C
	RCC->IOPENR |= GPIOAEN;
	RCC->IOPENR |= GPIOCEN;
	// GPIO PA5 output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
	// GPIO PC13 input mode
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);
    /* Loop forever */
	while(1)
	{
		// User BTN is active low
		if (GPIOC->IDR & PIN13_READ)
		{
		GPIOA->BSRR |= PIN5_RESET;	// LED OFF
		}
		else {
		GPIOA->BSRR |= PIN5_SET;	// BTN pressed, LED ON
		}

	}
}
