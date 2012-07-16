/*
 * LCD.cpp
 *
 *  Created on: 2012-07-15
 *      Author: Andrew
 */

#include "LCD.h"


LCD::LCD(uint8_t rs, uint8_t enable,uint8_t d4, uint8_t d5,
			uint8_t d6, uint8_t d7, uint8_t cols, uint8_t rows)
{
	lcd = new LiquidCrystal(rs,enable,d4,d5,d6,d7);
	lcd->begin(cols, rows); 	// need to specify how many columns and rows are in the LCD unit
	lcd->clear();      			// this clears the LCD. You can use this at any time
}

void LCD::trace(String message)
{
	lcd->clear();
	lcd->setCursor(0,0);
	lcd->print(message);
}

void LCD::updateLCD(int maxStepperSpeed, int numberOfFrames,
		int tension, int systemState){

	lcd->clear();

	lcd->setCursor(0,0); // positions starting point on LCD, column 0, row 0 (that is, the top left of our LCD)
	lcd->print("tenU:");
	lcd->print(maxStepperSpeed);

	lcd->setCursor(9,0);
	lcd->print("Frm:");
	lcd->print(numberOfFrames);

	lcd->setCursor(0,1); // positions starting point on LCD, column 0, row 1 (that is, the bottom left of our LCD)
	lcd->print("TenO:");
	lcd->print(tension);

	lcd->setCursor(9,1);
	lcd->print("st:");
	lcd->print(systemState);

}




