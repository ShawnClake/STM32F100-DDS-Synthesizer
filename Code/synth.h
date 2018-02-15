/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#ifndef __SYNTH__
#define __SYNTH__

#include <stdint.h>
#include "synth_dds_waveforms.h"
#include "synth_menu.h"

#define SAMPLE_RATE       24000UL 
#define CYCLES_PER_MS     2618

struct DDS {
	uint16_t increment;
	uint16_t accumulator;
	const int8_t* sample;   /* pointer to beginning of sample in memory */
};

class Synth
{
	private:
		SynthMenu* synthMenu;
		DDS voice;
		int tempoDelay;
	
		Waveforms dds_waveforms;
	
		void setup_sample_timer();
		void setup_pwm_audio_timer();
	
	public:
		int getTempoDelay();
		void pollMenu();
		void setup();
		Synth(SynthMenu* menu);
		
};


#endif