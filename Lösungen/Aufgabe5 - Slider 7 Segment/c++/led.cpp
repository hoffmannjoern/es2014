#include "LED.h"

const byte LED_PIN = 13;
const byte ANALOG_PIN = 1;

const byte seven_seg_digits[10][7] = {{ 1,1,1,1,1,1,0 },  // = 0
								{ 0,1,1,0,0,0,0 },  // = 1
                                { 1,1,0,1,1,0,1 },  // = 2
                                { 1,1,1,1,0,0,1 },  // = 3
                                { 0,1,1,0,0,1,1 },  // = 4
                                { 1,0,1,1,0,1,1 },  // = 5
                                { 1,0,1,1,1,1,1 },  // = 6
                                { 1,1,1,0,0,0,0 },  // = 7
                                { 1,1,1,1,1,1,1 },  // = 8
                                { 1,1,1,0,0,1,1 }   // = 9
                               };

const byte 7seq_pin_A = 2;
const byte 7seq_pin_B = 3;
const byte 7seq_pin_C = 4;
const byte 7seq_pin_D = 5;
const byte 7seq_pin_E = 6;
const byte 7seq_pin_F = 7;
const byte 7seq_pin_G = 8;
							   
							   
							   
//Setup
Led::Led()
{
		pinMode(LED_PIN, OUTPUT);
		pinMode(ANALOG_PIN, INPUT);
		
		pinMode(7seq_pin_A, OUTPUT);   
		pinMode(7seq_pin_B, OUTPUT);
		pinMode(7seq_pin_C, OUTPUT);
		pinMode(7seq_pin_D, OUTPUT);
		pinMode(7seq_pin_E, OUTPUT);
		pinMode(7seq_pin_F, OUTPUT);
		pinMode(7seq_pin_G, OUTPUT);
}
 
//Destruktor
Led::~Led(){}
 

void changeLedValue(int sensorValue)
{
		//PWM + Konvertierung zu Skala 0-255
		analogWrite(ledPin, sensorValue / 4); 
}

int readSliderValue()
{
		int sensorValue = analogRead(ANALOG_PIN);
		return sensorValue;
}