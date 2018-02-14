/* Synth Input */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

#ifndef __SYNTH_INPUT__
#define __SYNTH_INPUT__

#include <stdint.h>

struct CarrierInput
{
	bool btnBlack;
	bool btnBlue;
	bool btnGreen;
	bool btnRed;
	
	bool dip1;
	bool dip2;
	bool dip3;
	bool dip4;
	
	bool btnBlackRising;
	bool btnBlueRising;
	bool btnGreenRising;
	bool btnRedRising;
	
	bool dip1Rising;
	bool dip2Rising;
	bool dip3Rising;
	bool dip4Rising;
	
	CarrierInput()
	{
		this->btnBlack = false;
		this->btnBlue = false;
		this->btnGreen = false;
		this->btnRed = false;
	
		this->dip1 = false;
		this->dip2 = false;
		this->dip3 = false;
		this->dip4 = false;
		
		this->btnBlackRising = false;
		this->btnBlueRising = false;
		this->btnGreenRising = false;
		this->btnRedRising = false;
	
		this->dip1Rising = false;
		this->dip2Rising = false;
		this->dip3Rising = false;
		this->dip4Rising = false;
	}
};

class SynthInput
{
	private:
		CarrierInput previousPoll;
	
	public:
		CarrierInput pollCarrier();
		
	
	
};

#endif