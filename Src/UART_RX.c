/*
 * UART_RX.c
 *
 *  Created on: Mar 17, 2024
 *      Author: ThanhPC
 */

#include "uart.h"

#define GPIODEN      (1U << 3)
#define GPIOAEN      (1U << 0)
#define BTN           (1U << 0)

#define PIN12        (1U << 12)
#define PIN13        (1U << 13)
#define PIN14        (1U << 14)
#define PIN15        (1U << 15)

#define LED_PIN1        PIN12
#define LED_PIN2        PIN13
#define LED_PIN3        PIN14
#define LED_PIN4        PIN15

uint8_t key;
int main(void)
{

   RCC->AHB1ENR |= GPIODEN;
   RCC->AHB1ENR |= GPIOAEN;

   GPIOD->MODER |= (1U << 2*12);
//   GPIOD->MODER &= ~(1U << 25);

   uart2_txrx_init();

   while(1)
   {
      key = uart2_read();
      if (key == '1') {
         GPIOD->ODR |= LED_PIN1;
      } else {
         GPIOD->ODR &= ~ LED_PIN1;
      }

   }
}

