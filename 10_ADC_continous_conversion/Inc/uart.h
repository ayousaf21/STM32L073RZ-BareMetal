/*
 * uart.h
 *
 *  Created on: Mar 4, 2024
 *      Author: Muhammad Ali
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stm32l073xx.h>

#define SYS_FREQ 		16000000			// using HSI16 -> 16Mhz
#define APB1_CLK		SYS_FREQ

#define BAUDRATE		9600

#define GPIOAEN 		(1U << 0)
#define GPIOCEN			(1U << 2)

#define USART4EN		(1U << 19)

#define PIN5_SET        (1U << 5)		// LED ON
#define PIN5_RESET      (1U << 21)		// LED OFF

#define PIN13_READ		(1U << 13)		// User BTN

void UART4_TX_init(void);
void UART4_TXRX_init(void);

void UART4_write(int data);
char UART4_read(void);

#endif /* UART_H_ */
