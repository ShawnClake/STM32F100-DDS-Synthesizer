/* ADC Lib */
/* Author: Shawn Clake */
/* Date: Feb, 2018 */

#include <stdint.h>

void delayADC(uint32_t count);

void initADCPorts(void);

void initADC(void);

uint32_t readADC(uint8_t channel);