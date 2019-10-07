/*
 * motor.h
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include <stdint.h>

typedef struct{
	float dis;
	float vel_r;
	float vel_l;
	float wvel_r;
	float wvel_l;
	float acc;
} tarparameter;

extern tarparameter g_targetTrans;


void rightCWCCW(float wvel_r);
void leftCWCCW(float wvel_l);

uint16_t rightcalPWMCount(float wvel_r);
uint16_t leftcalPWMCount(float wvel_l);

void discalPara(tarparameter *para);

void motorEnable(uint8_t onoff);


#endif /* MOTOR_H_ */
