/*
 * adc.c
 *
 *  Created on: Mar 18, 2024
 *      Author: ThanhPC
 */

#include "adc.h"
#include "stm32f4xx.h"



void PA1_adc_init(void)
{
   /* Config the ADC GPIO PA1 pin */

   /* En clk access to GPIOA*/
   RCC->AHB1ENR |= GPIOAEN;
   /* Set mode of PA1 to analog */
   GPIOA->MODER |= (3U << 2*1);


   // Config the ADC module
   /* EN clk access to ADC  */
   RCC->APB2ENR |= ADC1EN;

   /* Enable ADC end of conversion it */
   ADC1->CR1 |= CR1_EOCIE;

   /* conversion sequence start */
   ADC1->SQR3 |= ADC_CH1;

   /* conversion sequence length */
   ADC1->SQR1 |= ADC_SEQ_LEN_1;

   /* EN ADC module */
   ADC1->CR2 |= CR2_ADCON;
}



void PA1_adc_it_init(void)
{
   /* Config the ADC GPIO PA1 pin */


   /* En clk access to GPIOA*/
   RCC->AHB1ENR |= GPIOAEN;
   /* Set mode of PA1 to analog */
   GPIOA->MODER |= (3U << 2*1);


   /* Config the ADC module */

   /* EN clk access to ADC  */
   RCC->APB2ENR |= ADC1EN;
   /* Config ADC para */

   /* En ADC end of conversion IT    */
   ADC1->CR1 |= CR1_EOCIE;

   /* En ADC it in NVIC    */
   NVIC_EnableIRQ(ADC_IRQn);

   /* conversion sequence start */
   ADC1->SQR3 |= ADC_CH1;

   /* conversion sequence length */
   ADC1->SQR1 |= ADC_SEQ_LEN_1;

   /* EN ADC module */
   ADC1->CR2 |= CR2_ADCON;
}

void start_conversion(void)
{
   /*EN continous conversion  */
   ADC1->CR2 |= CR1_CONT;
   /* start conversion*/
   ADC1->CR2 |= CR2_SWSTART;
}
uint32_t adc_read(void)
{
   /*Wait for conversion to be complete */
   while(! (ADC1->SR & SR_EOC) );

   /* Read converted result */
   return ADC1->DR;
}

