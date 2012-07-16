#include <Arduino.h>
#include "PDController.h"

PDController testController(250);

void setup()   {
	/*start serial communication*/
	Serial.begin(9600);

	/*Initialise parameters*/
	testController.Setpoint = 200;
	testController.setTunings(0.10,0.005);
	testController.setOutputLimits(-255,0);

	/*setup timer*/
	  cli();           // disable all interrupts
	  TCCR1A = 0;
	  TCCR1B = 0;
	  TCNT1  = 0;

	  /*formula in terms of ms: OCR1A = (SampleTime * 16MHz) / 256*/
	  OCR1A = 15625;            // compare match register 16MHz/256/2Hz
	  TCCR1B |= (1 << WGM12);   // CTC mode
	  TCCR1B |= (1 << CS12);    // 256 prescaler
	  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
	  sei();             		// enable all interrupts
}

void loop()
{
	/*compute output*/

}

ISR(TIMER1_COMPA_vect)        // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	/*compute output*/

	testController.Input = analogRead(2);
	testController.compute();
	Serial.print("Pot: ");
	Serial.print(testController.Input);
	Serial.print(" Motor: ");
	Serial.println(testController.Output);
}

int main(void) {

  init();
  setup();

  while(true) {
    loop();
  }
}
