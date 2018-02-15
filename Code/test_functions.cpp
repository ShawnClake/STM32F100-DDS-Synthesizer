/* Main Program */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

//#include "retarget.cpp"

#include "clock.h"
#include "io.h"
#include "lcd.h"

#include "synth_menu.h"
#include "synth_input.h"
#include "synth_output.h"
#include "synth.h"

int main(void)
{
	
	clockInit();
	initPortClocks();
	initLEDConfigs();
	
	initLCD();
	clearLCD();
	SynthMenu* menu = new SynthMenu();
	SynthInput* input = new SynthInput();
	SynthOutput* output = new SynthOutput();
	//Synth synth(menu);
	
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
		CarrierInput carrierInput = input->pollCarrier();
		
		CarrierOutput carrierOutput;
		carrierOutput.led1 = true;
		
		
		
		if(carrierInput.btnRedRising)
		{
			menu->pressMode();
			carrierOutput.led2 = true;
		}
		
		if(carrierInput.btnGreenRising)
		{
			menu->pressNext();
			carrierOutput.led3 = true;
		}

		blinky = !blinky;
		carrierOutput.led4 = blinky;
		//delay(1309000 * 2); //2618000 is roughly 60 BPM
		
		//synth.pollMenu();
		//delay(synth.getTempoDelay());
		
		menu->display();
		output->syncToOutputs(carrierOutput);
		
	}
	
	return 0;
	
}
