/*
 * 5_UART_TX.c
 *
 *  Created on: Mar 13, 2024
 *      Author: ThanhPC
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define GPIOAEN      (1U << 0)
#define UART2EN      (1U << 17)

#define SYS_FREQ      16000000
#define APB1_CLK      SYS_FREQ

#define UART_BAUDRATE   115200

#define CR1_TE          (1U << 3)
#define CR1_UE          (1U << 13)
#define SR_TXE          (1U << 7)

static void uart_set_baudrate(USART_TypeDef *pUARTx, uint32_t PeriClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriClk, uint32_t BaudRate);

void uart2_tx_init(void);
void uart2_write(int ch);

void delay(void)
{
   for(uint32_t i = 0; i < 100000;i++);
}

int __io_putchar(int ch)
{
   uart2_write(ch);
   return ch;
}

int main(void)
{
   uart2_tx_init();
   while(1)
   {
//      printf("Hello from STM32F4 .... \n\r");
      uart2_write('Y');
      delay();

   }
}
