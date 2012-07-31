/*
 * DCMotor.h
 *
 *  Created on: 2012-07-15
 *      Author: anderson
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include <Arduino.h>
#include "SoftPWM.h"

class DCMotor
{
private:
	int pwm_pin;
	int dir_pin;
	bool enable;

public:
	DCMotor(int pwm_pin, int dir_pin);
	void setMotorspeed(int speed);
	void stop();
};

void DCMotor_inti();


#endif /* DCMOTOR_H_ */
