/*
 * adc_continous_conversion.c
 *
 *  Created on: Mar 18, 2024
 *      Author: ThanhPC
 *      kết nối PA1 với GND giá trị sensor value = 0 còn vs 3.3V thì gt = 4095
 *      vì bộ ADC có resolution là 12 bit
 */


#include "adc.h"
#include "systick.h"
#include "uart.h"

uint32_t sensor_value;

static void adc_callback(void);


int main(int argc, char **argv) {

   uart2_tx_init();
   PA1_adc_it_init();
   start_conversion();
   while(1);
}

static void adc_callback(void)
{
   sensor_value = ADC1->DR;
   printf("Sensor value: %d \n\r",(int)sensor_value);
   systickDelayMs(500);

}
void ADC_IRQHandler(void)
{
   /* Check for EOC in SR    */
   if (ADC1->SR & SR_EOC) {
      /* clear EOC       */
      ADC1->SR &= ~SR_EOC;

      // Do something
    adc_callback();

   }
}
