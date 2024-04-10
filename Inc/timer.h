/*
 * timer.h
 *
 *  Created on: Mar 19, 2024
 *      Author: ThanhPC
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "systick.h"

#define TIM2EN    (1U << 0)
#define TIM3EN    (1U << 1)
#define TIM4EN    (1U << 2)

#define CR1_CEN     (1U << 0)   // CEN: Counter enable
#define OC_TOGGLE   (3U << 4)    // Output compare 1 mode -> 011 TOGGLE
#define CCER_CC1E   (1U << 0)    // Capture/Compare 1 output enable

#define GPIOAEN   (1U << 0)
#define GPIOCEN   (1U << 2)
#define GPIODEN   (1U << 3)

#define AFR5_TIM2   (1U << 5*4)
#define AFR12_TIM4   (2U << 4*4)
#define AFR6_TIM3   (2U << 4*6)
#define CCMR1_CC1S    (1U << 0)

#define DIER_UIE    (1U << 0)   // Update interrupt enable
#define CCER_CC1E   (1U << 0) //Capture/Compare 1 output enable
#define CCER_CC2E   (1U << 4) //Capture/Compare 2 output enable

void tim2_1hz_init(void);
void tim2_1hz_it_init(void);

void tim2_pa5_output_compare(void);
void tim4_pd12_output_compare(void);
void tim3_pc6_input_capture(void);



#define SR_UIF      (1U << 0)  // : Update interrupt flag
#define SR_CC1IF    (1U << 1)   // Capture/compare 1 interrupt flag

#endif /* TIMER_H_ */
