/******************************************************************************
 *
 * Module: Timer_and_Interrupt
 *
 * File Name: Timer_and_Interrupt.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#include "Timer_and_Interrupt.h"
volatile uint8 flag = 0;

Timer0_Fast_PWM(uint16 number)
{
	SREG |= (1<<7);
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
	DDRB |= (1<<PB3);
	OCR0 = number;
	TCNT0 = 0;
}

ISR(INT1_vect)
{
	if (flag == 0)
	{
		flag = 1;
	}
	else if (flag == 1 )
	{
		flag = 0;
	}
}

void INT1_Init(void)
{
	SREG &=~ (1<<7);
	DDRD  &= (~(1<<PD3));
	GICR = (1<<INT1);
	MCUCR = (1<<ISC10) | (1<<ISC11);
	SREG |= (1<<7);

}
