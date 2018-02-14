/* LCD Lib */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */


#include "stm32f10x.h"
#include "lcd.h"


/*
Originally written by Dave Duguid / Trevor Douglas
Taken from lab1_lib.c
*/
void delay(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}

void initLCDPorts(void)
{
	// Ensure port B is on for the control pins
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	// Ensure port C is on for the data pins
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	// RS
	GPIOB->CRL |= GPIO_CRL_MODE0;
  GPIOB->CRL &= ~GPIO_CRL_CNF0;
	
	// E
	GPIOB->CRL |= GPIO_CRL_MODE1;
  GPIOB->CRL &= ~GPIO_CRL_CNF1;
	
	// R/W
	GPIOB->CRL |= GPIO_CRL_MODE5;
  GPIOB->CRL &= ~GPIO_CRL_CNF5;
	
	// D0
	GPIOC->CRL |= GPIO_CRL_MODE0;
  GPIOC->CRL &= ~GPIO_CRL_CNF0;
	
	// D1
	GPIOC->CRL |= GPIO_CRL_MODE1;
  GPIOC->CRL &= ~GPIO_CRL_CNF1;
	
	// D2
	GPIOC->CRL |= GPIO_CRL_MODE2;
  GPIOC->CRL &= ~GPIO_CRL_CNF2;
	
	// D3
	GPIOC->CRL |= GPIO_CRL_MODE3;
  GPIOC->CRL &= ~GPIO_CRL_CNF3;
	
	// D4
	GPIOC->CRL |= GPIO_CRL_MODE4;
  GPIOC->CRL &= ~GPIO_CRL_CNF4;
	
	// D5
	GPIOC->CRL |= GPIO_CRL_MODE5;
  GPIOC->CRL &= ~GPIO_CRL_CNF5;
	
	// D6
	GPIOC->CRL |= GPIO_CRL_MODE6;
  GPIOC->CRL &= ~GPIO_CRL_CNF6;
	
	// D7
	GPIOC->CRL |= GPIO_CRL_MODE7;
  GPIOC->CRL &= ~GPIO_CRL_CNF7;
}

void initLCD(void)
{
	initLCDPorts(); // Set up ports
	delay(50000);
	
	cmdLCD(LCD_8B2L); // Wake up 1
	delay(32000);
	
	cmdLCD(LCD_8B2L); // Wake up 2
	delay(32000);
	
	cmdLCD(LCD_8B2L); // Wake up 3
	delay(32000);
	
	cmdLCD(LCD_8B2L); // Set up line count and font
	delay(32000);
	
	cmdLCD(LCD_DCB); // Set up display, cursor, and cursor blinking
	delay(32000);
	
	cmdLCD(LCD_CLR); // Clear the display and set cursor to 0,0
	delay(32000);
	
	cmdLCD(LCD_MCR); // Set cursor to move to the right after receiving data and disable shifting
	delay(32000);
}

void clearLCD()
{
	cmdLCD(LCD_CLR); // Clear the display and set cursor to 0,0
	delay(32000);
}

/*
Originally written by Dave Duguid / Trevor Douglas
Taken from 2018_Lab_3_GPIO_2_LCD_Display.pdf
*/
void cmdLCD(uint8_t data)
{
	GPIOB->BSRR = LCD_CM_ENA; //RS low, E high
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
	delay(80000);
}

/*
Originally written by Dave Duguid / Trevor Douglas
Modified by Shawn Clake to send ascii characters
Taken from 2018_Lab_3_GPIO_2_LCD_Display.pdf
*/
void dataLCD(uint8_t data)
{
	GPIOB->BSRR = LCD_DM_ENA; //RS high, E high
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(500); // was 8000  then 500
	GPIOB->BSRR = LCD_DM_DIS; //RS high, E low
	delay(500); // WAS 80000  then 500
}

void strLCD(char line[])
{
	int length = 16;
	int i;
	for(i = 0; i < length; i++)
	{
		dataLCD(line[i]);
	}
}

void strLCD(std::string line)
{
	for(int i = 0; i < line.size(); i++)
	{
		dataLCD(line[i]);
	}
}

void toLCD(LCDScreen screen)
{
	line1LCD();
	strLCD(screen.getLine1());
	line2LCD();
	strLCD(screen.getLine2());
}

void blankLineLCD(char line[])
{
	int i;
	for(i = 0; i < 16; i++)
	{
		line[i] = ' ';
	}
}

void gotoLineLCD(int i)
{
	if(i == 1)
		line1LCD();
	
	if(i == 2)
		line2LCD();
}

void line1LCD()
{
	cmdLCD(LCD_LN1); // Goto Line 1
	delay(32000);
}

void line2LCD()
{
	cmdLCD(LCD_LN2); // Goto Line 2
	delay(32000);
}