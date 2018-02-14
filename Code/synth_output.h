/* Synth Output */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

#ifndef __SYNTH_OUTPUT__
#define __SYNTH_OUTPUT__

#include <stdint.h>

struct CarrierOutput
{
	bool led1;
	bool led2;
	bool led3;
	bool led4;
	
	CarrierOutput()
	{
		this->led1 = false;
		this->led2 = false;
		this->led3 = false;
		this->led4 = false;

	}
};

class SynthOutput
{
	public:
		void syncToOutputs(CarrierOutput output);
		
	
	
};

#endif