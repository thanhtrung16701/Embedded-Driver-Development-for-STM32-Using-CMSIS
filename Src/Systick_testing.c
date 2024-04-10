/*
 * Systick_testing.c
 *
 *  Created on: Mar 19, 2024
 *      Author: ThanhPC
 */

#include "stm32f407xx.h"
#include "uart.h"
#include "systick.h"

#define GPIODEN     (1U << 3)
#define LED_12      (1U << 12)

int main(int argc, char **argv) {
   RCC->AHB1ENR |= GPIODEN;

   GPIOD->MODER |= (1U << 2*12);

   uart2_tx_init();
   while(1)
   {

      systickDelayMs(1000);
   }
}

