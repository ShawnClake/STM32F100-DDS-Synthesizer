/* LCD Lib */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

#ifndef __LCD__
#define __LCD__

#include <stdint.h>
#include <string>

/*
 * Following define statements originally written by Dave Duguid
 * Taken from 2018_Lab_3_GPIO_2_LCD_Display.pdf
 */
//Commands for Hitachi 44780 compatible LCD controllers
#define LCD_8B2L 0x38 // ; Enable 8 bit data, 2 display lines
#define LCD_DCB 0x0F // ; Enable Display, Cursor, Blink
#define LCD_MCR 0x06 // ; Set Move Cursor Right
#define LCD_CLR 0x01 // ; Home and clear LCD
#define LCD_LN1 0x80 // ;Set DDRAM to start of line 1
#define LCD_LN2 0xC0 // ; Set DDRAM to start of line 2
// Control signal manipulation for LCDs on 352/384/387 board
// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 0x00210002 //
#define LCD_CM_DIS 0x00230000 //
#define LCD_DM_ENA 0x00200003 //
#define LCD_DM_DIS 0x00220001 //

#define LCD_LINE_LENGTH 16;

struct LCDScreen {
	std::string line1;
	std::string line2;
	
	LCDScreen()
	{
		
	}
	
	LCDScreen(std::string line1, std::string line2)
	{
		this->line1 = line1;
		this->line2 = line2;
	}
	
	
	
	std::string padEnd(std::string text)
	{
		
		char padded[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
		
		for(int i = 0; i < text.length(); i++)
		{
			padded[i] = text[i];
		}
		
		return padded;
	}
	
	std::string getLine1()
	{
		return padEnd(this->line1);
	}
	
	std::string getLine2()
	{
		return padEnd(this->line2);
	}
};

void delay(uint32_t count);

void initLCD(void);

void cmdLCD(uint8_t data);

void dataLCD(uint8_t data);

void strLCD(char line[]);
void strLCD(std::string line);
void toLCD(LCDScreen screen);

void clearLCD();

void blankLineLCD(char line[]);

void gotoLineLCD(int i);
void line1LCD();
void line2LCD();

#endif