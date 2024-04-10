/*
 * Timer_testing.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ThanhPC
 */

#include "timer.h"
#include "uart.h"

#define GPIODEN     (1U << 3)
#define LED_14      (1U << 14)

static void tim2_callback(void);


int main(int argc, char **argv) {
   RCC->AHB1ENR |= GPIODEN;

   GPIOD->MODER |= (1U << 2*14);

   uart2_tx_init();
   tim2_1hz_it_init();

   while(1);
}

static void tim2_callback(void)
{
   printf("a second pass !! \n\r ");
   GPIOD->ODR ^= LED_14;
}

void TIM2_IRQHandler(void)
{
   /* Clear update it flag (UIF)    */
   TIM2->SR &= ~SR_UIF;

   // do something
   tim2_callback();
}
