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

void uart2_rx_it_init(void)
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

  /** ****** Config uart module **********
       EN clock access to uart2
  **/
   RCC->APB1ENR |= UART2EN;

    /* config baudrate*/
   uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    /* config config transfer direction*/
   USART2->CR1 |= (CR1_TE | CR1_RE );

   /* Enable RXNE interrupt    */
   USART2->CR1 |= CR1_RXNEIE;

   /* En UART interrupt in NVIC    */
   NVIC_EnableIRQ(USART2_IRQn);


    /* config uart module */
   USART2->CR1 |= CR1_UE;
}

void dma1_sream6_init(uint32_t src, uint32_t dst, uint32_t len)
{
   /* TX memory to peripheral    */

   /* En clock access to DMA    */
   RCC->AHB1ENR |= DMA1EN;

   /* Disable DMA1 stream 6    */
   DMA1_Stream6->CR &= ~DMA_SCR_EN;

   /* Wait till DMA1 stream 6 is disable    */
   while(DMA1_Stream6->CR & DMA_SCR_EN);

   /* Clear all IT flags of stream 6    */
   DMA1->HIFCR |= 1U  << 16;
   DMA1->HIFCR |= 15U << 18;


   /* Set the destination buffer    */
   DMA1_Stream6->PAR = dst;   //  peripheral addr reg

   /* Set the source buffer     */
   DMA1_Stream6->M0AR = src;

   /* Set the length    */
   DMA1_Stream6->NDTR = len;       // number of data

   /* Select stream6 CH4    */
   DMA1_Stream6->CR |= SCR_CHSEL4;

   /* EN memory increment   */
   DMA1_Stream6->CR |= SCR_MINC;

   /* Config transfer direction   */
   DMA1_Stream6->CR |= SCR_DIR_MP;

   /* EN DMA transfer complete IT    */
   DMA1_Stream6->CR |= SCR_TCIE;

   /* EN direct mode and disable  FIFO    */
   DMA1_Stream6->FCR = 0;

   /* EN DMA1 Stream 6    */
   DMA1_Stream6->CR |= DMA_SCR_EN;

   /* En UART2 transmit DMA    */
   USART2->CR3 |= CR3_DMAT;

   /* DMA IT enable in NVIC    */
   NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void uart2_write(int ch)
{
   /* make sure trans data reg empty */
   while( !(USART2->SR & SR_TXE) );
   /* Write to trans data reg */
   USART2->DR = ch & 0xFF;
}

uint8_t uart2_read(void)
{
   /* make sure recv data reg not empty */
  while(!( USART2->SR & SR_RXNE) );

  /* read data*/
  return USART2->DR;
}

void uart_set_baudrate(USART_TypeDef *pUARTx, uint32_t PeriClk, uint32_t BaudRate)
{
   pUARTx->BRR = compute_uart_bd(PeriClk,BaudRate);
}

uint16_t compute_uart_bd(uint32_t PeriClk, uint32_t BaudRate)
{
   return ( (PeriClk + BaudRate/2U)/BaudRate );
}

