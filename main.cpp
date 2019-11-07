#include "stdafx.h"
#include "LedController.h"

LedController uHallSensorLED = LedController(23);
LedController vHallSensorLED = LedController(25);
LedController wHallSensorLED = LedController(27);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
	uHallSensorLED.on();
	vHallSensorLED.on();
	wHallSensorLED.on();
	
	delay(500);
	
	uHallSensorLED.off();
	vHallSensorLED.off();
	wHallSensorLED.off();

	delay(500);
}
