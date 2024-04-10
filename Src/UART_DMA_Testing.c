/*
 * UART2_DMA_Testing.c
 *
 *  Created on: Mar 31, 2024
 *      Author: ThanhPC
 */

#include "uart_dma.h"

extern uint8_t rx_cmplt;
extern uint8_t tx_cmplt;
extern uint8_t uart_cmplt;
extern char uart_buffer_data[UART_BUFF_SIZE];

char msg[50] = { '\0' };

int main(int argc, char **argv)
{
   uart_dma_rx_tx_init();
   dma1_init();
   uart_rx_dma1_stream5_config();
   sprintf(msg, "Initialization ... complete \n\r");

   uart_tx_dma1_stream6_config((uint32_t) msg, strlen(msg));

   while(!tx_cmplt);  // tx not set

   while(1)
   {
      if(rx_cmplt)
      {   // reception complete
         sprintf(msg, "Message received: %s \n\r", uart_buffer_data);
         rx_cmplt = 0;
         tx_cmplt = 0;
         uart_cmplt = 0;
         uart_tx_dma1_stream6_config((uint32_t) msg, strlen(msg));
         while(!tx_cmplt);    // wait to receive again
      }
   }
}
