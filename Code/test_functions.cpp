/* Main Program */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

//#include "retarget.cpp"


/*

TODO: [REMOVED] Create a preset songs class
TODO: [REMOVED] Add a preset option to the settings menu, simply hovering a preset will play it, and leaving the menu will stop playing it
TODO: [DONE] Add synth keys to playback 5 notes: C,D,E,F,G
TODO: Read over the functional spec to ensure conformity

TODO: [DONE] Add sample & pwm audio timers - (Sample is a timer that controls when we change the duty cycle of the pwm signal, PWM audio timer outputs the duty cycle)
TODO: [DONE] Add timer interupt for calculating the new duty cycle when the sample timer runs out.
TODO: [REMOVED] Add a potentiometer for navigating menus
TODO: [IN PROGRESS] Add a pot for changing pitch
TODO: [REMOVED] Utilize sys_tick timer to debounce our buttons
TODO: [DONE] Change the tempo LED to utilize a timer interrupt

*/



#include "clock.h"
#include "io.h"
#include "lcd.h"

#include "adc.h"

#include "interupts.h"
#include "helpers.h"

#include "synth_menu.h"
#include "synth_input.h"
#include "synth_output.h"
#include "synth.h"
#include "scale.h"

// Use this because C++ mangles functions names as an 'optimization' whereas C does not.
extern "C" {
	void EXTI9_5_IRQHandler(void);
	void TIM2_IRQHandler(void);
	void TIM3_IRQHandler(void);
	uint16_t theValueToPlay = 500;
	//void EXTI0_IRQHandler(void); //Test on board button interupt
}

// Test on board button interupt
// Remember to uncomment the code in interupts.h as well.
/*void EXTI0_IRQHandler(void)
{
	EXTI->PR |= EXTI_PR_PR0;
	GPIOC->ODR ^= GPIO_ODR_ODR9;
}*/

/* GLOBAL SYNTH INSTANCES */
SynthMenu* synth_menu = new SynthMenu();
//SynthInput* synth_input = new SynthInput();
SynthOutput* synth_output = new SynthOutput();
Synth synth(synth_menu);

CarrierOutput carrierOutput;

bool needsChange = false;

int main(void)
{
	
	clockInit();
	initPortClocks();
	//initSwitchConfigs();
	initLEDConfigs();
	initADC();
	initLCD();
	clearLCD();
	
	modeInterupt();
	//Helpers helpers;

	//
//bool blinky = false;
	
	while(1)
	{
		//uint8_t switches = readSwitches();
		
		//setLEDs(switches);
		//std::string what = "what";
		
		//LCDScreen* lcd = new LCDScreen("W:sqr T:120 V:3", "D:5 P:100 N:512");
		//lcd->line1 = "W:sqr T:120 V:3";
		//lcd->line2 = "D:5 P:100 N:512";
		//toLCD(lcd);
		//delete(lcd);
		
		
		//line1LCD();
		//strLCD(what);
		//CarrierInput carrierInput = input->pollCarrier();
		
		carrierOutput.led5 = false;
		carrierOutput.led6 = false;
		
		
		carrierOutput.led1 = true;
		
		if(!(GPIOB->IDR & GPIO_IDR_IDR10))
		{
			//synth.playNote(700, RhythmType::quater, 0);
			if(theValueToPlay != 770)
			{
				needsChange = true;
				theValueToPlay = 770;
			}
			synth_menu->setNote(770);
			carrierOutput.led3 = true;
			if(GPIOA->IDR & GPIO_IDR_IDR6 && !needsChange)
				TIM1->CR1 |= TIM_CR1_CEN;
		}
		else if(!(GPIOB->IDR & GPIO_IDR_IDR11))
		{
			if(theValueToPlay != 605)
			{
				needsChange = true;
				theValueToPlay = 605;
			}
			synth_menu->setNote(605);
			carrierOutput.led3 = true;
			if(GPIOA->IDR & GPIO_IDR_IDR6 && !needsChange)
				TIM1->CR1 |= TIM_CR1_CEN;
		}
		else if(!(GPIOB->IDR & GPIO_IDR_IDR12))
		{
			if(theValueToPlay != 500)
			{
				needsChange = true;
				theValueToPlay = 500;
			}
			theValueToPlay = 500;
			synth_menu->setNote(500);
			carrierOutput.led3 = true;
			if(GPIOA->IDR & GPIO_IDR_IDR6 && !needsChange)
				TIM1->CR1 |= TIM_CR1_CEN;
		}
		else
		{
			synth_menu->setNote(0);
			theValueToPlay = 967;
			carrierOutput.led3 = false;
			TIM1->CR1 &= ~TIM_CR1_CEN;
		}
		
		if(!(GPIOA->IDR & GPIO_IDR_IDR6))
		{
			TIM1->CR1 &= ~TIM_CR1_CEN;
			TIM2->CR1 &= ~TIM_CR1_CEN;
		}
		
		if(!(GPIOA->IDR & GPIO_IDR_IDR7)) // Pitch lock
		{
			synth_menu->setPitch(100);
		} else {
			if(!(GPIOC->IDR & GPIO_IDR_IDR10))
			{
				carrierOutput.led5 = true;
				synth_menu->setPitch(((150 - 50) * (readADC(0x2) - 150) / (3600 - 150)) + 50);
			} else
			{
				carrierOutput.led6 = true;
				synth_menu->setPitch(((150 - 50) * (readADC(0x1) - 150) / (3600 - 150)) + 50);
			}
			//uint32_t pitch = ;
			//uint32_t finalPitch = helpers.scaleVal(pitch, 0, 4000, 50, 200);
			
		}
			
			
			
		
		/*if(carrierInput.btnRedRising)
		{
			menu->pressMode();
			carrierOutput.led2 = true;
		}
		
		if(carrierInput.btnGreenRising)
		{
			menu->pressNext();
			carrierOutput.led3 = true;
		}*/
		
		/*if(!synth_menu->isSettingsMode())
		{
			blinky = !blinky;
			carrierOutput.led4 = blinky;
		}*/
		
		//delay(1309000 * 2); //2618000 is roughly 60 BPM
		
		// Has to stay out of an isSettingsMode as pitch/note can change on the fly when in playback mode
		synth.pollMenu();
		
		//delay(synth.getTempoDelay() / 2);
		synth_menu->display();
		synth_output->syncToOutputs(carrierOutput);
		
		
		
		
		//TIM1->ARR = 180;
		
		//delay(1200000);
		
		//TIM1->ARR = 255;
		
		//synth.playNote(NOTE_G2, RhythmType::quater, 0);
		
		//delay(1200000);
		
	}
	
	return 0;
	
}

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	synth.generateWave();
}



void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;
	carrierOutput.led4 = !carrierOutput.led4;
	synth.playNote(theValueToPlay, RhythmType::quater, 0);
	needsChange = false;
	//synth.playNote(arr, RhythmType::quater, 0);
	
	/*if(~(GPIOB->IDR & GPIO_IDR_IDR12))
		synth.playNote(500, RhythmType::quater, 0);
	else
		synth.playNote(1000, RhythmType::quater, 0);*/
	
	/*arr -= 20;
	if(arr < 50)
		arr = 1024;
	synth.playNote(arr, RhythmType::quater, 0);*/

	/*TIM1->ARR = arr;
	TIM1->CCR1 = arr / 2;
	arr -= 20;
	if(arr < 50)
		arr = 1024;*/
	
	
}


void EXTI9_5_IRQHandler(void)
{	
	// Mode button
	if(EXTI->PR & EXTI_PR_PR8)
	{
		delay(80000);
		EXTI->PR |= EXTI_PR_PR8;
		synth_menu->pressMode();
		
	}
	
	// Next button
	if(EXTI->PR & EXTI_PR_PR9)
	{
		delay(80000);
		EXTI->PR |= EXTI_PR_PR9;
		synth_menu->pressNext();
		
	}

}


