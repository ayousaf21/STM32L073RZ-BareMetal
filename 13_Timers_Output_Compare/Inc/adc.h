/*
 * adc.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Muhammad Ali
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include <stm32l073xx.h>

#define GPIOAEN 		(1U << 0)
#define ADC1_EN			(1U << 9)
#define ADC1_START		(1U << 2)
#define ADC1_EOC 		(1U << 2)
#define ADC1_RDY		(1U << 0)
#define ADC1_CONT		(1U << 13)

void PA1_ADC_init(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
