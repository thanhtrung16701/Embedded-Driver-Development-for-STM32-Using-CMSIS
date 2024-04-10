

#include "pwm_dma.h"

/*
DMA1_Stream5_channel 3 : TIM2_CH1
DMA1_Stream6_channel 3 : TIM2_CH2
PA0  - TIM2_CH1
PA1  - TIM2_CH2
*/

#define LOOKUP_TABLE_LEN    200
uint32_t ch1_duty_lookup[LOOKUP_TABLE_LEN]=
{
      0, 50, 100, 151, 201, 250, 300, 349, 398, 446, 494, 542, 589, 635, 681
     ,726, 771, 814, 857, 899, 940, 981, 1020, 1058, 1095, 1131, 1166, 1200, 1233, 1264
     ,1294, 1323, 1351, 1377, 1402, 1426, 1448, 1468, 1488, 1505, 1522, 1536, 1550, 1561
     ,1572, 1580, 1587, 1593, 1597, 1599, 1600, 1599, 1597, 1593, 1587, 1580, 1572, 1561
     ,1550, 1536, 1522, 1505, 1488, 1468, 1448, 1426, 1402, 1377, 1351, 1323, 1294, 1264
     ,1233, 1200, 1166, 1131, 1095, 1058, 1020, 981, 940, 899, 857, 814, 771, 726, 681, 635
     ,589, 542, 494, 446, 398, 349, 300, 250, 201, 151, 100, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
     ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
     ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0
};
uint32_t ch2_duty_lookup[LOOKUP_TABLE_LEN]=
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 100, 151, 201, 250, 300, 349, 398, 446, 494
   , 542, 589, 635, 681, 726, 771, 814, 857, 899, 940, 981, 1020, 1058, 1095, 1131, 1166, 1200, 1233
   , 1264, 1294, 1323, 1351, 1377, 1402, 1426, 1448, 1468, 1488, 1505, 1522, 1536, 1550, 1561, 1572, 1580
   , 1587, 1593, 1597, 1599, 1600, 1599, 1597, 1593, 1587, 1580, 1572, 1561, 1550, 1536, 1522, 1505, 1488
   , 1468, 1448, 1426, 1402, 1377,  1351, 1323, 1294, 1264, 1233, 1200, 1166, 1131, 1095, 1058, 1020, 981
};

void tim2_pa0_pa1_pwm_dma_init(void)
{
   /************* GPIO Config **************    */
   /* En clock access to GPIOA    */
   RCC->AHB1ENR |= GPIOAEN;

   /* Set PA0 and PA1 to ALT mode - 10 - 2 bit   */
   GPIOA->MODER |= 2U << 2*0;
   GPIOA->MODER |= 2U << 2*1;

   /* ALT type - TIM2 (AF1 - 01 - 4 bit)    */
   GPIOA->AFR[0] |= 1U << 4*0;
   GPIOA->AFR[0] |= 1U << 4*1;

   /************* TIM2 Config *********    */
   /* En clock access to TIM2    */
   RCC->APB1ENR |= TIM2EN;

   /* Set timer prescaler    */
   TIM2->PSC |= 0;   // 16 000 000 / 10 = 1 600 000

   /* Set auto-reload value    */
   TIM2->ARR |= 1600 - 1; // 16 000 000/ 1600 = 10 KHz

   /* Reset timer count    */
   TIM2->CNT = 0;

   /* Set PA1- CH2 and PA0 - CH1 to 110: PWM mode 1  */
   /*ch1 - bit 4:6  */
   TIM2->CCMR1 |= 6U << 4;

   /* CH2 bit 12:14  */
   TIM2->CCMR1 |= 6U << 12;

   /* En CH1 and CH2-Capture/Compare output    */
   TIM2->CCER |= CCER_CC1E | CCER_CC2E;

   /* En DMA IT CH1 and CH2, update DMA and trigger DMA request    */
   TIM2->DIER |= DIER_CC1DE | DIER_CC2DE| DIER_UDE | DIER_TDE;

   /* En timer    */
   TIM2->CR1 |= CR1_CEN;

   /***************** Config DMA *********    */
   /************** Stream 5 *************** */

   /* En clock access to DMA    */
   RCC->AHB1ENR |= DMA1EN;

   /* Disable DMA Stream    */
   DMA1_Stream5->CR = 0;

   /* Wait till DMA Stream is disabled    */
   while(! (DMA1_Stream5->CR & SCR_EN));

   /* Select DMA channel 3      */
   DMA1_Stream5->CR |= SCR_CHSEL3;

   /* En  circular mode    */
   DMA1_Stream5->CR |= SCR_CIRC;

   /* En mem addr increment    */
   DMA1_Stream5->CR |= SCR_MINC;

   /* Set mem size : 10: word (32-bit) */
   DMA1_Stream5->CR |= SCR_MSIZE32;

   /* Set peripheral size : 32 bit - 10  */
   DMA1_Stream5->CR |= SCR_PSIZE32;

   /* transfer direction: mem to peri - taking value store in array -> timer duty cycle   */
   DMA1_Stream5->CR |= SCR_DIR_M2P;

   /* Config number of transfer    */
   DMA1_Stream5->NDTR |= (uint16_t)LOOKUP_TABLE_LEN;

   /* Config peri addr     */
   DMA1_Stream5->PAR |= (uint32_t)&(TIM2->CCR1);

   /* Config mem addr     */
   DMA1_Stream6->M0AR |= (uint32_t)(&ch1_duty_lookup);

   /* Enable DMA stream    */
   DMA1_Stream5->CR |= SCR_EN;

   /************** Stream 6 *************** */

   /* Disable DMA Stream    */

   /* Wait till DMA Stream is disabled    */

   /* Select DMA channel 3      */

   /* En  circular mode    */

   /* En mem addr increment    */

   /* Set mem size : 10: word (32-bit) */

   /* Set peripheral size : 32 bit - 10  */

   /* transfer direction: mem to peri - taking value store in array -> timer duty cycle   */

   /* Config number of transfer    */

   /* Config peri addr     */

   /* Config mem addr     */

   /* Enable DMA stream    */

}

void tim2_pa0_pa1_pwm_dma_set_duty(uint8_t ch, uint32_t duty)
{
   /* Select channel    */
   switch (ch) {
      /* Set duty cycle    */
      case 1:
         TIM2->CCR1 = duty; // CH1
         break;
      case 2:
         TIM2->CCR2 = duty; // CH2
      default:
         break;
   }
}





