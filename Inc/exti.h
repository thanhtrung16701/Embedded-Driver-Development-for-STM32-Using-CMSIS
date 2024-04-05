/*
 * exti.h
 *
 *  Created on: Mar 21, 2024
 *      Author: ThanhPC
 */

#ifndef EXTI_H_
#define EXTI_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f407xx.h"

void pa0_exti_init();
#define LINE0  (1U << 0)

#endif /* EXTI_H_ */
