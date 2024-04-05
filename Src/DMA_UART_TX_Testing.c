/*
 * EXTI_UART_RX_Testing.c
 *
 *  Created on: Mar 21, 2024
 *      Author: ThanhPC
 */

#include "uart.h"
#include "exti.h"
#include "systick.h"
#include "timer.h"

#define GPIODEN      (1U << 3)
#define GPIOAEN         (1U << 0)
#define BTN           (1U << 0)

#define LED13        (1U << 13)


char message[40] = "Hello world from STM32 DMA transfer \n\r";


static void dma_callback(void);


int main(int argc, char **argv) {


   RCC->AHB1ENR |= GPIODEN;

   GPIOD->MODER |= (1U << 2*13);

   uart2_tx_init();

   dma1_sream6_init((uint32_t)message, (uint32_t)&USART2->DR, 40);
   while(1);

}
static void dma_callback(void)
{
   while(1)
   {
      if ( (GPIOA->IDR & BTN) )
      {
         while(GPIOA->IDR & BTN);
         printf("BTN pressed ... \n\r");
         GPIOD->ODR ^= LED13 ;
         systickDelayMs(100);
      }
   }
}

void DMA1_Stream6_IRQHandler(void)
{
   if(DMA1->HISR & HISR_TCIF6)
   {
      // clear flag
      DMA1->HIFCR |= HIFCR_CTCIF6;
      // do something
      dma_callback();
   }
}


