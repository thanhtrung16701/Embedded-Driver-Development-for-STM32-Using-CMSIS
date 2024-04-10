/*
 * Timer_testing.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ThanhPC
 */

#include "timer.h"
#include "uart.h"

#define GPIODEN     (1U << 3)
#define LED_12      (1U << 12)



int main(int argc, char **argv) {
   RCC->AHB1ENR |= GPIODEN;

   GPIOD->MODER |= (1U << 2*12);

   uart2_tx_init();
   tim2_1hz_init();

   while(1)
   {
      while( !(TIM2->SR & SR_UIF) ); // wait till UIF is set -
                                    // cờ set, đk trong while sai (= 0) -> thực hiện lệnh tiếp
      /* Clear UIF */
      TIM2->SR &= ~SR_UIF;

      printf("a second pass !! \n\r ");
      GPIOD->ODR ^= LED_12;
   }
}
