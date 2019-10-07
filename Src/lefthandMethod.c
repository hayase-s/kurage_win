/*
 * lefthandMethod.c
 *
 *  Created on: Sep 26, 2019
 *      Author: kanako
 */


#include "lefthandMethod.h"
#include "move.h"
#include "ad.h"
#include "map.h"
#include "gpio.h"
#include "myassign.h"
#include "motor.h"

void leftHandMethod(void) {
	HAL_Delay(100);
	g_location.x = 0;
	g_location.y = 0;
	g_location.Direction = 0;
	g_WallThreshold.center = 1;
	g_WallThreshold.right = 150;
	g_WallThreshold.left = 65;

	while (1) {
		if (g_location.x == g_location.x_goal
				&& g_location.y == g_location.y_goal) { //ゴール座標
			break;
		} else {
			motorEnable(1);
			if (g_nowWallSensorValue.left < g_WallThreshold.left) { //左に回る
				turnLeft();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.center < g_WallThreshold.center) { //まっすぐ進む
				goAhead();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.right < g_WallThreshold.right) { //右に回る
				turnRight();
				setWalltoMap();
				HAL_Delay(500);
			} else { //後ろに下がる
				goBack();
				setWalltoMap();
				HAL_Delay(500);
			}
		}
	}


}
