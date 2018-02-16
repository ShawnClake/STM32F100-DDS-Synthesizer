/* IO Lib */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

#include "stm32f10x.h"
#include "io.h"

void initPortClocks(void)
{
	initPortAClock();
	initPortBClock();
	initPortCClock();
}

void initPortAClock(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
}

void initPortBClock(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
}

void initPortCClock(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

/**
Because the inputs are set like this by default, this is NOT needed
*/
void initSwitchConfigs(void)
{
	// Switch 1.1
	GPIOA->CRL |= GPIO_CRL_MODE6 | GPIO_CRL_CNF6_0;
	
	// Switch 1.2
	GPIOA->CRL |= GPIO_CRL_MODE7 | GPIO_CRL_CNF7_0;
	
	// Switch 1.3
	GPIOC->CRH |= GPIO_CRH_MODE10 | GPIO_CRH_CNF10_0;
	
	// Switch 1.4
	GPIOC->CRH |= GPIO_CRH_MODE11 | GPIO_CRH_CNF11_0;
	
	// Switch 2
	GPIOB->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_0;
	
	// Switch 3
	GPIOB->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_0;
	
	// Switch 4
	GPIOC->CRH |= GPIO_CRH_MODE12 | GPIO_CRH_CNF12_0;
	
	// Switch 5
	GPIOA->CRL |= GPIO_CRL_MODE5 | GPIO_CRL_CNF5_0;
}

void initLEDConfigs(void)
{
	// LED 1
	GPIOA->CRH |= GPIO_CRH_MODE9;
  GPIOA->CRH &= ~GPIO_CRH_CNF9;
	
	// LED 2
	GPIOA->CRH |= GPIO_CRH_MODE10;
  GPIOA->CRH &= ~GPIO_CRH_CNF10;
	
	// LED 3
	GPIOA->CRH |= GPIO_CRH_MODE11;
  GPIOA->CRH &= ~GPIO_CRH_CNF11;
	
	// LED 4
	GPIOA->CRH |= GPIO_CRH_MODE12;
  GPIOA->CRH &= ~GPIO_CRH_CNF12;
	
	GPIOC->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE8 ;
  GPIOC->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF8 ;
}

uint8_t readSwitches(void)
{
	uint8_t reads = 0;
	
	if(GPIOA->IDR & GPIO_IDR_IDR6)
		reads |= 1;
	if(GPIOA->IDR & GPIO_IDR_IDR7)
		reads |= 2;
	if(GPIOC->IDR & GPIO_IDR_IDR10)
		reads |= 4;
	if(GPIOC->IDR & GPIO_IDR_IDR11)
		reads |= 8;
	if(GPIOB->IDR & GPIO_IDR_IDR8)
		reads |= 16;
	if(GPIOB->IDR & GPIO_IDR_IDR9)
		reads |= 32;
	if(GPIOC->IDR & GPIO_IDR_IDR12)
		reads |= 64;
	if(GPIOA->IDR & GPIO_IDR_IDR5)
		reads |= 128;
	
	/*reads = ~( 
		(GPIOA->IDR & (GPIO_IDR_IDR6 | GPIO_IDR_IDR7)) >> 6 
		| (GPIOC->IDR & (GPIO_IDR_IDR10 | GPIO_IDR_IDR11)) >> 8
		| (GPIOB->IDR & (GPIO_IDR_IDR8 | GPIO_IDR_IDR9)) >> 4
		| (GPIOC->IDR & (GPIO_IDR_IDR12)) >> 6
		| (GPIOA->IDR & (GPIO_IDR_IDR5)) << 2
	);*/
	return ~reads;
}

void setLEDs(uint8_t leds)
{
	// might need to invert LEDs
	
	// Mask ODR
	if(leds & 1)
		GPIOA->BSRR = GPIO_BSRR_BR9;
	else
		GPIOA->BSRR = GPIO_BSRR_BS9;
	
	if(leds & 2)
		GPIOA->BSRR = GPIO_BSRR_BR10;
	else
		GPIOA->BSRR = GPIO_BSRR_BS10;
	
	if(leds & 4)
		GPIOA->BSRR = GPIO_BSRR_BR11;
	else
		GPIOA->BSRR = GPIO_BSRR_BS11;
	
	if(leds & 8)
		GPIOA->BSRR = GPIO_BSRR_BR12;
	else
		GPIOA->BSRR = GPIO_BSRR_BS12;
}