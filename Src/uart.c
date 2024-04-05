/*
 * uart.c
 *
 *  Created on: Mar 16, 2024
 *      Author: ThanhPC
 */

#include "uart.h"

#define GPIOAEN      (1U << 0)
#define UART2EN      (1U << 17)

#define SYS_FREQ      16000000
#define APB1_CLK      SYS_FREQ

#define UART_BAUDRATE   115200




// MODER: 2 bits  PA3 -> MODE 3
//00: Input (reset state)
//01: General purpose output mode
//10: Alternate function mode
//11: Analog mode

//
// Alternate function low/ high 4 bit : PA2 -> AFRL2 // PA9 -> AFRH9

void delay(void)
{
   for(uint32_t i = 0; i < 100000; i++);
}


void uart2_tx_init(void)
{
   /**
    * ****************config uart gpio pin**************
    * EN clock access to gpioa */
    RCC->AHB1ENR |= GPIOAEN;


    /** Set PA2 to ALT func mode, ALT func type to TX(AF7)  */
   GPIOA->MODER |= (2U << 2*2);   // MODER 2 bit

   GPIOA->AFR[0] |= (7U << 4*2);  // ALT 4 bit, AF7

   /*
    * ******Config uart module**********
    *   en clock access to uart2*/
   RCC->APB1ENR |= UART2EN;

    /* config baudrate*/
   uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* config config transfer direction*/
   USART2->CR1 |= CR1_TE;

    /* config uart module */
   USART2->CR1 |= CR1_UE;
}

void uart2_tx_it_init(void)
{
   /**
    * ****************config uart gpio pin**************
    * EN clock access to gpioa */
    RCC->AHB1ENR |= GPIOAEN;


    /** Set PA2 to ALT func mode, ALT func type to TX(AF7)  */
   GPIOA->MODER |= (2U << 2*2);   // MODER 2 bit

   GPIOA->AFR[0] |= (7U << 4*2);  // ALT 4 bit

   /*
    * ******Config uart module**********
    *   en clock access to uart2*/
   RCC->APB1ENR |= UART2EN;

    /* config baudrate*/
   uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* config config transfer direction*/
   USART2->CR1 |= CR1_TE;

   /* Enable TNE interrupt    */
   USART2->CR1 |= CR1_TXEIE;

   /* En UART interrupt in NVIC    */
   NVIC_EnableIRQ(USART2_IRQn);

    /* config uart module */
   USART2->CR1 |= CR1_UE;
}

void uart2_rx_init(void)
{
   /**
    * ****************config uart gpio pin**************
    * EN clock access to gpioa */
    RCC->AHB1ENR |= GPIOAEN;


    /** Set PA3 to ALT func mode, ALT func type to TX(AF7)  */
   GPIOA->MODER |= (2U << 2*3);   // MODER 2 bits

   GPIOA->AFR[0] |= (7U << 4*3);  // ALT 4 bits

   /*
    * ******Config uart module**********
    *   en clock access to uart2*/
   RCC->APB1ENR |= UART2EN;

    /* config baudrate*/
   uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* config config transfer direction*/
   USART2->CR1 |= CR1_RE;

    /* config uart module */
   USART2->CR1 |= CR1_UE;
}


void uart2_txrx_init(void)
{
   /*********************** TX *************************
    *         *config uart gpio pin*
    * EN clock access to gpioa */
    RCC->AHB1ENR |= GPIOAEN;

    /** Set PA2 to ALT func mode, ALT func type to TX(AF7)  */
   GPIOA->MODER |= (2U << 2*2);

   GPIOA->AFR[0] |= (7U << 4*2);

  /******************************* RX ****************************/
   /** Set PA3 to ALT func mode, ALT func type to TX(AF7)  */
  GPIOA->MODER |= (2U << 2*3);  // 2 bits

  GPIOA->AFR[0] |= (7U << 4*3);

  /** ******Config uart module**********
       EN clock access to uart2
  **/
   RCC->APB1ENR |= UART2EN;

    /* config baudrate*/
   uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* config config transfer direction*/
   USART2->CR1 |= (CR1_TE | CR1_RE);

    /* config uart module */
   USART2->CR1 |= CR1_UE;
}



void uart_set_baudrate(USART_TypeDef *pUARTx, uint32_t PeriClk, uint32_t BaudRate)
{
   pUARTx->BRR = compute_uart_bd(PeriClk,BaudRate);
}

uint16_t compute_uart_bd(uint32_t PeriClk, uint32_t BaudRate)
{
   return ( (PeriClk + BaudRate/2U)/BaudRate );
}

