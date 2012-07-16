#include "PDController.h"

PDController::PDController(double sampleTime)
{
	this->sampleTime = sampleTime;
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

   if(output > outMax) output = outMax;
   else if(output < outMin) output = outMin;

}

void PDController::outputSerial(int num, double input, double output )
{
	Serial.print("Pot");
	Serial.print(num);
	Serial.print(": ");
	Serial.print(input);
	Serial.print(" Motor: ");
	Serial.println(output);
}

void PDController_setSampleTime(uint16_t sampleTime)
{
	/*formula in terms of ms: OCR1A = (SampleTime * 16MHz) / 256*/
	OCR1A = (sampleTime*63);         // approximation

}

void PDController_init(uint16_t sampleTime)
{
	/*setup timer*/
	  cli();           // disable all interrupts
	  TCCR1A = 0;
	  TCCR1B = 0;
	  TCNT1  = 0;


	  PDController_setSampleTime(sampleTime);
	  TCCR1B |= (1 << WGM12);   // CTC mode
	  TCCR1B |= (1 << CS12);    // 256 prescaler
	  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
	  sei();             		// enable all interrupts
}




