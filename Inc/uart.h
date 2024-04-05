

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

/**************** USART2********** */
#define CR1_TE          (1U << 3)   // transmitter en
#define CR1_RE          (1U << 2)   // receiver en
#define CR1_UE          (1U << 13)  // uart en
#define CR1_RXNEIE      (1U << 5)
#define CR1_TXEIE       (1U << 7)

#define CR3_DMAT        (1U << 7)   // DMA enable transmitter

#define SR_TXE          (1U << 7)
#define SR_RXNE          (1U << 5)

/***************** DMA ***************** */
#define DMA1EN        (1U << 21)

#define DMA_SCR_EN      (1U << 0)
#define SCR_CHSEL4      (4U << 25)  // Channel selection
#define SCR_MINC        (1U << 10) // Memory increment mode

#define SCR_DIR_MP     (1U << 6)  /* Data transfer direction
                                   01: Memory-to-peripheral */
#define SCR_TCIE       (1U << 4)  // Transfer complete interrupt enable

#define HISR_TCIF6        (1U << 21)  /* transfer complete
                                       interrupt flag S6 */

#define HIFCR_CTCIF6      (1U << 21)  /* clear transfer
                                 complete interrupt flag S6 */


void uart_set_baudrate(USART_TypeDef *pUARTx, uint32_t PeriClk, uint32_t BaudRate);
uint16_t compute_uart_bd(uint32_t PeriClk, uint32_t BaudRate);


void uart2_tx_init(void);
void uart2_rx_init(void);
void uart2_txrx_init(void);
void uart2_tx_it_init(void);
void uart2_rx_it_init(void);
void dma1_sream6_init(uint32_t src, uint32_t dst, uint32_t len);

void uart2_write(int ch);
uint8_t uart2_read(void);



#endif /* UART_H_ */
