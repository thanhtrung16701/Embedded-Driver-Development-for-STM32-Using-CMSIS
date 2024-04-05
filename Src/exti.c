/*
 * exti.c
 *
 *  Created on: Mar 21, 2024
 *      Author: ThanhPC
 */

#include "exti.h"


#define   GPIOAEN   (1U << 0)
#define   SYSCFGEN   (1U << 14)



void pa0_exti_init()
{
   /* Disable global IT    */
   __disable_irq();

   /* En clock access PA0    */
   RCC->AHB1ENR |= GPIOAEN;

   /* Set PA0 as input     */
   GPIOA->MODER &= ~(1U << 2*0);

   /* En clock access to SYSCFG   */
   RCC->APB2ENR |= SYSCFGEN;

   /* Select PORTA for EXTI0    */
   SYSCFG->EXTICR[0] &= ~ (1U << 4*0);

   /* Unmask EXTI0    */
   EXTI->IMR |= 1U << 0;

   /* Select falling edge trigger     */
   EXTI->FTSR |= (1U << 0);

   /* En EXTI0 line in NVIC    */
   NVIC_EnableIRQ(EXTI0_IRQn);

   /* En global IT  */
   __enable_irq();
}
