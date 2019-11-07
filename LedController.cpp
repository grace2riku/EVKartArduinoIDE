#include "stdafx.h"
#include "LedController.h"

LedController::LedController(int pin) {
	m_ledPin = pin;
	pinMode(m_ledPin, OUTPUT);
}


void LedController::on(void) {
	digitalWrite(m_ledPin, HIGH);
}


void LedController::off(void) {
	digitalWrite(m_ledPin, LOW);
}
