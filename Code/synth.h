/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#ifndef __SYNTH__
#define __SYNTH__

#define SAMPLE_RATE       24000UL 
#define CYCLES_PER_MS     5236 // was 2618

#include <stdint.h>
#include "synth_dds_waveforms.h"
#include "rhythms.h"
#include "scale.h"
#include "synth_menu.h"

struct DDS {
	uint16_t increment;
	uint16_t accumulator;
	const int8_t* sample;   /* pointer to beginning of sample in memory */
};

class Synth
{
	private:
		SynthMenu* synthMenu;
		DDS voices[4];
		int tempoDelay;
	
		//Waveforms dds_waveforms;
	
		void setup_sample_timer();
		void setup_pwm_audio_timer();
		
		void setWaveform(WaveType wave);
	
		// Playing
		void noteProcessing();
		void applyDetune();
		void applyPitchShift();
	
		void delayNote(int count);
	public:
		int getTempoDelay();
		void pollMenu();
		void setup();
		Synth(SynthMenu* menu);
	
		void playNote(uint16_t note, RhythmType rhythmType, float ratioCutOff);
		
};


#endif