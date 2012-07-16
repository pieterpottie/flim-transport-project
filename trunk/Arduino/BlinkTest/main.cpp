#include <Arduino.h>


// The setup() method runs once, when the sketch startsgtk
void setup()   {
  Serial.begin(9600);
}

// the loop() method runs over and over again,
// as long as the Arduino has power

void loop()
{
	Serial.println(analogRead(2));
	delay(250);
}


int main(void) {

  init();
  setup();

  while(true) {
    loop();
  }
}
