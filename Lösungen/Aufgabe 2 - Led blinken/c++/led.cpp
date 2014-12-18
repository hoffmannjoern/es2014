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

void Led::off()
{
        digitalWrite(LED_PIN,LOW);
}

void Led::blink(int time)
{
		on();
		delay(time);
		off();
		delay(time);
}