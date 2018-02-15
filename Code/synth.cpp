/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "synth.h"

Synth::Synth(SynthMenu* menu)
{
	this->synthMenu = menu;
}

void Synth::pollMenu()
{
	if(this->synthMenu->getWaveType() == WaveType::Saw)
		this->voice.sample = this->dds_waveforms.Saw15;
	else if(this->synthMenu->getWaveType() == WaveType::Sine)
		this->voice.sample = this->dds_waveforms.Sine;
	else if(this->synthMenu->getWaveType() == WaveType::Square)
		this->voice.sample = this->dds_waveforms.Triangle;
	else if(this->synthMenu->getWaveType() == WaveType::Triangle)
		this->voice.sample = this->dds_waveforms.Square15;
}

int Synth::getTempoDelay()
{
	Helpers helpers;
	int millisDelay = 1000 / (this->synthMenu->getTempo() / 60); // Current delay with logic in place means 2618 = 1 ms of delay, as we add in more delaying this could shrink further
  return millisDelay * CYCLES_PER_MS; // This is how many cycles of delay function it takes to get ~1ms.
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