/*
 * EXTI_UART_RX_Testing.c
 *
 *  Created on: Mar 21, 2024
 *      Author: ThanhPC
 */

#include "uart.h"
#include "exti.h"
#include "timer.h"

#define GPIODEN      (1U << 3)
#define GPIOAEN      (1U << 0)
#define BTN           (1U << 0)

#define LED13        (1U << 13)
char key;

static void uart_callback(void);


int main(int argc, char **argv) {
   RCC->AHB1ENR |= GPIODEN;
   RCC->AHB1ENR |= GPIOAEN;

   GPIOD->MODER |= (1U << 2*13);

   uart2_rx_it_init();
   while(1);
}
static void uart_callback(void)
{
   key = USART2->DR;

   if (key == '1') {
     GPIOD->ODR |= LED13;
   } else {
     GPIOD->ODR &= ~ LED13;
   }
}

void USART2_IRQHandler(void)
{
   /* Check if RXNE is set    */
   if (USART2->SR & SR_RXNE )
   {
      // do something
     uart_callback();
   }
}
