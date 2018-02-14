/* Synth Output */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "synth_output.h"

void SynthOutput::syncToOutputs(CarrierOutput output)
{
	if(output.led1)
		GPIOA->BSRR = GPIO_BSRR_BR9;
	else
		GPIOA->BSRR = GPIO_BSRR_BS9;
	
	if(output.led2)
		GPIOA->BSRR = GPIO_BSRR_BR10;
	else
		GPIOA->BSRR = GPIO_BSRR_BS10;
	
	if(output.led3)
		GPIOA->BSRR = GPIO_BSRR_BR11;
	else
		GPIOA->BSRR = GPIO_BSRR_BS11;
	
	if(output.led4)
		GPIOA->BSRR = GPIO_BSRR_BR12;
	else
		GPIOA->BSRR = GPIO_BSRR_BS12;
	
}