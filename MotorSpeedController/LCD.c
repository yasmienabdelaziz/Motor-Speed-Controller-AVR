/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#include"LCD.h"

void LCD_init()
{
	LCD_CTRL_DIR = (1<<Rs) | (1<<RW) | (1<<E);
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_DIR = 0xF0;
#else
	LCD_DATA_DIR = 0x0F;
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_DIR = 0xFF;
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* 2 lines + 8bit mode */
#endif
	LCD_sendCommand(CURSOR_OFF); /* Cursor_OFF */
	LCD_sendCommand(CLEAR_COMMAND); /* Clear screen */
}

void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,Rs);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_us(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif

	_delay_us(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);

#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif

	_delay_us(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);

#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = 0xFF;
	_delay_us(1);
	LCD_DATA_PORT = command;
	_delay_us(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
#endif

}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,Rs);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_us(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0xF0);
#endif
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = data;
#endif
	_delay_us(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_us(1);
}

void LCD_displayString(const char * str)
{
	uint8 i = 0;
	while( str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}

void LCD_goToRowColumn(uint8 row, uint8 col)
{
	uint8 address;
	switch(row)
	{
		case 0 : address = col;
		break;
		case 1 : address = col + 0x40;
		break;
		case 2 : address = col + 0x10;
		break;
		case 3 : address = col + 0x05;
		break;
	}
	LCD_sendCommand(address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_integertostring(int data)
{
	uint8 buffer[16];
	itoa(data,buffer,10);
	LCD_displayString(buffer);
}
void LCD_clearScreen()
{
	LCD_sendCommand(CLEAR_COMMAND);
}
