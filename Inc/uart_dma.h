/*
 * uart_dma.h
 *
 *  Created on: Mar 30, 2024
 *      Author: ThanhPC
 */

#ifndef UART_DMA_H_
#define UART_DMA_H_

#include <stdint.h>
#include "string.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define UART_BUFF_SIZE    5


/**************** USART2********** */
#define CR1_TE          (1U << 3)   // transmitter en
#define CR1_RE          (1U << 2)   // receiver en
#define CR1_UE          (1U << 13)  // uart en
#define CR1_RXNEIE      (1U << 5)
#define CR1_TXEIE       (1U << 7)
#define CR1_TCIE        (1U << 6)   // EN transmission cmplt IT

#define CR3_DMAT        (1U << 7)   // DMA enable transmitter
#define CR3_DMAR        (1U << 6)   // DMA enable receiver

#define SR_TXE          (1U << 7)
#define SR_RXNE         (1U << 5)
#define SR_TC           (1U << 6)

/***************** DMA ***************** */
#define DMA1EN        (1U << 21)

#define DMA_SCR_EN      (1U << 0)
#define SCR_CHSEL4      (4U << 25) // Channel selection 4
#define SCR_MINC        (1U << 10) // Memory increment
#define SCR_PINC        (1U << 9)   // Peripheral increment

#define SCR_CIRC       (1U << 8) // Circular enabled

#define SCR_DIR_PM     (0U << 6)  // 00: peripheral  to mem
#define SCR_DIR_MP     (1U << 6)  /* Data transfer direction
                                   01: Memory-to-peripheral */

#define SCR_TCIE    (1U << 4)  // Transfer complete interrupt enable

#define SCR_TEIE    (1U << 2)    /* Transfer error
                                   interrupt enable */
/* HISR: high interrupt status register */
#define HISR_TCIF5    (1U << 11)  // transfer
#define HISR_TCIF6    (1U << 21)  // complete
                                  // interrupt flag X
/* high interrupt flag clear register */
#define HIFCR_CTCIF5      (1U << 11)  /* clear transfer
                                 complete interrupt flag S5 */
#define HIFCR_CTCIF6      (1U << 21)  /* clear transfer
                                 complete interrupt flag S6 */

#define SFCR_DMDIS  (1U << 2)   // Direct mode disable



void uart_dma_rx_tx_init(void);
void dma1_init(void);
void uart_rx_dma1_stream5_config(void);
void uart_tx_dma1_stream6_config(uint32_t msg_to_tx, uint32_t msg_len);

void uart_dma_set_baudrate(USART_TypeDef *pUARTx, uint32_t PeriClk, uint32_t BaudRate);
uint16_t compute_uart_dma_bd(uint32_t PeriClk, uint32_t BaudRate);



#endif /* UART_DMA_H_ */
