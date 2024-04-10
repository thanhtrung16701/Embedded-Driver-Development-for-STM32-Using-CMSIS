/*
 * systick.c
 *
 * *******  USING CORTEX M4 USER GUIDE  **********
 * *****  in SysTick Control and Status Register ****
 * **** ********** PAGE 250 *************
 */

#include "systick.h"




void systickDelayMs(int delay)
{
   /*Reload with number of clk per ms */
   SysTick->LOAD = SYSTICK_LOAD_VAL;

   /* Clear systick current value reg */
   SysTick->VAL = 0;

   /* EN systick and select internal clk src */
   SysTick->CTRL |= CTRL_ENABLE | CTRL_CLKSRC;

   for (int i = 0; i < delay; i++)
   {
      /*Wait till countflag set*/
      while( (SysTick->CTRL & CTRL_COUNTFLAG ) == 0); // while(! (...) )
   }
   SysTick->CTRL = 0;
}

void systick_1hz_it(void)
{
   /*Reload with number of clk per sec */
   SysTick->LOAD = ONE_SEC_LOAD - 1;

   /* Clear systick current value reg */
   SysTick->VAL = 0;

   /* EN systick and select internal clk src */
   SysTick->CTRL |= CTRL_ENABLE | CTRL_CLKSRC;

   /* En Systick IT    */
   SysTick->CTRL |= CTRL_TICKINT;
}
