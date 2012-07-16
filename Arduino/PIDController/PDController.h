/*
 * pdController.h
 *
 *  Created on: 2012-07-13
 *      Author: anderson
 */

#ifndef PDCONTROLLER_H_
#define PDCONTROLLER_H_

#include <Arduino.h>

class PDController{

public:
	/*working variables*/
	double Input, Output, Setpoint;
	double lastInput;
	double kp, kd;
	int sampleTime;
	double outMin, outMax;

	PDController(double sampleTime);
	void compute();
	void setTunings(double Kp, double Kd);
	void setSampleTime(int newSampleTime);
	void setOutputLimits(double Min, double Max);
};



#endif /* PDCONTROLLER_H_ */
