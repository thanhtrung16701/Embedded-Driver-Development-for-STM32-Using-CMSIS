/*
 * EXTI_Testing.c
 *
 *  Created on: Mar 21, 2024
 *      Author: ThanhPC
 */

#include "exti.h"
#include "adc.h"
#include "systick.h"
#include "uart.h"
#include "timer.h"

#define GPIODEN     (1U << 3)
#define LED_13      (1U << 13)

static void exti_callback(void);

int main(int argc, char **argv) {

   pa0_exti_init();
   uart2_tx_init();

   RCC->AHB1ENR |= GPIODEN;

   GPIOD->MODER |= (1U << 2*13);

   while(1);
}

static void exti_callback(void)
{
   printf("BTN pressed ... \n\r");
   GPIOD->ODR ^= LED_13;
   systickDelayMs(100);
}

void EXTI0_IRQHandler(void)
{
   if ( (EXTI->PR & LINE0)  ) // != 0
   {
      /* Clear PR flag       */
      EXTI->PR |= LINE0;

      exti_callback();
   }
}
