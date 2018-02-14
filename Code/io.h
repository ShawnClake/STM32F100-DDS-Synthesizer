/* IO Lib */
/* Author: Shawn Clake */
/* Date: Jan, 2018 */

#include <stdint.h>

void initPortClocks(void);

void initPortAClock(void);

void initPortBClock(void);

void initPortCClock(void);

void initLEDConfigs(void);

uint8_t readSwitches(void);

void setLEDs(uint8_t leds);
