/*
 * aqm1248a.h
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */

#ifndef AQM1248A_H_
#define AQM1248A_H_


#include "myassign.h"
#include <stdint.h>

enum AQM1248A { //Register Select State
	RS_OFF = LOW, RS_ON = HIGH
};

enum BACKGROUND { //Background Color
	WHITE = 0, BLACK = 1
};

//Initialize AQM1248A, LCD
void initAQM1248A(void);
//Write LCD Driver by SPI Tx
uint8_t spiWriteAQM1248A(uint8_t txData, uint8_t rs);
//Reset LCD Display
void displayReset(void);

//Print A Big Fonts on Display
void bigFont(uint8_t charCode, uint8_t row, uint8_t column, uint8_t contrast);
//Print String on Display
void printLCDString(uint8_t row, uint8_t column, uint8_t contrast, char *string);
//Print Format on Display
void printfLCD(uint8_t row, uint8_t column, uint8_t contrast, const char* fmt,
		...);

//Print Graph Test on Display
void drawGraph(void);
//Print Graph And String Test on Display
void drawGraphAndString(void);
#endif /* AQM1248A_H_ */
