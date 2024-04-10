/*
 * dma.c
 *
 *  Created on: Mar 25, 2024
 *      Author: ThanhPC
 */

#include "dma.h"


void dma_mem2mem_config(void)
{
  /* En clock access to dma module   */
   RCC->AHB1ENR |= DMA2EN;

   /* Disable dma stream    */
   DMA2_Stream0->CR &= SCR_EN;

   /* Wait till stream is disabled    */
   while(DMA2_Stream0->CR & SCR_EN);

   // Config DMA paras

   /* Set MSIZE to half-word    */
   DMA2_Stream0->CR |= 1U << 13;
   DMA2_Stream0->CR &= ~(1U << 14);

   /* Set PSIZE    */
   DMA2_Stream0->CR |= 1U << 11;
   DMA2_Stream0->CR &= ~(1U << 12);

   /* En memory increment    */
   DMA2_Stream0->CR |= SCR_MINC;

   /* En peripheral increment    */
   DMA2_Stream0->CR |= SCR_PINC;

   /* Select mem to mem transfer    */
   DMA2_Stream0->CR &= ~(1 << 6);
   DMA2_Stream0->CR |= 1 << 7;

   /* En transmit complete IT    */
   DMA2_Stream0->CR |= SCR_TCIE;

   /* En transmit error IT    */
   DMA2_Stream0->CR |= SCR_TEIE;

   /* Disable direct mode    */
   DMA2_Stream0->FCR |= SFCR_DMDIS;

   /* Set DMA FIFO threshold    */
   DMA2_Stream0->FCR |= (3U << 0);

    /* En DMA IT in NVIC    */
   NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

void dma2_transfer_start(uint32_t src_buf, uint32_t dst_buf, uint32_t len)
{
   /* Set peripheral - src addr   */
   DMA2_Stream0->PAR = src_buf;

   /* Set memory addr    */
   DMA2_Stream0->M0AR = dst_buf;

   /* Set transfer  length    */
   DMA2_Stream0->NDTR = len;

   /* En DMA stream    */
   DMA2_Stream0->CR |= SCR_EN;
}
