/*
 * aqm1248a.c
 *
 *  Created on: Sep 20, 2019
 *      Author: kanako
 */



#include "stm32f3xx_hal.h"
#include "spi.h"
#include "gpio.h"

#include "aqm1248a.h"
#include "font.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void initAQM1248A(void) {

	lcdCS(HIGH);
	lcdRS(LOW);

	HAL_Delay(3);
	spiWriteAQM1248A(0xAE, RS_OFF); //Display = OFF
	spiWriteAQM1248A(0xA0, RS_OFF); //ADC = normal
	spiWriteAQM1248A(0xC8, RS_OFF); //Common output = reverse
	spiWriteAQM1248A(0xA3, RS_OFF); //bias = 1/7

	HAL_Delay(3);
	spiWriteAQM1248A(0x2C, RS_OFF); //power control 1
	HAL_Delay(3);
	spiWriteAQM1248A(0x2E, RS_OFF); //power control 2
	HAL_Delay(3);
	spiWriteAQM1248A(0x2F, RS_OFF); //power control 3

	HAL_Delay(3);
	spiWriteAQM1248A(0x23, RS_OFF); //Vo voltage resistor ratio set
	spiWriteAQM1248A(0x81, RS_OFF); //Electronic volume mode set
	spiWriteAQM1248A(0x1C, RS_OFF); //Electronic volume value set

	HAL_Delay(3);
	spiWriteAQM1248A(0xA4, RS_OFF); //display all point = normal�i�S�_�����Ȃ��j
	spiWriteAQM1248A(0x40, RS_OFF); //display start line = 0
	spiWriteAQM1248A(0xA6, RS_OFF); //Display normal/revers = normal(�������]���Ȃ��j
	spiWriteAQM1248A(0xAF, RS_OFF); //Display = ON

	HAL_Delay(10);
	displayReset();

}

uint8_t spiWriteAQM1248A(uint8_t txData, uint8_t rs) {

	uint8_t txDataAQM1248A;
	signed int error;

	txDataAQM1248A = txData;

	lcdRS(rs);
	lcdCS(LOW);
	error = HAL_SPI_Transmit(&hspi1, (uint8_t *) &txDataAQM1248A, 1, 1000);
	lcdCS(HIGH);

	lcdRS(RS_OFF);

	return error;
}

void displayReset(void) {

	uint8_t pageAddress, columnAddress;

	for (pageAddress = 0; pageAddress < 6; pageAddress++) {
		spiWriteAQM1248A((0xB0 | pageAddress), RS_OFF);
		spiWriteAQM1248A(0x10, RS_OFF);
		spiWriteAQM1248A(0x00, RS_OFF);
		for (columnAddress = 0; columnAddress < 132; columnAddress++) {
			spiWriteAQM1248A(0x00, RS_ON);
		}
	}

}

void bigFont(uint8_t charCode, uint8_t row, uint8_t column, uint8_t contrast) {

	unsigned char startColum;
	unsigned char charCodeH, charCodeL;
	unsigned char txData;
	int i;

	startColum = column * 11;

	spiWriteAQM1248A((0xB0 | (row * 2)), RS_OFF);

	spiWriteAQM1248A((0x10 | ((startColum & 0xF0) >> 4)), RS_OFF); //���4bit
	spiWriteAQM1248A((0x00 | (startColum & 0x0F)), RS_OFF); //����4bit

	for (i = 0; i < 5; i++) {
		charCodeL = (g_Font[charCode][i] & 0x0F);
		if (contrast == 1) {
			charCodeL = ~charCodeL;
		}
		txData = 0;
		if ((charCodeL & 0x01) == 0x01) {
			txData = (txData | 0x03);
		}
		if ((charCodeL & 0x02) == 0x02) {
			txData = (txData | 0x0C);
		}
		if ((charCodeL & 0x04) == 0x04) {
			txData = (txData | 0x30);
		}
		if ((charCodeL & 0x08) == 0x08) {
			txData = (txData | 0xC0);
		}

		spiWriteAQM1248A(txData, RS_ON);
		spiWriteAQM1248A(txData, RS_ON);

	}
	if (contrast == 1) {
		spiWriteAQM1248A(0xFF, RS_ON);
	} else {
		spiWriteAQM1248A(0x00, RS_ON);
	}

	spiWriteAQM1248A((0xB0 | ((row * 2) + 1)), RS_OFF);

	spiWriteAQM1248A((0x10 | ((startColum & 0xF0) >> 4)), RS_OFF); //���4bit
	spiWriteAQM1248A((0x00 | (startColum & 0x0F)), RS_OFF); //����4bit

	for (i = 0; i < 5; i++) {
		charCodeH = ((g_Font[charCode][i] & 0xF0) >> 4);
		if (contrast == 1) {
			charCodeH = ~charCodeH;
		}
		txData = 0;
		if ((charCodeH & 0x01) == 0x01) {
			txData = (txData | 0x03);
		}
		if ((charCodeH & 0x02) == 0x02) {
			txData = (txData | 0x0C);
		}
		if ((charCodeH & 0x04) == 0x04) {
			txData = (txData | 0x30);
		}
		if ((charCodeH & 0x08) == 0x08) {
			txData = (txData | 0xC0);
		}

		spiWriteAQM1248A(txData, RS_ON);
		spiWriteAQM1248A(txData, RS_ON);

	}

	if (contrast == 1) {
		spiWriteAQM1248A(0xFF, RS_ON);
	} else {
		spiWriteAQM1248A(0x00, RS_ON);
	}
}

void printLCDString(uint8_t row, uint8_t column, uint8_t contrast,
		char *string) {
	int i;
	i = 0;

	while (string[i] != 0) {
		bigFont(string[i] - 0x20, row + (column + i) / 11, (column + i) % 11,
				contrast);
		i++;
		if (row + (column + i) / 11 >= 3) {
			return;
		}
	}
}

void printfLCD(uint8_t row, uint8_t column, uint8_t contrast, const char* fmt,
		...) {

	va_list list;
	char buffer[1024];

	va_start(list, fmt);

	vsprintf(buffer, fmt, list);

	printLCDString(row, column, contrast, buffer);

	va_end(list);

}

void drawcat(void) {
	uint8_t pageAddress, columnAddress;

	for (pageAddress = 0; pageAddress < 6; pageAddress++) {
		spiWriteAQM1248A((0xB0 | pageAddress), RS_OFF);
		spiWriteAQM1248A(0x10, RS_OFF);
		spiWriteAQM1248A(0x00, RS_OFF);
		for (columnAddress = 0; columnAddress < 128; columnAddress++) {
			spiWriteAQM1248A(g_Cat[pageAddress][columnAddress], RS_ON);
		}
	}

	printfLCD(1, 6, WHITE, "NYA");

}




