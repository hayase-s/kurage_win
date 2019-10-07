/*
 * adachiMethod.c
 *
 *  Created on: Oct 2, 2019
 *      Author: kanako
 */



#include "adachiMethod.h"
#include "move.h"
#include "map.h"
#include "ad.h"
#include "motor.h"
#include <stdio.h>
void adachi(void) {
	initStepMap();
	g_location.x = 0;
	g_location.y = 0;
	g_location.Direction = 0;
	motorEnable(1); //xxx
	while (g_location.x != g_location.x_goal
			|| g_location.y != g_location.y_goal) {
		StepMapforAdachi();
		if (g_nowWallSensorValue.center > g_WallThreshold.center
				&& g_nowWallSensorValue.right > g_WallThreshold.right
				&& g_nowWallSensorValue.left > g_WallThreshold.left) { //全方向に壁があれば後ろに下がる
			goBack();
			setWalltoMap();
			HAL_Delay(500);
		} else if (compareStep(g_location.x, g_location.y, g_location.Direction)
				== 0) { //壁がなければ前に進む
			if (g_nowWallSensorValue.center < g_WallThreshold.center) {
				goAhead();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		} else if (compareStep(g_location.x, g_location.y, g_location.Direction)
				== 1) { //壁がなければ左に進む
			if (g_nowWallSensorValue.left < g_WallThreshold.left) {
				turnLeft();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		} else if (compareStep(g_location.x, g_location.y, g_location.Direction)
				== 2) { //壁がなければ右に曲がる
			if (g_nowWallSensorValue.right < g_WallThreshold.right) {
				turnRight();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		} else if (compareStep(g_location.x, g_location.y, g_location.Direction)
				== 3) { //前壁→右壁→左壁で試す
			if (g_nowWallSensorValue.center < g_WallThreshold.center) { //前壁がなければ前に進む
				goAhead();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.right < g_WallThreshold.right) { //右壁がなければ右に進む
				turnRight();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.left < g_WallThreshold.left) { //左壁がなければ左に進む
				turnLeft();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		} else if (compareStep(g_location.x, g_location.y, g_location.Direction)
				== 4) { //前→右
			if (g_nowWallSensorValue.center < g_WallThreshold.center) { //前壁がなければ前に進む
				goAhead();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.right < g_WallThreshold.right) { //右壁がなければ右に進む
				turnRight();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		} else if (compareStep(g_location.x, g_location.y, g_location.Direction)
				== 5) { //前→左
			if (g_nowWallSensorValue.left < g_WallThreshold.left) { //左壁がなければ左に進む
				turnLeft();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.center < g_WallThreshold.center) { //前壁がなければ前に進む
				goAhead();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		} else { //右→左
			if (g_nowWallSensorValue.right < g_WallThreshold.right) { //右壁がなければ右に進む
				turnRight();
				setWalltoMap();
				HAL_Delay(500);
			} else if (g_nowWallSensorValue.left < g_WallThreshold.left) { //左壁がなければ左に進む
				turnLeft();
				setWalltoMap();
				HAL_Delay(500);
			} else {
				setWalltoMap();
			}
		}
//		saveMapFlash(0x0800f800);
	}
	motorEnable(0);
}

