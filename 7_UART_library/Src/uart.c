/*
 * uart.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Muhammad Ali
 */
#include "uart.h"


void UART4_TX_init(void)
{
	// Enable Clock on GPIO Port C
	RCC->IOPENR |= GPIOCEN;
	// GPIO C10 Alternate function mode
	GPIOC->MODER &= ~(1U << 20);
	GPIOC->MODER |= (1U << 21);
	// GPIO C10 alternate function UART4_TX (AF6)
	GPIOC->AFR[1] &= ~(1U << 8);
	GPIOC->AFR[1] |= (1U << 9);
	GPIOC->AFR[1] |= (1U << 10);
	GPIOC->AFR[1] &= ~(1U << 11);

	// Enable Clock on UART4
	RCC->APB1ENR |= USART4EN;
	// Config BaudRate
	USART4->BRR = APB1_CLK / BAUDRATE;
	// Configure transmission mode
	USART4->CR1 |= (1U << 3);
	// Enable UART4 module
	USART4->CR1 |= (1U << 0);

}

void UART4_write(int data)
{
	// Check if transmit data register is empty
	while (!(USART4->ISR & (1U << 7)));
	// Write to transmit data register
	USART4->TDR = (data);
}


int __io_putchar(int ch)
{
	UART4_write(ch);
	return ch;
}
