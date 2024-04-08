/*
 * timer.c
 *
 *  Created on: Mar 19, 2024
 *      Author: Muhammad Ali
 */


#include "timer.h"


void TIM2_1HZ_init(void)
{
	// Enable clock to TIM2
	RCC->APB1ENR |= APB1_TIM2_EN;
	// Set Prescalar Value; CLKSRC is 16Mhz
	TIM2->PSC = 1599;	// 16 000 000 / 3 200 = 5 000
	// Set auto-reload register
	TIM2->ARR = 9999; // 10 000 / 10 000 = 1Hz
	//  reset counter
	TIM2->CNT = 0;

	// Enable TIM2
	TIM2->CR1 |= TIM2_EN;

}


void TIM2_Output_Compare(void)
{
	// Enable clock on Port A
	RCC->IOPENR |= GPIOAEN;
	// Set Alternate Mode of PA5
	GPIOA->MODER &= ~(1U << 10);
	GPIOA->MODER |= (1U << 11);
	// Set Alternate Functionality TIM2_CH1 (AF5)
	GPIOA->AFR[0] |= (1U << 20);
	GPIOA->AFR[0] &= ~(1U << 21);
	GPIOA->AFR[0] |= (1U << 22);
	GPIOA->AFR[0] &= ~(1U << 23);

	// Enable clock to TIM2
	RCC->APB1ENR |= APB1_TIM2_EN;
	// Set Prescalar Value; CLKSRC is 16Mhz
	TIM2->PSC = 1599;	// 16 000 000 / 1 600 = 10 000
	// Set auto-reload register
	TIM2->ARR = 9999; // 10 000 / 10 000 = 1Hz

	// Set output compare toggle mode
	TIM2->CCMR1 |= (1U << 4) | (1U << 5);
	TIM2->CCMR1 &= ~(1U << 6);
	// Enable TIM1 CH1 in output compare mode
	TIM2->CCER |= TIM2_CMP_EN;

	//  reset counter
	TIM2->CNT = 0;

	// Enable TIM2
	TIM2->CR1 |= TIM2_EN;

}
