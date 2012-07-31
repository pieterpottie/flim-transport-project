#include <Arduino.h>
#include <avr/sleep.h>
#include <math.h>
#include "LCD.h"
#include "DCMotor.h"
#include "PDController.h"
#include "StepperMotor.h"

#define TRIGGER_PIN					10
#define SWITCH_PIN					13
#define LEFT_MOTOR_PIN_PWM			17
#define LEFT_MOTOR_PIN_DIR			14
#define RIGHT_MOTOR_PIN_PWM			18
#define RIGHT_MOTOR_PIN_DIR			19
#define MAX_STEPPER_SPEED			3000
#define ACCELERATION				500
#define FRAMESIZE 					400
#define NO_TENSION_THRESHOLD 		10   		//POT value to indicate no tension
#define TENSION_THRESHOLD 			120   		//POT value to indicate too much tension
#define SHUTDOWN_LIMIT 				2000	 	//Wait max 30 seconds
#define STOP_MOTOR_LIMIT 			2000	 	//Wait max 2 seconds

PDController *leftPDController;
PDController *rightPDController;
LCD 		 *lcd;
DCMotor		 *leftMotor;
DCMotor		 *rightMotor;
StepperMotor *myStepper;

uint16_t frameCount = 0;
uint16_t rightPotStallTime = 0;
uint16_t rightPotStallTime2 = 0;
uint16_t leftPotStallTime = 0;

bool inOperationMode = false;

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
	leftMotor = new DCMotor(LEFT_MOTOR_PIN_PWM, LEFT_MOTOR_PIN_DIR);
	rightMotor = new DCMotor(RIGHT_MOTOR_PIN_PWM, RIGHT_MOTOR_PIN_DIR);
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
	leftPDController->setpoint = 60; 					//desired pot value
	leftPDController->setTunings(4.7,0.005);				//set Kp and Kd values
	leftPDController->setOutputLimits(-255,255);			//set the output limits
	delay(100);

	/*Initialise right PD Controller parameters*/
	Serial.println("Initialise right PDC");
	rightPDController = new PDController();
	rightPDController->setpoint = 60; 					//desired pot value
	rightPDController->setTunings(3.0,0.005);				//set Kp and Kd values
	rightPDController->setOutputLimits(-255,255);			//set the output limits
	delay(100);

	/*Initialise timer1 for the PD Controllers*/
	Serial.println("Initialise PD timer");
	PDController_init();
	delay(100);

	/*Trigger pin*/
	pinMode(TRIGGER_PIN,OUTPUT);
	digitalWrite(TRIGGER_PIN, LOW);

	/*finally initialise the switch pin*/
	pinMode(SWITCH_PIN,INPUT);
}

void checkMotorStop()
{
	/* stops the right motor if no right tension is detected*/
	if(rightPDController->input < NO_TENSION_THRESHOLD)
	{
		if(rightPotStallTime > STOP_MOTOR_LIMIT)
			rightMotor->stop();
		rightPotStallTime += rightPDController->sampleTime;
	}
	else
		rightPotStallTime = 0;
}

void shutdown()
{
	leftMotor->stop();
	rightMotor->stop();
	digitalWrite(TRIGGER_PIN, LOW);
	sleep_enable();
	sleep_mode();
}

void checkStopFilm()
{
	/*stop the entire system if no right tension is detected*/
	if(rightPDController->input < NO_TENSION_THRESHOLD)
	{
		if(rightPotStallTime > SHUTDOWN_LIMIT)
			shutdown();
		rightPotStallTime += leftPDController->sampleTime;
	}
	else
		rightPotStallTime = 0;

	/*stop the entire system if too much tension is detected*/
	if(rightPDController->input > TENSION_THRESHOLD)
	{
		if(rightPotStallTime2 > SHUTDOWN_LIMIT)
			shutdown();
		rightPotStallTime2 += rightPDController->sampleTime;
	}
	else
		rightPotStallTime2 = 0;
}

// interrupt timer routine for the PD Controllers
ISR(TIMER1_COMPA_vect)
{
	/*compute output*/
	leftPDController->compute(analogRead(1));
	rightPDController->compute(analogRead(2));

	leftMotor->setMotorspeed(-leftPDController->output);
	rightMotor->setMotorspeed(rightPDController->output);

	Serial.println(leftPDController->input);

	if(inOperationMode)
	{
		//checkMotorStop();
		checkStopFilm();
	}

}

void checkManualMode(){

	if (!digitalRead(SWITCH_PIN))
	{
		lcd->updateLCD("Manual", 0);

		inOperationMode = false;
		while(!digitalRead(SWITCH_PIN))
		{
			/*in manual mode*/
			myStepper->setSpeed(5);
			myStepper->runSpeed();
		}
		//return to operation mode
		myStepper->advanceFrame(FRAMESIZE);
		frameCount = 0;
		lcd->updateLCD("Operation", 0);
	}

	inOperationMode = true;
}

int main(void)
{

	init();
	setup();

	checkManualMode();
	lcd->updateLCD("Operation", 0);

	for (;;)
	{
		digitalWrite(TRIGGER_PIN,HIGH);

		myStepper->advanceFrame(FRAMESIZE);
		while(myStepper->run())					//run till frame is complete
			checkManualMode();

		digitalWrite(TRIGGER_PIN,LOW);

		delay(2000); 							//wait for camera capture
		frameCount++;							//increment frame count
		lcd->updateLCD("Operation", frameCount);	//update LCD
	}
	return 0;
}
