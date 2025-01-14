/*
 * timer.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Muhammad Ali
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <stm32l073xx.h>

#define APB1_TIM2_EN		(1U << 0)
#define TIM2_EN				(1U << 0)
#define TIM2_UIF			(1U << 0)

void TIM2_1HZ_init(void);

#endif /* TIMER_H_ */
