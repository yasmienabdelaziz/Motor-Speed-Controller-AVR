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


#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

extern volatile uint32 adc;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


void ADC_init(void);
void ADC_read_channel(uint8 ch_num);


#endif /* ADC_H_ */
