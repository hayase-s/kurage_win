/*
 * myassign.c
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */



#include "stm32f3xx_hal.h"
#include "gpio.h"
#include "myassign.h"

//Output
void lcdRS(uint8_t onOff) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, onOff);
}
void lcdCS(uint8_t onOff) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, onOff);
}

//Input

void sensorFrontLED(uint8_t highlow) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, highlow);
}

void sensorSideLED(uint8_t highlow) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, highlow);
}
