int led_pin = 6;
byte analog_pin = A2;
int sensorValue = 0;

void setup() 
{                
	pinMode(led_pin, OUTPUT);
        pinMode(analog_pin, INPUT);
}

void loop()
{
	//Einlesen des analogen Wertes (Skala: 0-1023)
	sensorValue = analogRead(analog_pin);
        changeLedValue(sensorValue);

	
}

void changeLedValue( int sensorValue)
{
      //PWM + Konvertierung zu Skala 0-255
      analogWrite(led_pin, sensorValue / 4); 
}

