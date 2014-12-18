#include "LED.h"

const byte LED_PIN = 13;
const byte BUTTON_PIN = 2

//Setup
Led::Led()
{
		pinMode(LED_PIN, OUTPUT);
		pinMode(BUTTON_PIN, INPUT);		
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

int readButtonState()
{
		int buttonState = digitalRead(BUTTON_PIN);
		
		//Entprellung
		if (buttonState != lastButtonState)
		{
			lastButtonState = buttonState;
			delay(10);
		}
		
		return buttonState;
}