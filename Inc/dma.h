/*
 * dma.h
 *
 *  Created on: Mar 25, 2024
 *      Author: ThanhPC
 */

#ifndef DMA_H_
#define DMA_H_

#include "uart.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define DMA2EN        (1U << 22)
#define SCR_EN    (1U << 0)
#define SCR_MINC  (1U << 10)   // Memory increment

#define SCR_PINC  (1U << 9)   // Peripheral increment

#define SCR_TCIE  (1U << 4)   /* Transfer complete
                                    interrupt enable */

#define SCR_TEIE  (1U << 2)   /* Transfer error
                               interrupt enable */

#define SFCR_DMDIS  (1U << 2)   // Direct mode disable

#define LISR_TCIF0    (1U << 5)     /* Stream x transfer
                                       complete interrupt flag */

#define LISR_TEIF0      (1U << 3) /* transfer error
                                       interrupt flag */

#define LIFCR_CTCIF0     (1U << 5)  /* clear transfer complete
                                    interrupt flag */

#define LIFCR_CTEIF0     (1U << 3) /* clear transfer
                                    error interrupt flag */
void dma_mem2mem_config(void);

void dma2_transfer_start(uint32_t src_buf, uint32_t dst_buf, uint32_t len);

#endif /* DMA_H_ */
