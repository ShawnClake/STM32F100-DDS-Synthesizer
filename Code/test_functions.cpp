/* Main Program */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

//#include "retarget.cpp"


/*

TODO: Create a preset songs class
TODO: Add a preset option to the settings menu, simply hovering a preset will play it, and leaving the menu will stop playing it
TODO: Add synth keys to playback 5 notes: C,D,E,F,G
TODO: Read over the functional spec to ensure conformity

TODO: Add sample & pwm audio timers

*/



#include "clock.h"
#include "io.h"
#include "lcd.h"

#include "interupts.h"

#include "synth_menu.h"
#include "synth_input.h"
#include "synth_output.h"
#include "synth.h"

// Use this because C++ mangles functions names as an 'optimization' whereas C does not.
extern "C" {
	void EXTI9_5_IRQHandler(void);
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

int main(void)
{
	
	clockInit();
	initPortClocks();
	initLEDConfigs();
	
	initLCD();
	clearLCD();
	
	modeInterupt();
	

	
bool blinky = false;
	
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
		
		CarrierOutput carrierOutput;
		carrierOutput.led1 = true;
		
		
		
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
		
		if(!synth_menu->isSettingsMode())
		{
			blinky = !blinky;
			carrierOutput.led4 = blinky;
		}
		
		//delay(1309000 * 2); //2618000 is roughly 60 BPM
		
		// Has to stay out of an isSettingsMode as pitch/note can change on the fly when in playback mode
		synth.pollMenu();
		
		delay(synth.getTempoDelay() / 2);
		synth_menu->display();
		synth_output->syncToOutputs(carrierOutput);
		
	}
	
	return 0;
	
}


void EXTI9_5_IRQHandler(void)
{	
	// Mode button
	if(EXTI->PR & EXTI_PR_PR8)
	{
		delay(40000);
		EXTI->PR |= EXTI_PR_PR8;
		synth_menu->pressMode();
		
	}
	
	// Next button
	if(EXTI->PR & EXTI_PR_PR9)
	{
		delay(40000);
		EXTI->PR |= EXTI_PR_PR9;
		synth_menu->pressNext();
		
	}

}


