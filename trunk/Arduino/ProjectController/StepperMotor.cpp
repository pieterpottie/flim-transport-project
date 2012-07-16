/*
 * StepperMotor.cpp
 *
 *  Created on: 2012-07-16
 *      Author: anderson
 */
#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t pins, uint8_t pin1, uint8_t pin2) : AccelStepper(pins, pin1, pin2)
{
	//constructor
}

void StepperMotor::advanceFrame(int frameLength)
{
	this->moveTo(this->currentPosition()+frameLength);
}

void StepperMotor::reverseFrame(int speed)
{
	this->setSpeed(speed);
}



