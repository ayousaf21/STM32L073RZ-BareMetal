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
	// Set Alternate Mode of PA0
	GPIOA->MODER &= ~(1U << 0);
	GPIOA->MODER |= (1U << 1);
	// Set Alternate Functionality TIM2_CH1 (AF2)
	GPIOA->AFR[0] &= ~(1U << 0);
	GPIOA->AFR[0] |= (1U << 1);
	GPIOA->AFR[0] &= ~(1U << 2);
	GPIOA->AFR[0] &= ~(1U << 3);

	// Enable clock to TIM2
	RCC->APB1ENR |= APB1_TIM2_EN;
	// Set Prescalar Value; CLKSRC is 16Mhz
	TIM2->PSC = 1599;	// 16 000 000 / 1 600 = 10 000
	// Set auto-reload register
	TIM2->ARR = 9999; // 10 000 / 10 000 = 1Hz

	// Set output compare toggle mode
	TIM2->CCMR1 |= (1U << 4) | (1U << 5);
	TIM2->CCMR1 &= ~(1U << 6);
	// Enable TIM2 CH1 in output compare mode
	TIM2->CCER |= TIM2_CMP_EN;

	//  reset counter
	TIM2->CNT = 0;

	// Enable TIM2
	TIM2->CR1 |= TIM2_EN;

}


void TIM3_Input_Capture(void)
{
	// Enable clock on Port A
	RCC->IOPENR |= GPIOAEN;
	// Set Alternate Mode of PA6
	GPIOA->MODER &= ~(1U << 12);
	GPIOA->MODER |= (1U << 13);
	// Set Alternate Functionality TIM3_CH1 (AF2)
	GPIOA->AFR[0] &= ~(1U << 24);
	GPIOA->AFR[0] |= (1U << 25);
	GPIOA->AFR[0] &= ~(1U << 26);
	GPIOA->AFR[0] &= ~(1U << 27);

	// Enable clock on TIM3
	RCC->APB1ENR |= APB1_TIM3_EN;
	// Set TIM3 prescalar
	TIM3->PSC = 15999;
	// Set auto-reload register
//	TIM3->ARR = 9999;

	// Set CH1 to input capture mode
	TIM3->CCMR1 |= (1U << 0);
	TIM3->CCMR1 &= ~(1U << 1);
	// Set CH1 to capture at rising edge
	TIM3->CCER = TIM3_CP_EN;

	// Enable TIM3
	TIM3->CR1 = TIM3_EN;

}
