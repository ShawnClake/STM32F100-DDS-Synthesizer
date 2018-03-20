/* PWM Lib */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#ifndef __PWM__
#define __PWM__

#include <stdint.h>

void initPWM(void);

void initPWMAudio(void);

void initPWMSampler(int sample_rate);

void initTempoTicker(void);

void changeTempo(uint8_t tempo);

#endif
	