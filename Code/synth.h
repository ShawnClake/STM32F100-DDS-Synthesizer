/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#ifndef __SYNTH__
#define __SYNTH__

#include <stdint.h>
#include "synth_dds_waveforms.h"

#define SAMPLE_RATE       24000UL 

struct DDS {
	uint16_t increment;
	uint16_t accumulator;
	const int8_t* sample;   /* pointer to beginning of sample in memory */
};

class Synth
{
	private:
		DDS voice;
	
		Waveforms dds_waveforms;
	
		void setup_sample_timer();
		void setup_pwm_audio_timer();
	
	public:
		void setup();
		Synth();
		
	
	
	
};


#endif