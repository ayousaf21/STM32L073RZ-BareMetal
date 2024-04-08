/*
 * uart.c
 *
 *  Created on: Mar 4, 2024
 *      Author: Muhammad Ali
 */
#include "uart.h"

void UART4_TXRX_init(void)
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

	// GPIO C11 Alternate function mode
	GPIOC->MODER &= ~(1U << 22);
	GPIOC->MODER |= (1U << 23);
	// GPIO C11 alternate function UART4_RX (AF6)
	GPIOC->AFR[1] &= ~(1U << 12);
	GPIOC->AFR[1] |= (1U << 13);
	GPIOC->AFR[1] |= (1U << 14);
	GPIOC->AFR[1] &= ~(1U << 15);

	// Enable Clock on UART4
	RCC->APB1ENR |= USART4EN;
	// Config BaudRate
	USART4->BRR = APB1_CLK / BAUDRATE;
	// Configure transmission mode RXTX
	USART4->CR1 |= (1U << 2);		// RX Enable
	USART4->CR1 |= (1U << 3);		// TX Enable
	// Enable UART4 module
	USART4->CR1 |= (1U << 0);

}

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
	while (!(USART4->ISR & (1U << 5)));
	// Write to transmit data register
	USART4->TDR = (data);
}

char UART4_read(void)
{
	// Check if receiver data register is not empty
	while (!(USART4->ISR & (1U << 5)));

	return USART4->RDR;

}


int __io_putchar(int ch)
{
	UART4_write(ch);
	return ch;
}
