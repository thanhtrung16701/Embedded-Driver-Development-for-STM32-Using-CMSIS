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



int main(int argc, char **argv) {

   uart2_tx_init();
    tim4_pd12_output_compare();


//   while(1)
//   {
//      printf("a second pass !! \n\r ");
//      systickDelayMs(500);
//   }
}
