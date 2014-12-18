#include <LED.h>

//Klasse instanziieren
LED led;
int sensorValue = 0;

void setup(){/*nothing to setup*/}

void loop()
{
		//Einlesen des analogen Wertes (Skala: 0-1023)
		sensorValue = led.readSensorValue();
		
		if(sensorValue<512) 
		{
				led.writeSevenSeg(0);
		}
		else
		{
				led.writeSevenSeg(1);
		}
}
