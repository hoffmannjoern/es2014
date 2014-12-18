#include "LED.h"

const byte LED_PIN = 13;
const byte ANALOG_PIN = 1;

//Setup
Led::Led()
{
		pinMode(LED_PIN, OUTPUT);
		pinMode(ANALOG_PIN, INPUT);
}
 
//Destruktor
Led::~Led(){}
 

void changeLedValue( int sensorValue)
{
		//PWM + Konvertierung zu Skala 0-255
		analogWrite(ledPin, sensorValue / 4); 
}