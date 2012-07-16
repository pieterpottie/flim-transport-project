/*
 * DCMotor.cpp
 *
 *  Created on: 2012-07-15
 *      Author: Andrew
 */
#include "DCMotor.h"

DCMotor::DCMotor(int pin)
{
	this->pin = pin;
	pinMode(pin,OUTPUT);
}

void DCMotor::setMotorspeed(int speed)
{
	SoftPWMSet(this->pin, speed);
}

void DCMotor_inti()
{
	  SoftPWMBegin();	// Initialize soft PWM
}



