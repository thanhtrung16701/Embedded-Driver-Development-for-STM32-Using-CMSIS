
/*
 * adc.h
 *
 *  Created on: Mar 18, 2024
 *      Author: ThanhPC
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define  ADC1EN       (1U << 8)
#define GPIOAEN       (1U << 0)
#define ADC_CH1       (1U << 0)

#define ADC_SEQ_LEN_1   0x00

#define CR2_ADCON      (1U << 0)
#define CR2_SWSTART     (1U << 30)  // Start conversion of regular channels
#define CR1_CONT      (1U << 1)     // Continuous conversion mode
#define SR_EOC        (1U << 1)   // Regular channel end of conversion

#define CR1_EOCIE     (1U << 5)
#define CR1_EOCIE     (1U << 5)   //  enable end of conversion IT.

void PA1_adc_init(void);
void PA1_adc_it_init(void);
void start_conversion(void);
uint32_t adc_read(void);
 //



#endif /* ADC_H_ */
