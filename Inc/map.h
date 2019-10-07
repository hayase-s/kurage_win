/*
 * map.h
 *
 *  Created on: Sep 26, 2019
 *      Author: kanako
 */

#ifndef MAP_H_
#define MAP_H_
#include <stdint.h>

typedef struct {
	uint8_t x_goal;
	uint8_t y_goal;
	uint8_t x;
	uint8_t y;
	uint8_t Direction; //N=0 W=1 S=2 E=3
	uint8_t absoluteDirection;
} locparameter;

typedef struct{
	uint16_t center;
	uint16_t right;
	uint16_t left;
} wallThresholdparameter;

extern wallThresholdparameter g_WallThreshold;
extern locparameter g_location;

extern uint16_t g_WallEW[17];
extern uint16_t g_WallSN[17];
extern unsigned char g_stepNumber[16][16];

void initWall(void);
void setWallBit(uint8_t X, uint8_t Y, uint8_t absDir);
void setWalltoMap(void);
uint8_t judgeWall(uint8_t X, uint8_t Y, uint8_t absDir);
void printWall(void);
void saveMapFlash(uint32_t addr);
void loadMapFlash(uint32_t addr);
void initStepMap(void);
void StepMapforAdachi(void);
uint8_t compareStep(uint8_t X, uint8_t Y, uint8_t absDir);


#endif /* MAP_H_ */
