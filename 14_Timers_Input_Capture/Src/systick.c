/*
 * systick.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Muhammad Ali
 */

#include "systick.h"


void sysTick_delay_ms(int delay)
{
	// Reload the SysTick value
	SysTick->LOAD = SYSTICK_LOAD;

	// Clear SysTick current value
	SysTick->VAL = 0;

	// Enable SysTick and use Processor Clock
	SysTick->CTRL = SYSTICK_EN | SYSTICK_CLKSRC;

	for (int i = 0; i < delay; i++)
	{
		// wait until COUNTFLAG is set
		while (!(SysTick->CTRL & SYSTICK_CNT_FLAG));

	}

	SysTick->CTRL = 0;

}
