/*
 * pwm_dma.h
 *
 *  Created on: Apr 1, 2024
 *      Author: ThanhPC
 */

#ifndef PWM_DMA_H_
#define PWM_DMA_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"
#include "systick.h"

#define TIM2EN    (1U << 0)
#define TIM3EN    (1U << 1)
#define TIM4EN    (1U << 2)

#define CR1_CEN     (1U << 0)   // CEN: Counter enable

#define GPIOAEN   (1U << 0)
#define GPIOCEN   (1U << 2)
#define GPIODEN   (1U << 3)

#define SR_UIF      (1U << 0)  // : Update interrupt flag
#define SR_CC1IF    (1U << 1)   // Capture/compare 1 interrupt flag

#define DIER_UDE    (1U << 8)   // Update DMA request enable

#define DIER_CC1DE  (1U << 9) /* Capture/Compare 1
                              DMA  enable */
#define DIER_CC2DE  (1U << 10) /* Capture/Compare 2
                              DMA  enable */

#define DIER_TDE  (1U << 14) // Trigger DMA request enable

#define CCER_CC1E   (1U << 0) //Capture/Compare 1 output enable
#define CCER_CC2E   (1U << 4) //Capture/Compare 2 output enable

/**************** DMA  ***********/
#define DMA1EN        (1U << 21)

#define SCR_EN    (1U << 0)
#define SCR_CHSEL3  (3U << 25) // 011 - CH3
#define SCR_MINC  (1U << 10)   // Memory increment
#define SCR_TCIE    (1U << 4)  // Transfer complete interrupt enable
#define SCR_CIRC    (1U << 8) // Circular mode

#define SCR_MSIZE32  (2U << 13) // Mem size 10: word (32-bit)

#define SCR_PSIZE32  (2U << 11) // Peri size 10: 32-bit

#define SCR_DIR_M2P   (1U << 6) // transfer direction 01: M2P

/* high interrupt flag clear register */
#define HIFCR_CTCIF5      (1U << 11)  /* clear transfer
                                 complete interrupt flag S5 */
#define HIFCR_CTCIF6      (1U << 21)  /* clear transfer
                                 complete interrupt flag S6 */


void tim2_pa0_pa1_pwm_init(void);
void tim2_pa0_pa1_pwm_set_duty(uint8_t ch, uint32_t duty);
void tim2_pa0_pa1_pwm_dma_init(void);





#endif /* PWM_DMA_H_ */
