#include <Arduino.h>
#include <math.h>
#include "LCD.h"
#include "DCMotor.h"
#include "PDController.h"
#include "StepperMotor.h"

#define LEFT_MOTOR_PIN			17
#define RIGHT_MOTOR_PIN			18
#define MAX_STEPPER_SPEED		500
#define ACCELERATION			200
#define FRAMESIZE 				400

PDController *leftPDController;
PDController *rightPDController;
LCD 		 *lcd;
DCMotor		 *leftMotor;
DCMotor		 *rightMotor;
StepperMotor *myStepper;

uint16_t frameCount = 0;

void setup()
{
	/*start serial communication for debugging*/
	Serial.begin(9600);
	delay(100);

	/*Initialise LCD*/
	Serial.println("Initialise LCD");
	lcd = new LCD(12,11,5,4,3,2,16,2);	//in order: RS,enable,D4,D5,D6,D7,columns,rows
	delay(100);

	/*Initialise Soft PWM for DC motors*/
	Serial.println("Initialise PWM");
	DCMotor_inti();
	delay(100);

	/*Initialise DC Motor*/
	Serial.println("Initialise DC motor");
	leftMotor = new DCMotor(LEFT_MOTOR_PIN);
	rightMotor = new DCMotor(RIGHT_MOTOR_PIN);
	delay(100);

	/*Initialise Stepper Motor*/
	Serial.println("Initialise stepper motor");
	myStepper = new StepperMotor(4,8,9,6,7);
	myStepper->setMaxSpeed(MAX_STEPPER_SPEED);
	myStepper->setAcceleration(ACCELERATION);
	delay(100);

	/*Initialise left PD Controller parameters*/
	Serial.println("Initialise left PDC");
	leftPDController = new PDController();
	leftPDController->setpoint = 200; 					//desired pot value
	leftPDController->setTunings(0.40,0.05);				//set Kp and Kd values
	leftPDController->setOutputLimits(-255,0);			//set the output limits
	delay(100);

	/*Initialise right PD Controller parameters*/
	Serial.println("Initialise right PDC");
	rightPDController = new PDController();
	rightPDController->setpoint = 200; 					//desired pot value
	rightPDController->setTunings(0.40,0.05);				//set Kp and Kd values
	rightPDController->setOutputLimits(-255,0);			//set the output limits
	delay(100);

	/*Initialise timer1 for the PD Controllers*/
	Serial.println("Initialise PD timer");
	PDController_init();
	delay(100);
}


// interrupt timer routine for the PD Controllers
ISR(TIMER1_COMPA_vect)
{
	/*compute output*/
	leftPDController->compute(analogRead(1));
	rightPDController->compute(analogRead(2));

	leftMotor->setMotorspeed(fabs(leftPDController->output));
	rightMotor->setMotorspeed(fabs(rightPDController->output));

	Serial.print(leftPDController->input);
	Serial.print(" ");
	Serial.println(rightPDController->input);
}

void setFilmPos()
{
	lcd->trace("Set Film Pos");

	//TODO: replace this with a button presses
	//replace with user control to align the film

	myStepper->reverseFrame(-500);

	while(1)
	{
		myStepper->runSpeed();
	}

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

	//setFilmPos();

	lcd->updateLCD(0, 0, 0, 0);			//display 0

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
