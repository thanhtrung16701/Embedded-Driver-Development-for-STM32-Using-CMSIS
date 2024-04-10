/*
 * Systick.h
 *
 * *******  USING CORTEX M4 USER GUIDE  **********
 * *****  in SysTick Control and Status Register ****
 * ****************** PAGE 250 *************
 *
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

#define SYSTICK_LOAD_VAL     16000  // ngưỡng giá trị đếm ms
#define ONE_SEC_LOAD       16000000
#define CTRL_ENABLE     (1U << 0)


#define CTRL_CLKSRC     (1U << 2)   /*Indicates the clock source:
                                    0 = external clock
                                    1 = processor clock */

#define CTRL_COUNTFLAG  (1U << 16)  /* Returns 1 if timer counted to
                                    0 since last time this was read */

#define CTRL_TICKINT    (1U << 1)   /*Enables SysTick
                                    exception request  */


void systickDelayMs(int delay);
void systick_1hz_it(void);


#endif /* SYSTICK_H_ */
