/*
 * systick.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Muhammad Ali
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include <stm32l073xx.h>

#define SYSTICK_LOAD		16000 			// delay = N/CLKSRC; if i want 1ms of delay and clock source is at 16Mhz -> N is 16000
#define SYSTICK_EN 			(1U << 0)
#define SYSTICK_CLKSRC		(1U << 2)
#define SYSTICK_CNT_FLAG	(1U << 16)

void sysTick_delay_ms(int delay);


#endif /* SYSTICK_H_ */
