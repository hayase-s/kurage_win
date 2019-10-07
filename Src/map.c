/*
 * map.c
 *
 *  Created on: Sep 26, 2019
 *      Author: kanako
 */

#include "map.h"
#include "AD.h"
#include "gpio.h"
#include "myassign.h"

locparameter g_location;
wallThresholdparameter g_WallThreshold;
uint16_t g_WallEW[17];
uint16_t g_WallSN[17];
unsigned char g_stepNumber[16][16];

void initWall(void) {
//東西
	g_WallEW[0] = 0xffff;
	for (int i = 1; i < 16; i++) {
		g_WallEW[i] = 0x0000;
	}
	g_WallEW[16] = 0xffff;

//南北
	g_WallSN[0] = 0xffff;
	g_WallSN[1] = 0x0001;
	for (int i = 2; i < 16; i++) {
		g_WallSN[i] = 0x0000;
	}
	g_WallSN[16] = 0xffff;
} //壁情報初期化

void setWallBit(uint8_t X, uint8_t Y, uint8_t absDir) {
	if (absDir == 0) { //北壁を入れる
		g_WallEW[Y + 1] |= (1 << X);
	} else if (absDir == 1) { //西壁を入れる
		g_WallSN[X] |= (1 << Y);
	} else if (absDir == 2) { //南壁を入れる
		g_WallEW[Y] |= (1 << X);
	} else { //東壁を入れる
		g_WallSN[X + 1] |= (1 << Y);
	}
} //壁入れ関数

void setWalltoMap(void) {
	if (g_nowWallSensorValue.left > g_WallThreshold.left) { //左壁の有無
		setWallBit(g_location.x, g_location.y, (g_location.Direction + 1) % 4);
	}
	if (g_nowWallSensorValue.center > g_WallThreshold.center) { //前壁の有無
		setWallBit(g_location.x, g_location.y, g_location.Direction % 4);
	}
	if (g_nowWallSensorValue.right > g_WallThreshold.right) { //右壁の有無
		setWallBit(g_location.x, g_location.y, (g_location.Direction + 3) % 4);
	}
} //壁入れ指示

uint8_t judgeWall(uint8_t X, uint8_t Y, uint8_t absDir) {
	if (absDir == 0) { //北壁
		return (g_WallEW[Y + 1] >> X) & 1;
	} else if (absDir == 1) { //西壁
		return (g_WallSN[X] >> Y) & 1;
	} else if (absDir == 2) { //南壁
		return (g_WallEW[Y] >> X) & 1;
	} else { //東壁
		return (g_WallSN[X + 1] >> Y) & 1;
	}
} //壁の有無を判断

void printWall(void) {
	printf("\r \e[0m\e[1mMAP \n\r");
	for (int i = 15; i >= 0; i--) {
		for (int j = 0; j <= 15; j++) { //Y=iの時の北壁
			if (judgeWall(j, i, 0) == 1) {
				printf("\e[33m -----");
			} else {
				printf("\e[30m -----");
			}
		}
		printf("\r\n");
		for (int j = 0; j <= 15; j++) { //Y=iの時の西壁
			if (judgeWall(j, i, 1) == 1) {
				if (g_stepNumber[j][i] < 10) { //一桁なら
					printf("\e[33m|  \e[30m%d  ", g_stepNumber[j][i]);
				} else if (g_stepNumber[j][i] < 100) { //二桁なら
					printf("\e[33m|  \e[30m%d ", g_stepNumber[j][i]);
				} else { //三桁なら
					printf("\e[33m| \e[30m%d ", g_stepNumber[j][i]);
				}
			} else {
				if (g_stepNumber[j][i] < 10) { //一桁なら
					printf("\e[30m|  \e[30m%d  ", g_stepNumber[j][i]);
				} else if (g_stepNumber[j][i] < 100) { //二桁なら
					printf("\e[30m|  \e[30m%d ", g_stepNumber[j][i]);
				} else { //三桁なら
					printf("\e[30m| \e[30m%d ", g_stepNumber[j][i]);
				}
			}
		}
		if (judgeWall(15, i, 3) == 1) { //X=15,Y=iの時の東壁
			printf("\e[33m|");
		} else {
			printf("\e[30m|");
		}
		printf("\n\r");

	}
	printf("\r");
	for (int j = 0; j <= 15; j++) { //Y=0の時の南壁---
		if (judgeWall(j, 0, 2) == 1) {
			printf("\e[33m -----");
		} else {

		}
	}
	printf("\n");
} //壁情報吐き出し

void initStepMap(void) {
	for (uint8_t i = 0; i < 16; i++) {
		for (uint8_t j = 0; j < 16; j++) {
			g_stepNumber[i][j] = 255;
		}
	}

} //歩数マップ初期化

void StepMapforAdachi(void) {
	uint8_t x_map;
	uint8_t y_map;
	g_stepNumber[g_location.x_goal][g_location.y_goal] = 0;

	for (uint8_t k = 0; k < 256; k++) { //自分の今いる位置まで展開する
		if (g_stepNumber[g_location.x][g_location.y] != 255) {
			break;
		} else {
			for (uint8_t j = 0; j < 16; j++) {
				for (uint8_t i = 0; i < 16; i++) {
					if (g_stepNumber[i][j] == k) {
						x_map = i;
						y_map = j;
						if (judgeWall(x_map, y_map, 0) == 0) { //北壁がなければ
							if (g_stepNumber[x_map][y_map + 1] == 255) {
								g_stepNumber[x_map][y_map + 1] = k + 1;
							}
						}
						if (judgeWall(x_map, y_map, 1) == 0) { //西壁がなければ
							if (g_stepNumber[x_map - 1][y_map] == 255) {
								g_stepNumber[x_map - 1][y_map] = k + 1;
							}
						}
						if (judgeWall(x_map, y_map, 2) == 0) { //南壁がなければ
							if (g_stepNumber[x_map][y_map - 1] == 255) {
								g_stepNumber[x_map][y_map - 1] = k + 1;
							}
						}
						if (judgeWall(x_map, y_map, 3) == 0) { //東壁がなければ
							if (g_stepNumber[x_map + 1][y_map] == 255) {
								g_stepNumber[x_map + 1][y_map] = k + 1;
							}
						}
					}
				}
			}
		}
	}
}

uint8_t compareStep(uint8_t X, uint8_t Y, uint8_t absDir) {

	uint16_t front_StepNumber = 65535; //今向いてる方向の歩数
	uint16_t left_StepNumber = 65535; //今向いてる方向の左の歩数
	uint16_t right_StepNumber = 65535; //今向いてる方向の右の歩数
	uint8_t minStepNumberDir; //0=前に進む，1=左に進む，2=右に進む
	if (absDir % 4 == 0) { //北を向いていたら
		if (judgeWall(X, Y, 0) == 0) { //前壁がなければ
			front_StepNumber = g_stepNumber[X][Y + 1];
		} else {
			front_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 1) == 0) { //左壁がなければ
			if (X - 1 >= 0) {
				left_StepNumber = g_stepNumber[X - 1][Y];
			}
		} else {
			left_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 3) == 0) { //右壁がなければ
			right_StepNumber = g_stepNumber[X + 1][Y];
		} else {
			right_StepNumber = 65535;
		}
	} else if (absDir % 4 == 1) { //西を向いていたら
		if (judgeWall(X, Y, 1) == 0) { //前壁がなければ
			if (X - 1 >= 0) {
				front_StepNumber = g_stepNumber[X - 1][Y];
			}
		} else {
			front_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 2) == 0) { //左壁がなければ
			if (Y - 1 >= 0) {
				left_StepNumber = g_stepNumber[X][Y - 1];
			}
		} else {
			left_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 0) == 0) { //右壁がなければ
			right_StepNumber = g_stepNumber[X][Y + 1];
		} else {
			right_StepNumber = 65535;
		}
	} else if (absDir % 4 == 2) { //南を向いていたら
		if (judgeWall(X, Y, 2) == 0) { //前壁がなければ
			if (Y - 1 >= 0) {
				front_StepNumber = g_stepNumber[X][Y - 1];
			}
		} else {
			front_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 3) == 0) { //左壁がなければ
			left_StepNumber = g_stepNumber[X + 1][Y];
		} else {
			left_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 1) == 0) { //右壁がなければ
			if (X - 1 >= 0) {
				right_StepNumber = g_stepNumber[X - 1][Y];
			}
		} else {
			right_StepNumber = 65535;
		}
	} else { //東を向いていたら
		if (judgeWall(X, Y, 3) == 0) { //前壁がなければ
			front_StepNumber = g_stepNumber[X + 1][Y];
		} else {
			front_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 0) == 0) { //左壁がなければ
			left_StepNumber = g_stepNumber[X][Y + 1];
		} else {
			left_StepNumber = 65535;
		}
		if (judgeWall(X, Y, 2) == 0) { //右壁がなければ
			if (Y - 1 >= 0) {
				right_StepNumber = g_stepNumber[X][Y - 1];
			}
		} else {
			right_StepNumber = 65535;
		}
	}

	if (front_StepNumber < right_StepNumber
			&& front_StepNumber < left_StepNumber) { //前が一番小さい
		minStepNumberDir = 0;
	} else if (left_StepNumber < right_StepNumber
			&& left_StepNumber < front_StepNumber) { //左が一番小さい
		minStepNumberDir = 1;
	} else if (right_StepNumber < left_StepNumber
			&& right_StepNumber < front_StepNumber) { //右が一番小さい
		minStepNumberDir = 2;
	} else if (left_StepNumber == right_StepNumber
			&& left_StepNumber == front_StepNumber) { //全方向同じだった場合
		minStepNumberDir = 3;
	} else if (right_StepNumber == front_StepNumber) { //前と右が同じ
		minStepNumberDir = 4;
	} else if (left_StepNumber == front_StepNumber) { //前と左が同じ
		minStepNumberDir = 5;
	} else { //右と左が同じ
		minStepNumberDir = 6;
	}
	return minStepNumberDir;
}

void saveMapFlash(uint32_t addr) {

	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t PageError = 0;

	HAL_StatusTypeDef r;

	int i;
	const uint8_t MAZESIZEMAX = 17;

	//FLASH Unlock
	HAL_FLASH_Unlock();

	//Page Erase
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = addr;
	EraseInitStruct.NbPages = 1;

	r = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	if (r == HAL_OK) {
		printf("Page Erase OK\r\n");
	} else {
		HAL_FLASH_Lock();

		return;
	}

	printf("Write SN Wall\r\n");
	for (i = 0; i < MAZESIZEMAX; i++) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,
				(uint16_t) (addr + sizeof(uint16_t) * i),
				(uint16_t) g_WallSN[(i % MAZESIZEMAX)]);
	}

	printf("Write EW Wall\n");
	for (i = MAZESIZEMAX; i < 2 * MAZESIZEMAX; i++) {
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,
				(uint16_t) (addr + sizeof(uint16_t) * i),
				(uint16_t) g_WallEW[(i % MAZESIZEMAX)]);
	}

//FLASH Lock
	HAL_FLASH_Lock();

} //フラッシュに書き込み

void loadMapFlash(uint32_t addr) {
	uint32_t add;
	uint16_t* p;
	uint32_t i = 0;
	i = 0;
	for (add = addr; add < (addr + sizeof(g_WallSN)); add += 2) {
		p = (uint16_t*) add;
		g_WallSN[i] = *p;
		i++;  // add data pointer

	}
	i = 0;
	for (add = (addr + sizeof(g_WallSN)); add < (addr + 2 * sizeof(g_WallSN));
			add += 2) {
		p = (uint16_t*) add;
		g_WallEW[i] = *p;
		i++;  // add data pointer
	}
}  //フラッシュ読み出し

