/*
 * timer.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ThanhPC
 */

#include "timer.h"



void tim2_1hz_init(void)
{
   /*Enable clock  tim2    */
   RCC->APB1ENR |= TIM2EN;

   /*Set pre value*/
   TIM2->PSC = 1600 - 1; // 16 000 000 / 1600 = 10 000

   /* Set auto-reload value */
   TIM2->ARR = 10000 -1 ; // 10000 / 10000 = 1 Hz

   /* Clear the counter */
   TIM2->CNT = 0;

   /* Enable timer */
   TIM2->CR1 |= CR1_CEN;
}

void tim2_1hz_it_init(void)
{
   /*Enable clock  tim2    */
   RCC->APB1ENR |= TIM2EN;

   /*Set pre value*/
   TIM2->PSC = 1600 - 1; // 16 000 000 / 1600 = 10 000

   /* Set auto-reload value */
   TIM2->ARR = 10000 -1 ; // 10000 / 10000 = 1 Hz

   /* Clear the counter */
   TIM2->CNT = 0;

   /* Enable timer */
   TIM2->CR1 |= CR1_CEN;

   /* En TIM interrupt    */
   TIM2->DIER |= DIER_UIE;

   /* Enable TIM IT in NVIC    */
   NVIC_EnableIRQ(TIM2_IRQn);
}

void tim2_pa5_output_compare(void)
{
   /* EN clock access to GPIOA  */
   RCC->AHB1ENR |= GPIOAEN;

   /* PA5-> ALT mode */
   GPIOA->MODER |= (2U << 2*5);

   /* Set AF1 (PA5 alt function) to TIM2
    * AF5 -> AFRL5
    */
   GPIOA->AFR[0]  |= AFR5_TIM2;

   /*Enable clock  tim2,   */
   RCC->APB1ENR |= TIM2EN;


   /*Set pre value*/
   TIM2->PSC = 1600 - 1; // 16 000 000 / 1600 = 10 000

   /* Set auto-reload value */
   TIM2->ARR = 10000 - 1 ; // 10000 / 10000 = 1 Hz

   /* Set the output compare toggle mode */
   TIM2->CCMR1 |= OC_TOGGLE;

   /* En tim2 ch1 in compare mode */
   TIM2->CCER |= CCER_CC1E;

   /* Clear the counter */
   TIM2->CNT = 0;

   /* Enable timer */
   TIM2->CR1 |= CR1_CEN;
}

void tim4_pd12_output_compare(void)
{
   /* EN clock access to GPIOD  */
   RCC->AHB1ENR |= GPIODEN;

   /* PD12-> ALT mode */
   GPIOD->MODER |= (2U << 2*12);

   /* Set AF2 (PD12 alt function) to TIM4
    * PD12 -> AFRH12
    */
   GPIOD->AFR[1]  |= AFR12_TIM4;

   /*Enable clock  tim4,   */
   RCC->APB1ENR |= TIM4EN;


   /*Set pre value*/
   TIM4->PSC = 1600 - 1; // 16 000 000 / 1600 = 10 000

   /* Set auto-reload value */
   TIM4->ARR = 10000 - 1 ; // 10000 / 10000 = 1 Hz -> 1s

   /* Set the output compare toggle mode */
   TIM4->CCMR1 |= OC_TOGGLE;

   /* En tim4 ch1 in compare mode */
   TIM4->CCER |= CCER_CC1E;

   /* Clear the counter */
   TIM4->CNT = 0;

   /* Enable timer */
   TIM4->CR1 |= CR1_CEN;
}

void tim3_pc6_input_capture(void)
{
   /* EN clock access to GPIOC  */
   RCC->AHB1ENR |= GPIOCEN;

   /* PC6-> ALT mode */
   GPIOC->MODER |= 2U << 2*6;

   /* Set AF2 (PC6 alt function) to TIM3
    * PC6 -> AFRL6
    */
   GPIOC->AFR[0] |= AFR6_TIM3;

   /*Enable clock to tim3   */
   RCC->APB1ENR |= TIM3EN;

   /*Set pre value*/
   TIM3->PSC |= 1600 - 1;  // 16 000 000 / 1600 = 10 000

   /* SET CH1 to input capture      */
   TIM3->CCMR1 |= CCMR1_CC1S;

   /* SET ch2 to capture at rising edge    */
   TIM3->CCER |= CCER_CC1E;

   /* En timer    */
   TIM3->CR1 |= CR1_CEN;
}

















