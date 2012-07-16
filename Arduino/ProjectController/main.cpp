#include <Arduino.h>
#include <math.h>
#include "LCD.h"
#include "DCMotor.h"
#include "PDController.h"
#include "StepperMotor.h"

#define INIT_SAMPLE_RATE 		250 //50 ms per sample
#define LEFT_MOTOR_PIN			17
#define RIGHT_MOTOR_PIN			18
#define MAX_STEPPER_SPEED		500
#define ACCELERATION			200
#define FRAMESIZE 				400

PDController *testController;
LCD 		 *lcd;
DCMotor		 *leftMotor;
DCMotor		 *rightMotor;
StepperMotor *myStepper;

uint16_t frameCount = 0;

void setup()
{
	/*start serial communication for debugging*/
	Serial.begin(9600);

	/*Initialise LCD*/
	lcd = new LCD(12,11,5,4,3,2,16,2);	//in order: RS,enable,D4,D5,D6,D7,columns,rows

	/*Initialise Soft PWM for DC motors*/
	DCMotor_inti();

	/*Initialise DC Motor*/
	leftMotor = new DCMotor(LEFT_MOTOR_PIN);
	rightMotor = new DCMotor(RIGHT_MOTOR_PIN);

	/*Initialise timer1 for the PD Controllers*/
	PDController_init(INIT_SAMPLE_RATE);

	/*Initialise PD Controller parameters*/
	testController = new PDController(INIT_SAMPLE_RATE);
	testController->setpoint = 200; 					//desired pot value
	testController->setTunings(0.25,0.005);				//set Kp and Kd values
	testController->setOutputLimits(-255,0);			//set the output limits

	/*Initialise Stepper Motor*/
	myStepper = new StepperMotor(2,8,9);
	myStepper->setMaxSpeed(MAX_STEPPER_SPEED);
	myStepper->setAcceleration(ACCELERATION);
}


// interrupt timer routine for the PD Controllers
ISR(TIMER1_COMPA_vect)
{
	/*compute output*/
	testController->compute(analogRead(2));
	testController->outputSerial(1,testController->input, testController->output);
	leftMotor->setMotorspeed(fabs(testController->output));
	rightMotor->setMotorspeed(fabs(testController->output));
}

void setFilmPos()
{
	lcd->trace("Set Film Pos");

	//TODO: replace this with a button presses
	//replace with user control to align the film

	delay(3000);
	//myStepper->reverseFrame(-500);
}

void emergencyStop()
{
	//TODO: replace this with a button press
}

int main(void)
{

	init();
	setup();

	setFilmPos();

	lcd->updateLCD(0, 0 , 0, 0);			//display 0

	for (;;)
	{
		myStepper->advanceFrame(FRAMESIZE);
		while(myStepper->run()); 				//run till frame is complete
		frameCount++;							//increment frame count
		delay(1000); 							//wait for camera capture
		lcd->updateLCD(frameCount, 0 , 0, 0);
	}
	return 0;
}
