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
#define LED_13      (1U << 13)

int main(int argc, char **argv) {
   RCC->AHB1ENR |= GPIODEN;

   GPIOD->MODER |= (1U << 2*13);

   uart2_tx_init();
   systick_1hz_it();

   while(1);
}

static void systick_callback(void)
{
   printf("A second passed !! \n\r");
   GPIOD->ODR ^= LED_13;
}
void SysTick_Handler(void)
{
   // do something
   systick_callback();
}
