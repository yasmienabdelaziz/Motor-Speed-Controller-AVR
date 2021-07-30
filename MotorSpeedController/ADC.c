/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#include "ADC.h"

volatile uint32 adc = 0;

ISR(ADC_vect)
{
	adc = ADC;
}

void ADC_init(void)
{
	ADMUX = 0;
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);
}

void ADC_read_channel(uint8 ch_num)
{
	SREG |= (1<<7);
	ch_num &= 0x07; // clear last five bits
	ADMUX &= 0xE0; //clear first five bits
	ADMUX =  ADMUX | ch_num;
	SET_BIT(ADCSRA,ADSC);
}
