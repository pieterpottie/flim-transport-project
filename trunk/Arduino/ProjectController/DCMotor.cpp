/*
 * DCMotor.cpp
 *
 *  Created on: 2012-07-15
 *      Author: Andrew
 */
#include "DCMotor.h"

#define CLOCKWISE LOW
#define COUNTER_CLOCKWISE HIGH

DCMotor::DCMotor(int pwm_pin, int dir_pin)
{
	/*set pins to high to prevent motion*/
	this->pwm_pin = pwm_pin;
	pinMode(pwm_pin,OUTPUT);
	digitalWrite(pwm_pin,HIGH);

	this->dir_pin = dir_pin;
	pinMode(dir_pin,OUTPUT);
	digitalWrite(dir_pin,HIGH);

	this->enable = true;

}

void DCMotor::stop()
{
	/*stop the motor from running*/
	SoftPWMEnd(this->pwm_pin);
	digitalWrite(this->pwm_pin,HIGH);
	digitalWrite(this->dir_pin,HIGH);
	this->enable = false;
}

void DCMotor::setMotorspeed(int speed)
{
	if(this->enable)
	{
		/* set speed based on direction*/
		if (speed >= 0)
		{
			digitalWrite(dir_pin,CLOCKWISE);
			SoftPWMSet(this->pwm_pin, speed);
		}
		else
		{
			digitalWrite(dir_pin,COUNTER_CLOCKWISE);
			SoftPWMSet(this->pwm_pin, 0xFF + speed);
		}
	}
}

void DCMotor_inti()
{
	  SoftPWMBegin();	// Initialize soft PWM
}



