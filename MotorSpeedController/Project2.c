/******************************************************************************
 *
 * Module: Project2
 *
 * File Name: Project2.c
 *
 * Description: Main file
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#include"LCD.h"
#include"ADC.h"
#include "Timer_and_Interrupt.h"

volatile uint16 result;

int main()
{
	LCD_init();
	ADC_init();
	LCD_clearScreen();
	LCD_displayString("Project 2");
	_delay_ms(1500);
	LCD_clearScreen();
	LCD_displayString("ADC Value = ");
	DDRB |= (1<<PB3);
	DDRB |= 0x03;
	INT1_Init();

	while(1)
	{
		LCD_goToRowColumn(0,12);
		ADC_read_channel(0);
		result = adc;
		LCD_integertostring(result);
		Timer0_Fast_PWM(result/4);
		if (flag == 0 )
		{
			// Rotate the motor --> clock wise
			PORTB &= (~(1<<PB0));
			PORTB |= (1<<PB1);
		}
		else if(flag == 1)
		{
			// Rotate the motor --> anti-clock wise
			PORTB |= (1<<PB0);
			PORTB &= (~(1<<PB1));
		}
	}
}
