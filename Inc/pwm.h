/*
 * pwm.h
 *
 *  Created on: Mar 31, 2024
 *      Author: ThanhPC
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include "string.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"



#define TIM2EN    (1U << 0)
#define TIM3EN    (1U << 1)
#define TIM4EN    (1U << 2)

#define CR1_CEN     (1U << 0)   // CEN: Counter enable
#define OC_TOGGLE   (3U << 4)    // Output compare 1 mode -> 011 TOGGLE
#define CCER_CC1E   (1U << 0)    // Capture/Compare 1 output enable

#define GPIOAEN   (1U << 0)
#define GPIOCEN   (1U << 2)
#define GPIODEN   (1U << 3)


#define DIER_UIE    (1U << 0)   // Update interrupt enable
#define CCER_CC1E   (1U << 0) //Capture/Compare 1 output enable
#define CCER_CC2E   (1U << 4) //Capture/Compare 2 output enable

void tim2_pa0_pa1_pwm_init(void);
void tim2_pa0_pa1_pwm_set_duty(uint8_t ch, uint32_t duty);




#define SR_UIF      (1U << 0)  // : Update interrupt flag
#define SR_CC1IF    (1U << 1)   // Capture/compare 1 interrupt flag


#endif /* PWM_H_ */
