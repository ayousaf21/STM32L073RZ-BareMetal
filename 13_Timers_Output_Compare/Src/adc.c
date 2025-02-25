/*
 * adc.c
 *
 *  Created on: Mar 13, 2024
 *      Author: Muhammad Ali
 */
#include "adc.h"

void PA1_ADC_init(void)
{
	// Enable clock on PA1
	RCC->IOPENR |= GPIOAEN;
	// Set PA1 mode
	GPIOA->MODER |= (1U << 2);
	GPIOA->MODER |= (1U << 3);
	// Enable clock on ADC
	RCC->APB2ENR |= ADC1_EN;
	// Channel Selection
	ADC1->CHSELR = (1U << 1);
	ADC1->CFGR1 &= ~(1U << 15);
	// Resolution 12-bit
	ADC1->CFGR1 &= ~(1U << 3);
	ADC1->CFGR1 &= ~(1U << 4);
	// ADC Clock PCLK/4
	ADC1->CFGR2 &= ~(1U << 30);
	ADC1->CFGR2 &= ~(1U << 31);
	// ADC Sampling time 160.5 clock cycles
//	ADC1->SMPR |= (1U << 0);
//	ADC1->SMPR |= (1U << 1);
//	ADC1->SMPR |= (1U << 2);
	// VREF Enable
	ADC1_COMMON->CCR |= (1U << 22);
	// Enable ADC
	ADC1->ISR |= ADC1_RDY;
	ADC1->CR |= (1U << 0);
	// Config ADC parameters

}


void start_conversion(void)
{
//	while (!(ADC1->ISR & ADC1_RDY)){}
	// Enable Continous Conversion
	ADC1->CFGR1 |= ADC1_CONT;

	ADC1->CR |= ADC1_START;

}


uint32_t adc_read(void)
{
	// Wait for converstion to complete
	while(!(ADC1->ISR & ADC1_EOC)){}
	// read from data register
	return (ADC1->DR);

}
