/*
 * pwm.c
 *
 *  Created on: Mar 31, 2024
 *      Author: ThanhPC
 */

#include "pwm.h"

void tim2_pa0_pa1_pwm_init(void)
{
   /************* GPIO Config **************    */
   /* En clock access to GPIOA    */
   RCC->AHB1ENR |= GPIOAEN;

   /* Set PA0 and PA1 to ALT mode - 10 - 2 bit   */
   GPIOA->MODER |= 2U << 2*0;
   GPIOA->MODER |= 2U << 2*1;

   /* ALT type - TIM2 (AF1 - 01 - 4 bit)    */
   GPIOA->AFR[0] |= 1U << 4*0;
   GPIOA->AFR[0] |= 1U << 4*1;

   /************* TIM2 Config *********    */
   /* En clock access to TIM2    */
   RCC->APB1ENR |= TIM2EN;

   /* Set timer prescaler    */
   TIM2->PSC |= 10 - 1;   // 16 000 000 / 10 = 1 600 000

   /* Set auto-reload value    */
   TIM2->ARR |= 100 - 1; // 1 600 000/ 100 = 16 KHz

   /* Reset timer count    */
   TIM2->CNT = 0;

   /* Set PA1- CH2 and PA0 - CH1 to 110: PWM mode 1  */
   /*ch1 - bit 4:6  */
   TIM2->CCMR1 |= 6U << 4;
   /* CH2 bit 12:14  */
   TIM2->CCMR1 |= 6U << 12;

   /* En CH1 and CH2    */
   TIM2->CCER |= CCER_CC1E | CCER_CC2E;

   /* En timer    */
   TIM2->CR1 |= CR1_CEN;
}

void tim2_pa0_pa1_pwm_set_duty(uint8_t ch, uint32_t duty)
{
   /* Select channel    */
   switch (ch) {
      /* Set duty cycle    */
      case 1:
         TIM2->CCR1 = duty; // CH1
         break;
      case 2:
         TIM2->CCR2 = duty; // CH2
      default:
         break;
   }
}





