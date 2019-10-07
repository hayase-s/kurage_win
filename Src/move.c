/*
 * move.c
 *
 *  Created on: Sep 23, 2019
 *      Author: kanako
 */
#include "move.h"
#include "tim.h"
#include "myassign.h"
#include "motor.h"
#include "ad.h"
#include "map.h"
#include <math.h>
#include <stdlib.h>

float control;
traaccelerationparameter g_traAcceleration;
turnparameter g_turn;
wallcontrolparameter g_wallControl;

void Traacc(void) {
	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_3);

	g_traAcceleration.a = 1400.0;
	g_traAcceleration.v_start = 200.0;
	g_traAcceleration.v_max = 1500.0;
	g_traAcceleration.v_end = 200.0;

	g_traAcceleration.x_acc = (g_traAcceleration.v_max * g_traAcceleration.v_max
			- g_traAcceleration.v_start * g_traAcceleration.v_start)
			/ (2 * g_traAcceleration.a);
	g_traAcceleration.x_dec = (g_traAcceleration.v_max * g_traAcceleration.v_max
			- g_traAcceleration.v_end * g_traAcceleration.v_end)
			/ (2 * g_traAcceleration.a);
	if ((g_traAcceleration.x_acc + g_traAcceleration.x_dec)
			> g_traAcceleration.x) {
		g_traAcceleration.x_acc = g_traAcceleration.x / 2
				+ (g_traAcceleration.v_end * g_traAcceleration.v_end
						- g_traAcceleration.v_start * g_traAcceleration.v_start)
						/ (4 * g_traAcceleration.a);
		g_traAcceleration.x_dec = g_traAcceleration.x / 2
				+ (g_traAcceleration.v_start * g_traAcceleration.v_start
						- g_traAcceleration.v_end * g_traAcceleration.v_end)
						/ (4 * g_traAcceleration.a);
	}

	g_targetTrans.vel_r = g_traAcceleration.v_start;
	g_targetTrans.vel_l = g_traAcceleration.v_start;
	g_targetTrans.dis = 0;
	g_targetTrans.acc = g_traAcceleration.a;

	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);
	g_traAcceleration.Tra = 1;
	while (g_targetTrans.dis < g_traAcceleration.x) {
	}
	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_3);
	g_traAcceleration.Tra = 0;
}

void turn(void) {
	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_3);

	g_turn.v = 0;
	g_turn.ome = (270.00 / 180.00) * 3.14159265;
	g_turn.r = 47.0;
	g_turn.th_rad = (fabsf(g_turn.th) / 180.00) * 3.14159265;

	if (g_turn.th > 0) {
		g_turn.v_R = g_turn.ome * g_turn.r;
		g_turn.v_L = -g_turn.ome * g_turn.r;
	} else {
		g_turn.v_R = -g_turn.ome * g_turn.r;
		g_turn.v_L = g_turn.ome * g_turn.r;
	}

	g_targetTrans.wvel_r = g_turn.v_R;
	g_targetTrans.wvel_l = g_turn.v_L;

	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_3);

	g_turn.count = 0;
	g_turn.tur = 1;
	while (g_turn.count < (g_turn.th_rad / g_turn.ome) * 1000) {
	}
	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_3);
	g_turn.tur = 0;

}

void wallControl(void) {
	const float Kp = 0.5;
	const float DIFF_THRESHOLD = 30;
	float Error;
	g_wallControl.r_Threadhold = 77;
	g_wallControl.l_Threadhold = 41;
	g_wallControl.r_ref = 270;
	g_wallControl.l_ref = 82;

	if (abs(g_wallControl.r_diff) > DIFF_THRESHOLD) {
		g_wallControl.r_Threadhold = g_wallControl.r_ref + 10;  //変化量が一定以上なら、閾値を引き上げる
	}
	if (abs(g_wallControl.l_diff) > DIFF_THRESHOLD) {
		g_wallControl.r_Threadhold = g_wallControl.l_ref + 10;  //変化量が一定以上なら、閾値を引き上げる
	}//壁切れ対策　本当にできてる？

	if ((g_nowWallSensorValue.right > g_wallControl.r_Threadhold) && (g_nowWallSensorValue.left > g_wallControl.r_Threadhold)) {
		//両壁あり
		Error = (g_nowWallSensorValue.left - g_wallControl.l_ref) - (g_nowWallSensorValue.right - g_wallControl.r_ref); //右に寄ってたらマイナス
	} else if ((g_nowWallSensorValue.right <= g_wallControl.r_Threadhold) && (g_nowWallSensorValue.left < g_wallControl.r_Threadhold)) {
		//両壁なし
		Error = 0;
	} else if (g_nowWallSensorValue.right > g_wallControl.r_Threadhold) {
		//右壁のみあり
		Error = -2.0 * (g_nowWallSensorValue.right - g_wallControl.r_ref); //右に寄ってたらマイナス
	} else {
		//左壁のみあり
		Error = 2.0 * (g_nowWallSensorValue.left - g_wallControl.l_ref); //左に寄ってたらプラス
	}
	control = Kp * Error;
}


void goAhead(void) {
	g_traAcceleration.x = 181;
	Traacc();
	if (g_location.Direction % 4 == 0) { //北を向いていたら
		g_location.y += 1;
	} else if (g_location.Direction % 4 == 1) { //西を向いていたら
		g_location.x -= 1;
	} else if (g_location.Direction % 4 == 2) { //南を向いていたら
		g_location.y -= 1;
	} else {
		g_location.x += 1;
	}

}

void turnLeft(void) {
	g_turn.th = -90;
	turn();
	g_location.Direction += 1;
	HAL_Delay(500);
	g_traAcceleration.x = 181;
	Traacc();
	if (g_location.Direction % 4 == 0) { //北を向いていたら
		g_location.y += 1;
	} else if (g_location.Direction % 4 == 1) { //西を向いていたら
		g_location.x -= 1;
	} else if (g_location.Direction % 4 == 2) { //南を向いていたら
		g_location.y -= 1;
	} else {
		g_location.x += 1;
	}
}

void turnRight(void) {
	g_turn.th = 90;
	turn();
	g_location.Direction += 3;
	HAL_Delay(500);
	g_traAcceleration.x = 181;
	Traacc();
	if (g_location.Direction % 4 == 0) { //北を向いていたら
		g_location.y += 1;
	} else if (g_location.Direction % 4 == 1) { //西を向いていたら
		g_location.x -= 1;
	} else if (g_location.Direction % 4 == 2) { //南を向いていたら
		g_location.y -= 1;
	} else {
		g_location.x += 1;
	}
}

void goBack(void) {
	g_turn.th = 180;
	turn();
	g_location.Direction += 2;
	HAL_Delay(500);
	g_traAcceleration.x = 181;
	Traacc();
	if (g_location.Direction % 4 == 0) { //北を向いていたら
		g_location.y += 1;
	} else if (g_location.Direction % 4 == 1) { //西を向いていたら
		g_location.x -= 1;
	} else if (g_location.Direction % 4 == 2) { //南を向いていたら
		g_location.y -= 1;
	} else {
		g_location.x += 1;
	}
}


