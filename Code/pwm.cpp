#include "stm32f10x.h"
#include "pwm.h"

void initPWM(void)
{
	// Enable AFIO Clock so that NVIC can run
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Enable port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Enable TIM1 clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	// Disables MCO output (Microcontroller clock output)
	//RCC->CFGR &= 0xF8FFFFFF;

	// Enable PA8 as a output
	GPIOA->CRH |= GPIO_CRH_MODE8;
  GPIOA->CRH &= ~GPIO_CRH_CNF8_0;   // need this to become 10, so 00's first
	//GPIOA->CRH |= GPIO_CRH_CNF8_1; // then add the 10
	
	// CLOCK SETUPS COMPLETE

	// TIMER SETUPS NOW
	
	// Tell the timer we are about the configure it
	TIM1->CR1 |= TIM_CR1_CEN;
	
	// Sets the default idle level high, invert to set default idle level low.
	// This is currently great for active low devices
	TIM1->CR2 |= TIM_CR2_OIS1;
	
	// This allows values we save into registers to go from a 'buffer' register to the
	// actual register
	TIM1->EGR |= TIM_EGR_UG;

	// OC1M_x sets the PWM mode bits. Here we are setting it to PWM Mode 1
	// OC1MPE sets preload enable will allow us to read/write without needing to tell it
	// OC1MFE allows us to auto loop the timer rather than reinitiate it
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	
	// Turns on channel 1
	TIM1->CCER |= TIM_CCER_CC1E;
	
	/*
	Here we set configurable values
	PSC: Predivider which when not touched is 24MHz (Subtract 1 because of shenanigans)
	ARR: This controls the period. The period is a frequency of (ARR * (24MHz / PSC))
	CCR1: This controls the pulse width. The pulse width %on is = (ARR/CCR1)
	*/
	
	TIM1->PSC = 2400 - 1;
	TIM1->ARR = 100;
	TIM1->CCR1 = 100 / 2;
	
	
	
	// Sets Main Output Enable so that pin A8 gets the signal
	// Sets off state select for idle mode
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	
	// Enables the timer
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	
	
}



void initPWMAudio(void)
{
	
	// Enable AFIO Clock so that NVIC can run
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Enable port A
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Enable TIM1 clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	// Disables MCO output (Microcontroller clock output)
	//RCC->CFGR &= 0xF8FFFFFF;
	
	//temp
	//GPIOB->CRH |= GPIO_CRH_MODE13 | GPIO_CRH_CNF13_1;
  //GPIOB->CRH &= ~GPIO_CRH_CNF13_0;
	
	
	// Enable PA8 as a output
	GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;
  GPIOA->CRH &= ~GPIO_CRH_CNF8_0;   // need this to become 10, so 00's first
	//GPIOA->CRH |= GPIO_CRH_CNF8_1; // then add the 10
	
	// CLOCK SETUPS COMPLETE

	// TIMER SETUPS NOW
	
	// Tell the timer we are about the configure it
	TIM1->CR1 |= TIM_CR1_CEN;
	
	// Sets the default idle level high, invert to set default idle level low.
	// This is currently great for active low devices
	TIM1->CR2 |= TIM_CR2_OIS1;
	
	// This allows values we save into registers to go from a 'buffer' register to the
	// actual register
	TIM1->EGR |= TIM_EGR_UG;

	// OC1M_x sets the PWM mode bits. Here we are setting it to PWM Mode 1
	// OC1MPE sets preload enable will allow us to read/write without needing to tell it
	// OC1MFE allows us to auto loop the timer rather than reinitiate it
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	
	// Turns on channel 1
	TIM1->CCER |= TIM_CCER_CC1E;
	
	/*
	Here we set configurable values
	PSC: Predivider which when not touched is 24MHz (Subtract 1 because of shenanigans)
	ARR: This controls the period. The period is a frequency of (ARR * (24MHz / PSC))
	CCR1: This controls the pulse width. The pulse width %on is = (ARR/CCR1)
	*/
	
	//TIM1->PSC = 2400 - 1;
	TIM1->PSC = 380 - 1;
	TIM1->ARR = 255;
	TIM1->CCR1 = 255 / 2;
	
	// Sets Main Output Enable so that pin A8 gets the signal
	// Sets off state select for idle mode
	TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	
	// Enables the timer
	TIM1->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	
}

void initPWMSampler(int sample_rate)
{
	
	// Enable AFIO Clock so that NVIC can run
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Enable port A
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Enable TIM1 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	// Disables MCO output (Microcontroller clock output)
	//RCC->CFGR &= 0xF8FFFFFF;
	
	//temp
	//GPIOB->CRH |= GPIO_CRH_MODE13 | GPIO_CRH_CNF13_1;
  //GPIOB->CRH &= ~GPIO_CRH_CNF13_0;
	
	
	// We don't need to output the signal for the sampler timer
	// Enable PA8 as a output
	//GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;
  //GPIOA->CRH &= ~GPIO_CRH_CNF8_0;   // need this to become 10, so 00's first
	//GPIOA->CRH |= GPIO_CRH_CNF8_1; // then add the 10
	
	// CLOCK SETUPS COMPLETE

	// TIMER SETUPS NOW
	
	// Tell the timer we are about the configure it
	TIM2->CR1 |= TIM_CR1_CEN;
	
	// Sets the default idle level high, invert to set default idle level low.
	// This is currently great for active low devices
	//TIM2->CR2 |= TIM_CR2_OIS1;
	
	// This allows values we save into registers to go from a 'buffer' register to the
	// actual register
	TIM2->EGR |= TIM_EGR_UG;

	// OC1M_x sets the PWM mode bits. Here we are setting it to PWM Mode 1
	// OC1MPE sets preload enable will allow us to read/write without needing to tell it
	// OC1MFE allows us to auto loop the timer rather than reinitiate it
	//TIM2->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	
	// Turns on channel 1
	TIM2->CCER |= TIM_CCER_CC1E;
	
	// Enable events
	TIM2->DIER |= TIM_DIER_UIE;
	
	/*
	Here we set configurable values
	PSC: Predivider which when not touched is 24MHz (Subtract 1 because of shenanigans)
	ARR: This controls the period. The period is a frequency of (ARR * (24MHz / PSC))
	CCR1: This controls the pulse width. The pulse width %on is = (ARR/CCR1)
	*/
	
	//TIM1->PSC = 2400 - 1;
	TIM2->PSC = 250 - 1; // Should result in about 96kHz
	TIM2->ARR = (96000 / sample_rate) - 1; // Basically divides the timers overflow frequency by 4, will count 0,1,2,3 generate overflow event and then startover
	//TIM2->CCR1 = 255 / 2; // not needed because we arent outputting this signal
	
	// Sets Main Output Enable so that pin A8 gets the signal
	// Sets off state select for idle mode
	//TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	
	// Enables the timer
	TIM2->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	
}





void initTempoTicker(void)
{
	
	// Enable AFIO Clock so that NVIC can run
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Enable port A
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// Enable TIM1 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	// Disables MCO output (Microcontroller clock output)
	//RCC->CFGR &= 0xF8FFFFFF;
	
	//temp
	//GPIOB->CRH |= GPIO_CRH_MODE13 | GPIO_CRH_CNF13_1;
  //GPIOB->CRH &= ~GPIO_CRH_CNF13_0;
	
	
	// We don't need to output the signal for the sampler timer
	// Enable PA8 as a output
	//GPIOA->CRH |= GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1;
  //GPIOA->CRH &= ~GPIO_CRH_CNF8_0;   // need this to become 10, so 00's first
	//GPIOA->CRH |= GPIO_CRH_CNF8_1; // then add the 10
	
	// CLOCK SETUPS COMPLETE

	// TIMER SETUPS NOW
	
	// Tell the timer we are about the configure it
	TIM3->CR1 |= TIM_CR1_CEN;
	
	// Sets the default idle level high, invert to set default idle level low.
	// This is currently great for active low devices
	//TIM3->CR2 |= TIM_CR2_OIS1;
	
	// This allows values we save into registers to go from a 'buffer' register to the
	// actual register
	TIM3->EGR |= TIM_EGR_UG;

	// OC1M_x sets the PWM mode bits. Here we are setting it to PWM Mode 1
	// OC1MPE sets preload enable will allow us to read/write without needing to tell it
	// OC1MFE allows us to auto loop the timer rather than reinitiate it
	//TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;
	
	// Turns on channel 1
	TIM3->CCER |= TIM_CCER_CC2E;
	
	// Enable events
	TIM3->DIER |= TIM_DIER_UIE;
	
	/*
	Here we set configurable values
	PSC: Predivider which when not touched is 24MHz (Subtract 1 because of shenanigans)
	ARR: This controls the period. The period is a frequency of (ARR * (24MHz / PSC))
	CCR1: This controls the pulse width. The pulse width %on is = (ARR/CCR1)
	*/
	
	//TIM1->PSC = 2400 - 1;
	TIM3->PSC = 2400 - 1; // Should result in about 10kHz
	TIM3->ARR = 5000 / 2; // Sets up a default of 2Hz (120 BPM) (Technically we split it so we can get the on part of the beat and the off part)
	//TIM2->CCR1 = 255 / 2; // not needed because we arent outputting this signal
	
	// Sets Main Output Enable so that pin A8 gets the signal
	// Sets off state select for idle mode
	//TIM1->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSI;
	
	// Enables the timer
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
	
	
}

void changeTempo(uint8_t tempo)
{
	TIM3->ARR = 10000 / (tempo / 30); // Only dividing by 30 here so we can get the on part and off part of the beat seperately
}