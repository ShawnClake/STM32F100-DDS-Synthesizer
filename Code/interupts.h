/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#ifndef __INTERUPTS__
#define __INTERUPTS__

#include <stdint.h>
#include "stm32f10x.h"

void modeInterupt(void)
{
	// This enables the onboard test interupt button
	/*	// Enable AFIO Clock so that NVIC can run
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Choose Port A
	AFIO->EXTICR[0] &= ~AFIO_EXTICR1_EXTI0;
	
	// Unmask P0
	EXTI->IMR |= EXTI_IMR_MR0;
	
	// Select falling edge for the button
	EXTI->FTSR |= EXTI_FTSR_TR0;
	
	// Unmask EXTI0
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;*/
	
	
	
	
	// Setup interupt clock
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	/* Next 4 lines setup red button (PB8) as an interupt with a falling edge trigger and unmasked interupt */ 
	AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI8;   // resets bottom 4 bits to 0's
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PB; // puts a 1 into bit0 to use port B
	EXTI->IMR |= EXTI_IMR_MR8;
	EXTI->FTSR |= EXTI_FTSR_TR8;
	
	/* Next 4 lines setup green button (PB9) as an interupt with a falling edge trigger and unmasked interupt */ 
	AFIO->EXTICR[2] &= ~AFIO_EXTICR3_EXTI9;   // resets bottom 4 bits to 0's
	AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI9_PB; // puts a 1 into bit0 to use port B
	EXTI->IMR |= EXTI_IMR_MR9;
	EXTI->FTSR |= EXTI_FTSR_TR9;
	
	// Enable the EXTI9_5 interupt handler
	NVIC->ISER[0] |= NVIC_ISER_SETENA_23;
	
	NVIC->ISER[0] |= NVIC_ISER_SETENA_28;
	NVIC->ISER[0] |= NVIC_ISER_SETENA_29;
}

#endif