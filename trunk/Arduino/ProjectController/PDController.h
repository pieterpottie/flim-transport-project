/*
 * pdController.h
 *
 *  Created on: 2012-07-13
 *      Author: anderson
 */

#ifndef PDCONTROLLER_H_
#define PDCONTROLLER_H_

#define KP_MAX	200.0
#define KP_MIN 0.01
#define KP_AUTO 0.1

#include <Arduino.h>

class PDController
{
public:
	/*working variables*/
	double input, output, setpoint;
	double lastInput;
	double kp, kd;
	int sampleTime;
	double outMin, outMax;

	PDController();
	void compute(double analogInput);
	void autoTune(double upper, double lower);
	void setTunings(double Kp, double Kd);
	void setOutputLimits(double Min, double Max);
};

	void PDController_init();



#endif /* PDCONTROLLER_H_ */
