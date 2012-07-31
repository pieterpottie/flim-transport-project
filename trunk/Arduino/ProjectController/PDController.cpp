#include "PDController.h"

PDController::PDController()
{
	this->sampleTime = 250;
}

void PDController::compute(double analogInput)
{
	input = analogInput;

	/*Compute all the working error variables*/
	double error = setpoint - input;
	double dInput = (input - lastInput);

	/*Compute PID Output*/
	output = kp * error + kd * dInput;

	if(output > outMax) output = outMax;
	else if(output < outMin) output = outMin;

	/*Remember the input for next time*/
	lastInput = input;
}

void PDController::autoTune(double upper, double lower)
{
	if (input > upper && kp > KP_MIN)
		kp -= KP_AUTO;
	else if (input < lower && kp < KP_MAX)
		kp += KP_AUTO;
}

void PDController::setTunings(double Kp, double Kd)
{
	double sampleTimeInSec = ((double)sampleTime)/1000;
	kp = Kp;
	kd = Kd/ sampleTimeInSec;
}

void PDController::setOutputLimits(double Min, double Max)
{
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;

   if(output > outMax) output = outMax;
   else if(output < outMin) output = outMin;

}

void PDController_init()
{
	/*setup timer*/
	  cli();           // disable all interrupts
	  TCCR1A = 0;
	  TCCR1B = 0;
	  TCNT1  = 0;


	  OCR1A = 15625;
	  TCCR1B |= (1 << WGM12);   // CTC mode
	  TCCR1B |= (1 << CS12);    // 256 prescaler
	  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
	  sei();             		// enable all interrupts
}




