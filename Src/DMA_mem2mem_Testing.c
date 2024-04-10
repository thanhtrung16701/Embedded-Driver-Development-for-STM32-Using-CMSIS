/*
 * EXTI_UART_RX_Testing.c
 *
 *  Created on: Mar 21, 2024
 *      Author: ThanhPC
 */

#include "uart.h"
#include "systick.h"
#include "timer.h"
#include "dma.h"


uint16_t sensor_data[BUFFER_SIZE] = { 887, 745, 1265, 98, 33 };

uint16_t temp_data[BUFFER_SIZE];

volatile uint8_t transfer_cmplt;

int main(int argc, char **argv)
{
   transfer_cmplt = 0;
   dma_mem2mem_config();
   uart2_tx_init();

   dma2_transfer_start((uint32_t) sensor_data, (uint32_t) temp_data, BUFFER_SIZE);

   /* wait till transfer cmplt    */
   while(!transfer_cmplt);

   for(int i = 0; i < BUFFER_SIZE; i++)
   {
      printf("Temp buffer [%d]: %d \n\r", i, temp_data[i]);

   }

   while(1);
}

void DMA2_Stream0_IRQHandler(void)
{
   if(DMA2->LISR & LISR_TCIF0)
   {
      transfer_cmplt = 1;
      DMA2->LIFCR |= LIFCR_CTCIF0;

   }
   /* check if trans error occurred   */
   if(DMA2->LISR & LISR_TEIF0)
   {
      /* Do something       */

      /* clear flag       */
      DMA2->LIFCR |= LIFCR_CTEIF0;
   }
}
