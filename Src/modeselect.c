/*
 * modeselect.c
 *
 *  Created on: Sep 26, 2019
 *      Author: kanako
 */

#include "modeselect.h"
#include "aqm1248a.h"
#include "gpio.h"
#include "lefthandMethod.h"
#include "adachiMethod.h"
#include "map.h"
#include "ad.h"
#include <stdint.h>

void modeSelect(void) {
	uint8_t mode;
	uint8_t select;
	for (uint8_t i = 0; i <= 3; i++) {
		select = 0;
		if (i == 0) { //モードセレクト
			printfLCD(0, 0, BLACK, "           ");
			printfLCD(1, 0, WHITE, "MODE SELECT");
			printfLCD(2, 0, BLACK, "           ");
			while (select == 0) {
				if (HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_12) == 0) { //次のモード画面に LOW
					HAL_Delay(300);
					select = 1;
				} else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0) { //次のモード画面に LOW
					HAL_Delay(300);
					select = 1;
				} else {

				}
			}
		} else if (i == 1) { //足立法
			printfLCD(1, 0, WHITE, "!  ADCHI  !");

			while (select == 0) {
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0) { //次のモード画面に LOW
					HAL_Delay(300);
					select = 1;
				} else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0) { //足立法スタート LOW
					HAL_Delay(300);
					mode = 1;
					i = 3;
					select = 1;
				} else {
				}
			}

		} else if (i == 2) {
			printfLCD(1, 0, WHITE, "!   MAP   !");
			while (select == 0) {
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0) { //次のモード画面に LOW
					HAL_Delay(300);
					select = 1;
				} else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0) { //マップ表示 LOW
					HAL_Delay(300);
					mode = 2;
					i = 3;
					select = 1;
				} else {
				}
			}

		} else { //左手法
			printfLCD(1, 0, WHITE, "! HIDARTE !");
			while (select == 0) {
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12) == 0) { //次のモード画面に LOW
					HAL_Delay(300);
					i = 0;
					select = 1;
				} else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0) { //マップ表示 LOW
					HAL_Delay(300);
					mode = 3;
					i = 3;
					select = 1;
				} else {
				}
			}
		}
	}

	if (mode == 1) { //ADACH
		printfLCD(1, 0, WHITE, "!  ADACHI !");
		printfLCD(2, 0, BLACK, "   START!   ");
		g_sensorLEDFlag = 1;
		HAL_Delay(1000);
		initWall();
		adachi();
		saveMapFlash(0x0800f800);
	} else if (mode == 2) { //MAP
		printfLCD(1, 0, WHITE, "!   MAP   !");
		printfLCD(2, 0, BLACK, "   START!   ");
		HAL_Delay(500);
		loadMapFlash(0x0800f800);
		initStepMap();
		StepMapforAdachi();
		printWall();
	} else { //HIDARITE
		printfLCD(1, 0, WHITE, "! HIDARTE !");
		printfLCD(2, 0, BLACK, "   START!   ");
		g_sensorLEDFlag = 1;
		HAL_Delay(1000);
		initWall();
		leftHandMethod();
		saveMapFlash(0x0800f800);
	}

}
