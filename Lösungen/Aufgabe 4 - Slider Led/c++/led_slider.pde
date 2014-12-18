#include <LED.h>

//Klasse instanziieren
LED led;
int sensorValue = 0;

void setup(){/*nothing to setup*/}

void loop()
{
		//Einlesen des analogen Wertes (Skala: 0-1023)
		sensorValue = led.analogRead(analog_pin);
		led.changeLedValue(sensorValue);	
}
