/*
 * adc_dma.c
 *
 *  Created on: Mar 26, 2024
 *      Author: ThanhPC
 */

#include "adc_dma.h"

uint16_t adc_raw_data[NUM_OF_SAMPLES];

void adc_dma_init(void)
{
   //************* GPIO config ***********
   /* En clock access to ADC GPIO  */
   RCC->AHB1ENR |= GPIOAEN;

   /* Set PA1 and PA0 mode to analog mode - 11  */
   GPIOA->MODER |= 3U << 2 * 0;
   GPIOA->MODER |= 3U << 2 * 1;

   //************ ADC Config ***************
   /* en clock access to ADC    */
   RCC->APB2ENR |= ADC1EN;

   /* Set sequence length - 4bit -> 2 conversions  */
   ADC1->SQR1 |= 1U << 20;
   ADC1->SQR1 &= ~(1U << 21);
   ADC1->SQR1 &= ~(1U << 22);
   ADC1->SQR1 &= ~(1U << 23);

   /* Set sequence : 2 channel -  5 bit  */
   ADC1->SQR3 |= (0U << 0) | (1U << 5);

   /* En scan mode    */
   ADC1->CR1 |= CR1_SCAN;

   /* Select to use DMA    */
   ADC1->CR2 |= CR2_CONT | CR2_DMA | CR2_DDS;

   //************* DMA Config ****************
   /* Enable clock access to DMA    */
   RCC->AHB1ENR |= DMA2EN;

   /* Disable DMA    */
   DMA2_Stream0->CR &= ~SCR_EN;

   /* Wai till DMA is disabled    */
   while(DMA2_Stream0->CR & SCR_EN);

   /* En circular mode    */
   DMA2_Stream0->CR |= SCR_CIRC;

   /* Set mem transfer size    */
   DMA2_Stream0->CR |= 1U << 13;
   DMA2_Stream0->CR &= ~(1U << 14);

   /* Set peripheral transfer size    */
   DMA2_Stream0->CR |= 1U << 11;
   DMA2_Stream0->CR &= ~(1U << 12);

   /* En memory increment   */
   DMA2_Stream0->CR |= SCR_MINC;

   /* Set peripheral addr - destination   */
   DMA2_Stream0->PAR |= (uint32_t) &(ADC1->DR);

   /* Set mem addr    */
   DMA2_Stream0->M0AR |= (uint32_t) &adc_raw_data;

   /* Set number of transfer - length   */
   DMA2_Stream0->NDTR |= (uint16_t) NUM_OF_CHANNELS;

   /* Enable DMA stream    */
   DMA2_Stream0->CR |= SCR_EN;

   //************ ADC Config ***************
   /* En ADC    */
   ADC1->CR2 |= CR2_ADON;

   /* Start ADC    */
   ADC1->CR2 |= CR2_SWSTART;
}

void adc_tim_dma_init(void)
{
   //************* GPIO config ***********
   /* En clock access to ADC GPIO  */
   RCC->AHB1ENR |= GPIOAEN;

   /* Set  PA0 mode to analog mode - 11  */
   GPIOA->MODER |= 3U << 2 * 0;

   //************ ADC Config ***************
   /* en clock access to ADC    */
   RCC->APB2ENR |= ADC1EN;

   /* Select to use DMA    */
   ADC1->CR2 |= CR2_DMA | CR2_DDS;

   /* Select external on rising edge - 01 - bit 28,29   */
   ADC1->CR2 |= 1U << 28;

   /* Select timer 2  TRGO event- 0110  */
   ADC1->CR2 |= 6U << 24;

   //************* DMA Config ****************
   /* Enable clock access to DMA    */
   RCC->AHB1ENR |= DMA2EN;

   /* Disable DMA    */
   DMA2_Stream0->CR &= ~SCR_EN;

   /* Wai till DMA is disabled    */
   while(DMA2_Stream0->CR & SCR_EN);

   /* En circular mode    */
   DMA2_Stream0->CR |= SCR_CIRC;

   /* Set peripheral data size    */
   DMA2_Stream0->CR |= 1U << 13;
   DMA2_Stream0->CR &= ~(1U << 14);

   /* Set mem size to  half word - 01  */
   DMA2_Stream0->CR |= 1U << 11;
   DMA2_Stream0->CR &= ~(1U << 12);

   /* En memory increment   */
   DMA2_Stream0->CR |= SCR_MINC;

   /* Enable transfer complete IT    */
   DMA2_Stream0->CR |= SCR_TCIE;

   /* Set peripheral addr - destination   */
   DMA2_Stream0->PAR |= (uint32_t) &(ADC1->DR);

   /* Set mem addr    */
   DMA2_Stream0->M0AR |= (uint32_t) &adc_raw_data;

   /* Set number of transfer - length   */
   DMA2_Stream0->NDTR |= (uint16_t)NUM_OF_SAMPLES;

   /* En DMA IT in NVIC    */
   NVIC_EnableIRQ(DMA2_Stream0_IRQn);


   //************ Timer Config  ***************
   /* Config timer period to 100 Hz rate, ADC sampling at this every 10 ms    */
   /* En clock access to TIM2    */
   RCC->APB1ENR |= TIM2EN;

   /* Set TIM prescaler value    */
   TIM2->PSC = 16000 - 1; // 16 000 000 / 1600 = 1 000

   /* Set TIM auto reload value    */
   TIM2->ARR = 10 - 1;   // 1000 / 10 = 100 Hz

   /* Config master mode bits- 010: Update EVE  */
   /*  selected as trigger output (TRGO) bit 4,5,6 -CR2
    a master be used as a prescaler for a slave timer    */
   TIM2->CR2 |= (2U << 4);

   //************ Enable modules ***************
   /* En ADC    */
   ADC1->CR2 |= CR2_ADON;

   /* Enable DMA stream    */
   DMA2_Stream0->CR |= SCR_EN;

   /* Enable timer 2    */
   TIM2->CR1 |= CR1_CEN;
}

















