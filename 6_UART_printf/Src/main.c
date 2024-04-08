/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Muhammad Ali
 * @brief          : UART retargetting printf
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

#define SYS_FREQ 		2100000   // default 2.1MHz
#define APB1_CLK		SYS_FREQ

#define BAUDRATE		9600

#define GPIOAEN 		(1U << 0)
#define GPIOCEN			(1U << 2)

#define USART4EN		(1U << 19)

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

	UART4_TX_init();

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
		printf("Hello...LED is ON\n\r");
		}
//		UART4_write('Y');

	}
}
