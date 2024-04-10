/*
 * adc_dma.h
 *
 *  Created on: Mar 26, 2024
 *      Author: ThanhPC
 */

#ifndef ADC_DMA_H_
#define ADC_DMA_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define NUM_OF_SAMPLES      10
#define NUM_OF_CHANNELS      2

#define DMA2EN        (1U << 22)  // ahb1
#define ADC1EN        (1U << 8)   // APB2
#define GPIOAEN       (1U << 0)
#define TIM2EN        (1U << 0)
#define SCR_EN        (1U << 0)

#define DMA2EN        (1U << 22)

#define SCR_MINC  (1U << 10)   // Memory increment mode

#define SCR_PINC  (1U << 9)   // Peripheral increment mode

#define SCR_TCIE  (1U << 4)   /* Transfer complete
                                    interrupt enable */

#define SCR_TEIE   (1U << 2)   /* Transfer error
                                   interrupt enable */
#define SCR_CIRC      (1U << 8) // Circular mode enabled

#define SFCR_DMDIS  (1U << 2)   // Direct mode disable

#define LISR_TCIF0     (1U << 5)     /* Stream x transfer
                                       complete interrupt flag */

#define LISR_TEIF0     (1U << 3) /* transfer error
                                       interrupt flag */

#define LIFCR_CTCIF0   (1U << 5)  /* clear transfer complete
                                    interrupt flag */

#define LIFCR_CTEIF0   (1U << 3) /* clear transfer
                                    error interrupt flag */

/******** ADC ************ */
#define CR1_SCAN      (1U << 8) // ADC SCAN MODE
#define CR2_DMA       (1U << 8) // ADC DMA
#define CR2_DDS       (1U << 9) // DMA disable selection
#define CR2_CONT      (1U << 1) // Continuous conversion
#define CR2_ADON      (1U << 0) // Enable ADC
#define CR2_SWSTART   (1U << 30) // Software Start conversion

/******** TIMER ************ */
#define CR1_CEN     (1U << 0)   // CEN: Counter enable

void adc_dma_init(void);
void adc_tim_dma_init(void);


#endif /* ADC_DMA_H_ */
