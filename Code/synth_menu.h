/* Synth Menu */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include <stdint.h>
#include "synth_dds_waveforms.h"
#include "helpers.h"

enum class Option
{
	tempo,
	voices,
	detune,
	wavetype,
	playback
};

class SynthMenu
{
	private:
		bool settingsMode = false;
		bool inOption = false;
		Option option;
	
		// Current option values
		int tempo;
		WaveType waveType;
		int voices;
		int spread;
	
		// Real time adjusted and not in settings menu but controlled here anyways
		int pitch;
		int note;
	
		void displayPlayback(void);
		void displaySettings(void);
	
		void getTempoOption(char* line);
		void getWaveTypeOption(char* line);
		void getVoicesOption(char* line);
		void getSpreadOption(char* line);
		
		void nextOption(void);
		//void saveOption(void);
	
	public:
		SynthMenu();
	
		void display(void);
		
		void pressMode(void);
		void pressNext(void);
};