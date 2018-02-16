/* Synth Menu */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include "stm32f10x.h"
#include "synth_menu.h"
#include "lcd.h"

SynthMenu::SynthMenu()
{
	this->option = Option::tempo;
	this->tempo = 120;
	this->waveType = WaveType::Square;
	this->voices = 1;
	this->spread = 1;
	this->pitch = 100;
	this->note = 512;
}

void SynthMenu::displayPlayback(void)
{
	
	Helpers helpers;
	
	/*LCDScreen* lcd = new LCDScreen("one", helpers.itos(100));
	toLCD(lcd);
	delete(lcd);*/

	int i1 = 0;
	char line1c[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	line1c[i1] = 'W'; i1++;
	line1c[i1] = ':'; i1++;
	
	if(this->waveType == WaveType::Saw)
	{
		line1c[i1] = 's'; i1++;
		line1c[i1] = 'a'; i1++;
		line1c[i1] = 'w'; i1++;
	}
	else if(this->waveType == WaveType::Sine)
	{
		line1c[i1] = 's'; i1++;
		line1c[i1] = 'i'; i1++;
		line1c[i1] = 'n'; i1++;
	}
	else if(this->waveType == WaveType::Square)
	{
		line1c[i1] = 's'; i1++;
		line1c[i1] = 'q'; i1++;
		line1c[i1] = 'r'; i1++;
	}
	else if(this->waveType == WaveType::Triangle)
	{
		line1c[i1] = 't'; i1++;
		line1c[i1] = 'r'; i1++;
		line1c[i1] = 'i'; i1++;
	}
	
	//line1c[i1] = 's'; i1++;
	//line1c[i1] = 'q'; i1++;
	//line1c[i1] = 'r'; i1++;
	line1c[i1] = ' '; i1++;
	line1c[i1] = 'T'; i1++;
	line1c[i1] = ':'; i1++;
	
	char cTempo[5] = {' ', ' ', ' ', ' ', ' '};
	helpers.my_itoa(this->tempo, cTempo, 10);
	for(int j = 0; j < 5; j++)
	{
		if(cTempo[j] == '\0')
			break;
		line1c[i1] = cTempo[j]; i1++;
	}
	
	line1c[i1] = ' '; i1++;
	line1c[i1] = 'V'; i1++;
	line1c[i1] = ':'; i1++;
	
	char cVoices[5] = {' ', ' ', ' ', ' ', ' '};
	helpers.my_itoa(this->voices, cVoices, 10);
	for(int j = 0; j < 5; j++)
	{
		if(cVoices[j] == '\0')
			break;
		line1c[i1] = cVoices[j]; i1++;
	}

	//line1 = std::string("W:") + "sqr" + " T:" + helpers.itos(this->tempo) + " V:" ; 
	std::string line1(line1c);
	
	
	
	int i2 = 0;
	char line2c[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	line2c[i2] = 'D'; i2++;
	line2c[i2] = ':'; i2++;

	char cDetune[5] = {' ', ' ', ' ', ' ', ' '};
	helpers.my_itoa(this->spread, cDetune, 10);
	for(int j = 0; j < 5; j++)
	{
		if(cDetune[j] == '\0')
			break;
		line2c[i2] = cDetune[j]; i2++;
	}
	
	line2c[i2] = ' '; i2++;
	line2c[i2] = 'P'; i2++;
	line2c[i2] = ':'; i2++;
	
	char cPitch[5] = {' ', ' ', ' ', ' ', ' '};
	helpers.my_itoa(this->pitch, cPitch, 10);
	for(int j = 0; j < 5; j++)
	{
		if(cPitch[j] == '\0')
			break;
		line2c[i2] = cPitch[j]; i2++;
	}
	
	
	line2c[i2] = ' '; i2++;
	line2c[i2] = 'N'; i2++;
	line2c[i2] = ':'; i2++;
	
	char cNote[5] = {' ', ' ', ' ', ' ', ' '};
	helpers.my_itoa(this->note, cNote, 10);
	for(int j = 0; j < 5; j++)
	{
		if(cNote[j] == '\0')
			break;
		line2c[i2] = cNote[j]; i2++;
	}
	
	
	
	
	//std::string line2(line2c);
	//line2 = "D:" + helpers.itos(this->spread) + " P:" + helpers.itos(this->pitch) + " N:" + helpers.itos(this->note); 
	
	
	std::string line2(line2c);
	LCDScreen lcd;
	lcd.line1 = line1;
	lcd.line2 = line2;
	toLCD(lcd);
}

void SynthMenu::displaySettings(void)
{
	std::string line1;
	if(this->inOption)
		line1 = "SettingV";
	else
		line1 = "Setting>";
	char num[5] = {' ', ' ', ' ', ' ', ' '};
	
	if(this->option == Option::tempo)
	{
		line1 += "Tempo";
		this->getTempoOption(num);
	}
	
	if(this->option == Option::voices)
	{
		line1 += "Voices";
		this->getVoicesOption(num);
	}
	
	if(this->option == Option::detune)
	{
		line1 += "Detune";
		this->getSpreadOption(num);
	}
	
	if(this->option == Option::wavetype)
	{
		line1 += "Waveform";
		this->getWaveTypeOption(num);
	}
	
	if(this->option == Option::playback)
	{
		line1 += "Playback";
		num[0] = '<';
	}
	
	std::string line2(num);
	LCDScreen lcd;
	lcd.line1 = line1;
	lcd.line2 = line2;
	toLCD(lcd);
}

void SynthMenu::display(void)
{
	if(this->settingsMode)
		this->displaySettings();
	else
		this->displayPlayback();
}

void SynthMenu::pressMode(void)
{
	//if(this->settingsMode && !this->inOption)
	//	this->settingsMode = false;
	if (!this->settingsMode)
		this->settingsMode = true;
	else if(this->settingsMode && !this->inOption)
	{
		if(this->option == Option::playback)
		{
			this->settingsMode = false;
		} else {
			this->inOption = true;
		}
		
	}
	else if(this->settingsMode && this->inOption)
	{
		this->inOption = false;
	}
	
}

void SynthMenu::pressNext(void)
{
	if(this->settingsMode)
	{
		if(!this->inOption)
		{
			// Change the option
			if(this->option == Option::tempo)
			{
				this->option = Option::voices;
			}
			
			else if(this->option == Option::voices)
			{
				this->option = Option::detune;
			}
			
			else if(this->option == Option::detune)
			{
				this->option = Option::wavetype;
			}
			
			else if(this->option == Option::wavetype)
			{
				this->option = Option::playback;
			}
			
			else if(this->option == Option::playback)
			{
				this->option = Option::tempo;
			}
			
		} else {
			this->nextOption(); // Change the value of the option
		}
	}
}

void SynthMenu::getTempoOption(char* line)
{
	Helpers helpers;
	helpers.my_itoa(this->tempo, line, 10);
}
void SynthMenu::getWaveTypeOption(char* line)
{
	if(this->waveType == WaveType::Saw)
	{
		line[0] = 's';
		line[1] = 'a';
		line[2] = 'w';
	}
	else if(this->waveType == WaveType::Sine)
	{
		line[0] = 's';
		line[1] = 'i';
		line[2] = 'n';
	}
	else if(this->waveType == WaveType::Square)
	{
		line[0] = 's';
		line[1] = 'q';
		line[2] = 'r';
	}
	else if(this->waveType == WaveType::Triangle)
	{
		line[0] = 't';
		line[1] = 'r';
		line[2] = 'i';
	}
}
void SynthMenu::getVoicesOption(char* line)
{
	Helpers helpers;
	helpers.my_itoa(this->voices, line, 10);
}
void SynthMenu::getSpreadOption(char* line)
{
	Helpers helpers;
	helpers.my_itoa(this->spread, line, 10);
}

void SynthMenu::nextOption(void)
{
	
	if(this->option == Option::wavetype)
	{
		if(this->waveType == WaveType::Saw)
			this->waveType = WaveType::Sine;
		else if(this->waveType == WaveType::Sine)
			this->waveType = WaveType::Square;
		else if(this->waveType == WaveType::Square)
			this->waveType = WaveType::Triangle;
		else if(this->waveType == WaveType::Triangle)
			this->waveType = WaveType::Saw;
		
		this->optionStates.wavetype = true;
	}
	
	if(this->option == Option::tempo)
	{
		this->tempo += 10;
		if(this->tempo > 240)
			this->tempo = 60;
		
		this->optionStates.tempo = true;
	}
	
	if(this->option == Option::voices)
	{
		this->voices += 1;
		if(this->voices > 4)
			this->voices = 1;
		
		this->optionStates.voices = true;
	}
	
	if(this->option == Option::detune)
	{
		this->spread += 1;
		if(this->spread > 10)
			this->spread = 1;
		
		this->optionStates.detune = true;
	}

}

int SynthMenu::getTempo()
{
	return this->tempo;
}

WaveType SynthMenu::getWaveType()
{
	return this->waveType;
}
int SynthMenu::getVoices()
{
	return this->voices;
}
int SynthMenu::getSpread()
{
	return this->spread;
}
int SynthMenu::getPitch()
{
	return this->pitch;
}
int SynthMenu::getNote()
{
	return this->note;
}

bool SynthMenu::isSettingsMode()
{
	return this->settingsMode;
}