/*
 * ADC_DMA_Testing.c
 *
 *  Created on: Mar 26, 2024
 *      Author: ThanhPC
 */

#include "adc_dma.h"
#include "uart.h"
#include "systick.h"

extern uint16_t adc_raw_data[NUM_OF_CHANNELS];

int main(int argc, char **argv) {

   uart2_tx_init();
   adc_dma_init();

   while(1)
   {
      printf("Value from sensor 1: %d\n",adc_raw_data[0]);
      printf("Value from sensor 2: %d\n",adc_raw_data[1]);
      systickDelayMs(500);
   }
}
