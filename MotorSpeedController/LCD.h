/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Yasmien Abdelaziz
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif


/* LCD HW PINS */

#define LCD_DATA_PORT PORTC
#define LCD_DATA_DIR DDRC

#define Rs PD0
#define RW PD1
#define E PD2
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_DIR DDRD

/* LCD Commands */

#define CLEAR_COMMAND 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28
#define CURSOR_OFF 0x0C
#define SET_CURSOR_LOCATION 0x80


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char * str);
void LCD_goToRowColumn(uint8 row, uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_integertostring(int data);
void LCD_clearScreen();

#endif /* LCD_H_ */
