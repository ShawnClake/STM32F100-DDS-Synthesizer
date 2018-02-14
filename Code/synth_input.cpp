/* Synth Input */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "synth_input.h"

CarrierInput SynthInput::pollCarrier()
{
	CarrierInput reads;
	
	if(!(GPIOA->IDR & GPIO_IDR_IDR6))
		reads.dip1 = true;
	if(!(GPIOA->IDR & GPIO_IDR_IDR7))
		reads.dip2 = true;
	if(!(GPIOC->IDR & GPIO_IDR_IDR10))
		reads.dip3 = true;
	if(!(GPIOC->IDR & GPIO_IDR_IDR11))
		reads.dip4 = true;
	if(!(GPIOB->IDR & GPIO_IDR_IDR8))
		reads.btnRed = true;
	if(!(GPIOB->IDR & GPIO_IDR_IDR9))
		reads.btnGreen = true;
	if(!(GPIOC->IDR & GPIO_IDR_IDR12))
		reads.btnBlue = true;
	if(!(GPIOA->IDR & GPIO_IDR_IDR5))
		reads.btnBlack = true;
	
	if(reads.dip1 && !this->previousPoll.dip1)
		reads.dip1Rising = true;
	
	if(reads.dip2 && !this->previousPoll.dip2)
		reads.dip2Rising = true;
		
	if(reads.dip3 && !this->previousPoll.dip3)
		reads.dip3Rising = true;
			
	if(reads.dip4 && !this->previousPoll.dip4)
		reads.dip4Rising = true;
				
	if(reads.btnRed && !this->previousPoll.btnRed)
		reads.btnRedRising = true;
	
	if(reads.btnGreen && !this->previousPoll.btnGreen)
		reads.btnGreenRising = true;
	
	if(reads.btnBlue && !this->previousPoll.btnBlue)
		reads.btnBlueRising = true;

	if(reads.btnBlack && !this->previousPoll.btnBlack)
		reads.btnBlackRising = true;
	
	this->previousPoll = reads;
	
	return reads;
	
}