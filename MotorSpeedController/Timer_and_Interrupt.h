/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Description: Header file for the ADC driver
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#ifndef TIMER_AND_INTERRUPT_H_
#define TIMER_AND_INTERRUPT_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

extern volatile uint8 flag;

void Timer0_Fast_PWM(uint16 number);
void INT1_Init(void);


#endif /* TIMER_AND_INTERRUPT_H_ */
