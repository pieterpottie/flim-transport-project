/*
 * StepperMotor.h
 *
 *  Created on: 2012-07-16
 *      Author: anderson
 */

#include "AccelStepper.h"

#ifndef STEPPERMOTOR_H_
#define STEPPERMOTOR_H_

class StepperMotor: public AccelStepper
{
public:
	StepperMotor(uint8_t pins, uint8_t pin1, uint8_t pin2, uint8_t pin3,uint8_t pin4);
	void advanceFrame(int frameLength);
	void reverseFrame(int speed);
};


#endif /* STEPPERMOTOR_H_ */
