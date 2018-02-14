/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "synth.h"

Synth::Synth()
{
		this->voice.sample = this->dds_waveforms.Square15;
}

void Synth::setup()
{
	this->setup_sample_timer();
	this->setup_pwm_audio_timer();
}

void Synth::setup_sample_timer()
{
	
}
void Synth::setup_pwm_audio_timer()
{
	
}