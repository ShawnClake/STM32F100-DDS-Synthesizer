/* Synth */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "synth.h"
#include "pwm.h"

Synth::Synth(SynthMenu* menu)
{
	this->synthMenu = menu;
	this->setup_sample_timer();
	this->setup_pwm_audio_timer();
	this->setup_tempo_timer();
}

void Synth::pollMenu()
{
	/*if(this->synthMenu->getWaveType() == WaveType::Saw)
		this->setWaveform(&Saw15);
	else if(this->synthMenu->getWaveType() == WaveType::Sine)
		this->voice.sample = Sine;
	else if(this->synthMenu->getWaveType() == WaveType::Square)
		this->voice.sample = Triangle;
	else if(this->synthMenu->getWaveType() == WaveType::Triangle)
		this->voice.sample = Square15;*/
	
	if(this->synthMenu->optionStates.tempo)
	{
		//Helpers helpers;
		//int millisDelay = 1000 / (this->synthMenu->getTempo() / 60); // Current delay with logic in place means 2618 = 1 ms of delay, as we add in more delaying this could shrink further
		//this->tempoDelay = millisDelay * CYCLES_PER_MS; // This is how many cycles of delay function it takes to get ~1ms.
		//return millisDelay * CYCLES_PER_MS; // This is how many cycles of delay function it takes to get ~1ms.
		
		//this->synthMenu->optionStates.tempo = false;
		changeTempo(this->synthMenu->getTempo());
	}
	
	if(this->synthMenu->optionStates.wavetype)
	{
		this->setWaveform(this->synthMenu->getWaveType());
		this->synthMenu->optionStates.wavetype = false;
	}
}

int Synth::getTempoDelay()
{
	return this->tempoDelay;
}

void Synth::setup()
{
	this->setup_sample_timer();
	this->setup_pwm_audio_timer();
}

void Synth::setup_sample_timer()
{
	initPWMSampler(SAMPLE_RATE);
}
void Synth::setup_pwm_audio_timer()
{
	initPWMAudio();
}

void Synth::setup_tempo_timer()
{
	initTempoTicker();
}

void Synth::setWaveform(WaveType wave)
{
	if(wave == WaveType::Saw)
	{
		this->voices[0].sample = Saw15;
	}
	else if(wave == WaveType::Sine)
	{
		this->voices[0].sample = Sine;
		
	}
	else if(wave == WaveType::Square)
	{
		this->voices[0].sample = Square15;
	}
	else if(wave == WaveType::Triangle)
	{
		this->voices[0].sample = Triangle;
	}
	
	for(int i = 1; i < this->synthMenu->getVoices(); i++)
	{
		this->voices[i].sample = this->voices[0].sample;
	}

}

void Synth::applyPitchShift()
{
	float pitchShift = (float)this->synthMenu->getPitch() / 100.0;
	this->voices[0].increment = this->voices[0].accumulator * pitchShift;
	this->voices[1].increment = this->voices[1].accumulator * pitchShift;
	this->voices[2].increment = this->voices[2].accumulator * pitchShift;
	this->voices[3].increment = this->voices[3].accumulator * pitchShift;
}

void Synth::applyDetune()
{
	this->voices[0].increment = this->voices[0].increment;
	this->voices[1].increment = this->voices[1].increment + this->synthMenu->getSpread() / 3;
	this->voices[2].increment = this->voices[2].increment - this->synthMenu->getSpread();
	this->voices[3].increment = this->voices[3].increment + this->synthMenu->getSpread() * 2 / 3;
}

void Synth::noteProcessing()
{
	this->applyPitchShift();
	this->applyDetune();
}

void Synth::delayNote(int count)
{
	int i=0;
	for(i=0; i< count; ++i)
	{
	}
}

void Synth::playNote(uint16_t note, RhythmType rhythmType, float ratioCutOff)
{
	if(ratioCutOff > 1)
		ratioCutOff = 1;
	
	// Set all voices to the new note regardless of voice count
	// We can do this because the extra voices just wont play if we dont have a high enough count
	this->voices[0].accumulator = note;
	this->voices[1].accumulator = note;
	this->voices[2].accumulator = note;
	this->voices[3].accumulator = note;
	
	this->noteProcessing();
	
	/*if(note > 10)
		this->noteProcessing();*/
	
	/*int noteDelay = 0;
	
	if(rhythmType == RhythmType::whole)
	{
		noteDelay = this->getTempoDelay() * 4;
	}
	
	if(rhythmType == RhythmType::half)
	{
		noteDelay = this->getTempoDelay() * 2;
	}
	
	if(rhythmType == RhythmType::quater)
	{
		noteDelay = this->getTempoDelay();
	}
	
	if(rhythmType == RhythmType::eigth)
	{
		noteDelay = this->getTempoDelay() / 2;
	}*/
	
	/*this->delayNote(noteDelay * (1.0 - ratioCutOff));
	
	this->voices[0].increment = REST;
	this->voices[1].increment = REST;
	this->voices[2].increment = REST;
	this->voices[3].increment = REST;
	
	this->delayNote(noteDelay * ratioCutOff);*/
	// do rhythm delays after this point
}

int iamtheguy = 0;

void Synth::generateWave()
{
	//uint16_t total = 0;
	
	//for(uint8_t i = 0; i < this->synthMenu->getVoices(); i++)
	//{
		//total += (int8_t)*(this->voices[i].sample + (this->voices[i].accumulator >> 8));
		//this->voices[i].accumulator += voices[i].increment;
	//}
	
	this->noteProcessing();
	
	uint16_t arrr = this->voices[iamtheguy].increment;
	//arrr = this->voices[0].increment;
	TIM1->ARR = arrr;
	TIM1->CCR1 = arrr / 2;
	/*arrr -= 20;
	if(arr < 50)
		arr = 1024;*/
	
	iamtheguy++;
	if(iamtheguy >= this->synthMenu->getVoices())
		iamtheguy = 0;
	
	/*total = total / this->synthMenu->getVoices();
	total += 128;
	if(total > 255)
		total = 255;
	if(total < 0)
		total = 0;*/
	//TIM1->CCR1 = total;
	
}