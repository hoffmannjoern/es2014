#include "LED.h"

const byte LED_PIN = 13;

//Setup
Led::Led()
{
		pinMode(LED_PIN, OUTPUT);
}
 
//Destruktor
Led::~Led(){}
 

//Led einschalten
void Led::on()
{
        digitalWrite(LED_PIN,HIGH);
}
