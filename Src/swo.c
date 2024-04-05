/*
 * swo.c
 *
 *  Created on: Mar 25, 2024
 *      Author: ThanhPC
 */

#include "swo.h"

int __io_putchar(int ch)
{
   ITM_SendChar(ch);
   uart2_write(ch);
   return ch;
}

