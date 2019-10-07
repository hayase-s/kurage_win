/*
 * myassign.h
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */

#ifndef MYASSIGN_H_
#define MYASSIGN_H_

#include <stdint.h>

enum ONOFF {
	HIGH = 1, LOW = 0
};

void lcdRS(uint8_t onOff);
void lcdCS(uint8_t onOff);
void sensorFrontLED(uint8_t highlow);
void sensorSideLED(uint8_t highlow);

#endif /* MYASSIGN_H_ */
