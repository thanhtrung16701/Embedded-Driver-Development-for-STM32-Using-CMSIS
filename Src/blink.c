/*
 * blink.c
 *
 *  Created on: Mar 16, 2024
 *      Author: ThanhPC
 */


#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

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


int main(void)
{
   RCC->AHB1ENR |= GPIODEN;
   RCC->AHB1ENR |= GPIOAEN;
   GPIOD->MODER |= 1U << 24;

   GPIOD->MODER &= ~(1U << 25);

   GPIOD->MODER |= 1U << 26;
   GPIOD->MODER &= ~(1U << 27);
   GPIOD->MODER |= 1U << 28;
   GPIOD->MODER &= ~(1U << 29);
   GPIOD->MODER |= 1U << 30;
   GPIOD->MODER &= ~(1U << 31);
   while(1)
   {
         if ( (GPIOA->IDR & BTN) )
         {
            GPIOD->BSRR = LED_PIN1 ;

         }else
         {
            GPIOD->BSRR = 1U << 28 ;
         }
   }
}
