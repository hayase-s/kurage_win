/*
 * move.h
 *
 *  Created on: Sep 23, 2019
 *      Author: kanako
 */

#ifndef MOVE_H_
#define MOVE_H_

#include <stdint.h>

typedef struct{
	float a;
	float v_start;
	float v_max;
	float v_end;
	float x;
	float x_acc;
	float x_dec;
	uint8_t Tra;
}traaccelerationparameter;

typedef struct{
	float v_R;
	float v_L;
	float v;
	float ome;
	float r;
	float th;
	float th_rad;
	uint8_t tur;
	uint16_t count;
}turnparameter;

typedef struct{
	float r_Threadhold;
	float l_Threadhold;
	float r_ref;
	float l_ref;//真ん中に置いた時の値
	float r_diff;
	float l_diff;
}wallcontrolparameter;

extern traaccelerationparameter g_traAcceleration;
extern turnparameter g_turn;
extern wallcontrolparameter g_wallControl;
extern float control;

void Traacc(void);
void turn(void);
void wallControl(void);
void goAhead(void);
void turnLeft(void);
void turnRight(void);
void goBack(void);

#endif /* MOVE_H_ */
