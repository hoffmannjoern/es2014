#include <LED.h>

//Klasse instanziieren
LED led;
int buttonState = 0;

void setup(){/*nothing to setup*/}

void loop()
{
		buttonState=led.readButtonState();
		
		if (buttonState==HIGH)
		{
				led.on();
		}
		else
		{
				led.off();
		}
}
