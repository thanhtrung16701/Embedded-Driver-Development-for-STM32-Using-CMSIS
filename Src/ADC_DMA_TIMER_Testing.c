/*
 * ADC_DMA_Testing.c
 *
 *  Created on: Mar 26, 2024
 *      Author: ThanhPC
 */

#include "adc_dma.h"
#include "uart.h"
#include "systick.h"
#include "swo.h"

extern uint16_t adc_raw_data[NUM_OF_SAMPLES];

volatile uint8_t transfer_cmplt;

int main(int argc, char **argv)
{
   transfer_cmplt = 0;
   uart2_tx_init();
   adc_tim_dma_init();

   while(1)
   {
      if (transfer_cmplt)
      {
//         transfer_cmplt = 0;
         for(int i = 0; i < NUM_OF_SAMPLES; i++)
         {
            printf("Sample number [%d] = %d \n\r", i, adc_raw_data[i]);
         }
         systickDelayMs(500);
      }
   }
}

void DMA2_Stream0_IRQHandler(void)
{
   /* check if transfer cmplt IT occurred    */
   if(DMA2->LISR & LISR_TCIF0)
   {
      transfer_cmplt = 1;

      /* Clear flag       */
      DMA2->LIFCR |= LIFCR_CTCIF0;
   }

}
