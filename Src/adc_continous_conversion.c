/*
 * adc_continous_conversion.c
 *
 *  Created on: Mar 18, 2024
 *      Author: ThanhPC
 *      kết nối PA1 với GND giá trị sensor value = 0 còn vs 3.3V thì gt = 4095
 *      vì bộ ADC có resolution là 12 bit
 */


#include "adc.h"
#include "uart.h"

uint32_t sensor_value;

int main(int argc, char **argv) {
   uart2_txrx_init();
   PA1_adc_init();
   start_conversion();

   while(1)
   {
      delay();
      sensor_value = adc_read();
      printf("Sensor value: %d \n\r",(int)sensor_value);
   }
}
