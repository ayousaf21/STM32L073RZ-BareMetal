/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Muhammad Ali
 * @brief          : General Purpose Timer Input Capture Driver
 ******************************************************************************
 * @attention
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include <stm32l073xx.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

uint32_t sensor_value = 0;
int timestamp = 0;

int main(void)
{
	// Enabling HSI16 to gain 16Mhz clock
	RCC->CFGR |= (1U << 15);
	RCC->CFGR &= ~(1U << 24);
	RCC->CFGR |= (1U << 25);
	RCC->CFGR &= ~(1U << 26);
	RCC->CFGR &= ~(1U << 27);
	RCC->CFGR |= (1U << 0);
	RCC->CFGR &= ~(1U << 1);
	RCC->CR |= (1 << 0);
	// Check HSI16 status flag
	while (!(RCC->CR & (1 << 2)));

	// Enable GPIO clock for Port A and C
	RCC->IOPENR |= GPIOAEN;
	RCC->IOPENR |= GPIOCEN;
	// GPIO PA5 output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
	// GPIO PC13 input mode
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	UART4_TX_init();
//	TIM2_1HZ_init();
	PA1_ADC_init();
	start_conversion();

	// Toggling LED via TIM2 output toggle mode
	TIM2_Output_Compare();

	TIM3_Input_Capture();
    /* Loop forever */
	while(1)
	{
		// Wait until rising edge is captured
		while(!(TIM3->SR & TIMx_CC1IF));

		// read value
		timestamp = TIM3->CCR1;
		printf("timestamp = %d\r\n ",timestamp);

		// Wait for UIF
//		while(!(TIM2->SR & TIM2_UIF));
		// Clear UIF
//		TIM2->SR &= ~TIM2_UIF;

//		sensor_value = adc_read();
//		printf("ADC value = %d\r\n ",(int)sensor_value );

	}
}
