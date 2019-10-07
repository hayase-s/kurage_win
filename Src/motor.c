/*
 * motor.c
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */

#include "motor.h"
#include "myassign.h"
#include "gpio.h"
#include <stdint.h>
#include <math.h>

const uint8_t tireDia = 52; //定数
const float dT = 0.001;
tarparameter g_targetTrans;

uint16_t rightcalPWMCount(float wvel_r) {
	uint16_t PWMCount;
	if ((fabs(g_targetTrans.wvel_r) > 0.0)
			&& ((8000000 * 0.9 * (3.141592653 / 180) * (tireDia / 2))
					/ fabs(g_targetTrans.wvel_r) < UINT16_MAX)) {
		PWMCount = (uint16_t) ((8000000 * 0.9 * (3.141592653 / 180)
				* (tireDia / 2)) / fabs(g_targetTrans.wvel_r)) - 1;
	} else {
		PWMCount = UINT16_MAX - 1;
	}
	return PWMCount;
} //SOKUDO_MIGI

uint16_t leftcalPWMCount(float wvel_l) {
	uint16_t PWMCount;
	if ((fabs(g_targetTrans.wvel_l) > 0.0)
			&& ((8000000 * 0.9 * (3.141592653 / 180) * (tireDia / 2))
					/ fabs(g_targetTrans.wvel_l) < UINT16_MAX)) {
		PWMCount = (uint16_t) ((8000000 * 0.9 * (3.141592653 / 180)
				* (tireDia / 2)) / fabs(g_targetTrans.wvel_l)) - 1;
	} else {
		PWMCount = UINT16_MAX - 1;
	}
	return PWMCount;
} //SOKUDO_HIDARI

void rightCWCCW(float wvel_r) {
	if (g_targetTrans.wvel_r > 0.0) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, HIGH);
	} else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, LOW);
	}
} //MAEUSHIRO_MIGI

void leftCWCCW(float wvel_l) {
	if (g_targetTrans.wvel_l > 0.0) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, LOW);
	} else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, HIGH);
	}
} //MAEUSHIRO_HIDARI

//xxx
void discalPara(tarparameter *para) { //関数名
	para->dis += para->vel_r * dT;
} //SEKIBUNKANSUU

void motorEnable(uint8_t onoff) {
	if (onoff == 1) {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, HIGH);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, SET);
		HAL_Delay(3);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, RESET);
	} else {
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, LOW);
	}
}
