/*
 * ad.h
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */

#ifndef ad_H_
#define ad_H_

#include <stdint.h>


typedef struct {
	int center;
	int right;
	int left;
} wallsenpara;

extern wallsenpara g_offWallSensorValue, g_onWallSensorValue,
		g_nowWallSensorValue;
extern int g_sensorLEDFlag;
extern uint16_t g_ADCBuffer[4];

enum sen_change {
	OFFVALUE, SIDEVALUE, FRONTVALUE, END
};

void getWallSensorValue(void);
void AD_bat(void);
void getSensorvalue(void);

#endif /* ad_H_ */
