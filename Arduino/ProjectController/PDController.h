/*
 * pdController.h
 *
 *  Created on: 2012-07-13
 *      Author: anderson
 */

#ifndef PDCONTROLLER_H_
#define PDCONTROLLER_H_

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

	PDController(double sampleTime);
	void compute(double analogInput);
	void setTunings(double Kp, double Kd);
	void setSampleTime(int newSampleTime);
	void setOutputLimits(double Min, double Max);
	void outputSerial(int num, double input, double output );
};

	void PDController_setSampleTime(uint16_t sampleTime);
	void PDController_init(uint16_t sampleTime);



#endif /* PDCONTROLLER_H_ */
