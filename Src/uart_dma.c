/*
 * uart_dma.c
 *
 *  Created on: Mar 30, 2024
 *      Author: ThanhPC
 */

#include "uart_dma.h"

#define GPIOAEN      (1U << 0)
#define UART2EN      (1U << 17)

#define SYS_FREQ      16000000
#define APB1_CLK      SYS_FREQ

#define UART_BAUDRATE   115200

uint8_t rx_cmplt = 0;
uint8_t tx_cmplt = 0;
uint8_t uart_cmplt = 0;
char uart_buffer_data[UART_BUFF_SIZE];

// MODER: 2 bits  PA3 -> MODE 3
//00: Input (reset state)
//01: General purpose output mode
//10: Alternate function mode
//11: Analog mode

//
// Alternate function low/ high 4 bit : PA2 -> AFRL2 // PA9 -> AFRH9

void uart_dma_rx_tx_init(void)
{
   /*********************** TX *************************
    1. EN clock access to gpioa */
   RCC->AHB1ENR |= GPIOAEN;

   /* 2. Set PA2 to ALT func mode, ALT func type to TX(AF7)  */
   GPIOA->MODER |= (2U << 2 * 2);

   GPIOA->AFR[0] |= (7U << 4 * 2);

   /******************************* RX ****************************/
   /* 3. Set PA3 to ALT func mode, ALT func type to TX(AF7)  */
   GPIOA->MODER |= (2U << 2 * 3);  // 2 bits

   GPIOA->AFR[0] |= (7U << 4 * 3);

   /** ******Config uart module**********
    4. EN clock access to uart2  **/
   RCC->APB1ENR |= UART2EN;

   /*5. Config baudrate */
   uart_dma_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

   /* 6. Use DMA for TX and RX   */
   USART2->CR3 |= CR3_DMAT | CR3_DMAR;

   /* 7. config transfer direction*/
   USART2->CR1 |= (CR1_TE | CR1_RE);

   /* 8. Clear transfer cmplt(TC) flag    */
   USART2->SR &= ~SR_TC;      // optional

   /* 9. Enable transfer cmplt IT (TCIE)    */
   USART2->CR1 |= CR1_TCIE;

   /* 10. Enable uart module */
   USART2->CR1 |= CR1_UE;

   /* 11. En UART IT in NVIC    */
   NVIC_EnableIRQ(USART2_IRQn);
}

void dma1_init(void)
{
   /* En clock access to  DMA    */
   RCC->AHB1ENR |= DMA1EN;

   /* En DMA Stream 6 IT in NVIC    */
   NVIC_EnableIRQ(DMA1_Stream6_IRQn);

   /*    */
}

// UART receive from peripheral and store it in mem -> peri to mem
void uart_rx_dma1_stream5_config(void)
{
   /* Disable DMA Stream    */
   DMA1_Stream5->CR &= DMA_SCR_EN;

   /* Wait till DMA Stream disabled   */
   while(DMA1_Stream5->CR & DMA_SCR_EN);

   /* Clear IT flag for stream 5    */
   DMA1->HIFCR |= (1U << 6 | 15U << 8);

   /* Set peripheral addr    */
   DMA1_Stream5->PAR = (uint32_t) &(USART2->DR);

   /* Set memory addr    */
   DMA1_Stream5->M0AR = (uint32_t) (&uart_buffer_data);

   /* Set number of transfer    */
   DMA1_Stream5->NDTR |= (uint16_t) UART_BUFF_SIZE;

   /* Select channel 4 - SCR 100   */
   DMA1_Stream5->CR = SCR_CHSEL4;

   /* En mem addr increment    */
   DMA1_Stream5->CR |= SCR_MINC;

   /* En transfer cmplt IT    */
   DMA1_Stream5->CR |= SCR_TCIE;

   /* En Circular mode    */
   DMA1_Stream5->CR |= SCR_CIRC;

   /* Set transfer direction: Peri to mem    */
//   DMA1_Stream5->CR &= ~(1U << 6| 1U << 7);
   DMA1_Stream5->CR |= SCR_DIR_PM;

   /* En DMA stream    */
   DMA1_Stream5->CR |= DMA_SCR_EN;

   /* En DMA stream 5 IT  in NVIC    */
   NVIC_EnableIRQ(DMA1_Stream5_IRQn);
}

void uart_tx_dma1_stream6_config(uint32_t msg_to_tx, uint32_t msg_len)
{
   /* Disable DMA Stream    */
   DMA1_Stream6->CR &= ~DMA_SCR_EN;   // optional

   /* Wait till DMA Stream disabled   */
   while(DMA1_Stream6->CR & DMA_SCR_EN);

   /* Clear IT flag for stream 6    */
   DMA1->HIFCR |= (1U << 16 | 15U << 18);

   /* Set peripheral addr    */
   DMA1_Stream6->PAR |= (uint32_t) &(USART2->DR);

   /* Set memory addr    */
   DMA1_Stream6->M0AR = msg_to_tx;

   /* Set number of transfer    */
   DMA1_Stream6->NDTR = msg_len;

   /* Select channel 4    */
   DMA1_Stream6->CR |= SCR_CHSEL4;

   /* En mem addr increment    */
   DMA1_Stream6->CR |= SCR_MINC;

   /* Set transfer direction: mem to peri    */
   DMA1_Stream6->CR |= SCR_DIR_MP;

   /* Set transfer cmplt IT    */
   DMA1_Stream6->CR |= SCR_TCIE;

   /* En DMA stream    */
   DMA1_Stream6->CR |= DMA_SCR_EN;
}

void DMA1_Stream5_IRQHandler(void)
{
   if(DMA1->HISR & HISR_TCIF5)
   {
      rx_cmplt = 1;
      // do something... (toggle led)
      // clear flag
      DMA1->HIFCR |= HIFCR_CTCIF5;
   }
}
void DMA1_Stream6_IRQHandler(void)
{
   if(DMA1->HISR & HISR_TCIF6)
   {
      // do something... (toggle led)
      tx_cmplt = 1;
      // clear flag
      DMA1->HIFCR |= HIFCR_CTCIF6;
   }
}

void USART2_IRQHandler(void)
{
   uart_cmplt = 1;
   /* clear TC flag    */
   USART2->SR &= ~SR_TC;
}

void uart_dma_set_baudrate(USART_TypeDef *pUARTx, uint32_t PeriClk, uint32_t BaudRate)
{
   pUARTx->BRR = compute_uart_dma_bd(PeriClk, BaudRate);
}

uint16_t compute_uart_dma_bd(uint32_t PeriClk, uint32_t BaudRate)
{
   return ((PeriClk + BaudRate / 2U) / BaudRate);
}

