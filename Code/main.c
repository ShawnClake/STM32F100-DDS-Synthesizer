/* Main Program */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

//#include "retarget.cpp"

#include "stm32f10x.h"

#include "clock.h"
#include "io.h"
#include "lcd.h"

#include "interupts.h"

/*void EXTI9_5_IRQHandler(void);

void EXTI9_5_IRQHandler(void)
{
	GPIOC->ODR |= GPIO_ODR_ODR9;
	//if(EXTI->PR & EXTI_PR_PR8)
	//	GPIOA->BSRR = GPIO_BSRR_BR10;
	EXTI->PR |= EXTI_PR_PR8;
	//GPIOC->ODR ^= GPIO_ODR_ODR9;
}*/

int main(void)
{
	
	clockInit();
	initPortClocks();
	initLEDConfigs();
	
	//modeInterupt();
	
	initLCD();
	//clearLCD();
	
	

	while(1)
	{
		
	}
	
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR0;
	GPIOC->ODR ^= GPIO_ODR_ODR9;
}
