/*
 * LCD.h
 *
 *  Created on: 2012-07-15
 *      Author: anderson
 */

#ifndef LCD_H_
#define LCD_H_

#include <string.h>
#include "LiquidCrystal.h"

class LCD
{
private:
	LiquidCrystal *lcd;  //in order: RS,enable,D4,D5,D6,D7
public:
	LCD(uint8_t rs, uint8_t enable,uint8_t d4, uint8_t d5,
			uint8_t d6, uint8_t d7, uint8_t cols, uint8_t rows);
	void trace(String message);
	void updateLCD(String mode, int frames);
};

#endif /* LCD_H_ */
