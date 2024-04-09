/*
 * adc_test.c
 *
 *  Created on: Mar 18, 2024
 *      Author: ThanhPC
 */

#include "adc.h"
#include "uart.h"

uint32_t sensor_value;

int main(int argc, char **argv) {
   uart2_txrx_init();
   PA1_adc_init();
   while(1)
   {
      start_conversion();
      sensor_value = adc_read();
      printf("Sensor value: %d \n\r",(int)sensor_value);
   }
}

