#include "PDController.h"

PDController::PDController(double sampleTime)
{
	this->sampleTime = sampleTime;
}

void PDController::compute()
{

   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   double dInput = (Input - lastInput);

   /*Compute PID Output*/
   Output = kp * error + kd * dInput;

   if(Output > outMax) Output = outMax;
   else if(Output < outMin) Output = outMin;

   /*Remember the input for next time*/
   lastInput = Input;
}

void PDController::setTunings(double Kp, double Kd)
{
	double sampleTimeInSec = ((double)sampleTime)/1000;
	kp = Kp;
	kd = Kd/ sampleTimeInSec;
}


void PDController::setSampleTime(int newSampleTime)
{
   /*set new sample time during operation*/
   if (newSampleTime > 0)
   {
	  double ratio  = (double)newSampleTime
					  / (double)sampleTime;
	  kd /= ratio;
	  sampleTime = (unsigned long)newSampleTime;
   }
}

void PDController::setOutputLimits(double Min, double Max)
{
   if(Min > Max) return;
   outMin = Min;
   outMax = Max;

   if(Output > outMax) Output = outMax;
   else if(Output < outMin) Output = outMin;

}


