/*
 * PWM_Timer_Testing.c
 *
 *  Created on: Apr 1, 2024
 *      Author: ThanhPC
 */

#include "pwm.h"

int main(int argc, char **argv)
{
   /* Init PWM at PA0 PA1    */
   tim2_pa0_pa1_pwm_init();

   tim2_pa0_pa1_pwm_set_duty(1, 100);
   tim2_pa0_pa1_pwm_set_duty(2, 10);

   while(1);
}
