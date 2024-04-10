/*
 * Timer_testing.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ThanhPC
 */

#include "timer.h"
#include "uart.h"
#include "systick.h"

#define GPIODEN     (1U << 3)
#define LED_12      (1U << 12)


int timestamp = 0;

int main(int argc, char **argv) {

   uart2_tx_init();
   tim4_pd12_output_compare();
   tim3_pc6_input_capture();

   while(1)
   {
      /* Wait till edge is captured       */
      while( !(TIM3->SR & SR_CC1IF) );

      /* Read captured value   */
      timestamp = TIM3->CCR1;
   }
}
