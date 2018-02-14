/* ADC Lib */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "adc.h"

void delayADC(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}

void initADCPorts(void)
{
	// Is ADC port on?
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	
	// Ensure port A clocks are on
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	//GPIOA->CRL |= GPIO_CRL_MODE1;
  GPIOA->CRL &= ~GPIO_CRL_CNF1;
	
	//GPIOA->CRL |= GPIO_CRL_MODE0;
  GPIOA->CRL &= ~GPIO_CRL_CNF2;
}

void initADC(void)
{
	initADCPorts();
	
	// sets ADON and CAL
	ADC1->CR2 |= 5;
	
	// sets up channel 1
	ADC1->SMPR2 |= 56; // 8, 16, 32 - alternatively 0x38
	
	// sets up channel 2
	ADC1->SMPR2 |= 0xFFFFFFFF; // 64, 128, 256 - alternatively 0x1C0
	
	// sets channel 1 as the default channel to read
	ADC1->SQR3 = 0x1;
}

uint32_t readADC(uint8_t channel)
{
	// Overwrite the channel to use
	ADC1->SQR3 = channel;
	
	// Send another high to ADON to execute conversion
	ADC1->CR2 |= 1;
	delayADC(1200000);
	while(ADC1->SR == 0)
	{
		
	}
	
	return ADC1->DR;
}