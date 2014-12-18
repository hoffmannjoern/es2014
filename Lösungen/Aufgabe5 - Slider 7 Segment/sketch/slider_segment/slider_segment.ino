//Pins vom Dangershield
int led_slider1   = 11;
int led_slider2   = 10;
int  slider2      = 1;
int  slider3      = 0;
int  serial_in    = 13;
int  clock        = 12;
int  latch        = 8;
int button        = 2;

int buttonState = 0;
int lastButtonState = 0;
int zustand = 0;


//Bitarray für 7  segmentanzeige
const byte seven_seg_digits[10][8] = {{ 0, 0, 1, 1, 1, 1, 1, 1 }, // = 0
  { 0, 0, 0, 0, 0, 1, 1, 0 }, // = 1
  { 0, 1, 0, 1, 1, 0, 1, 1 }, // = 2
  { 0, 1, 0, 0, 1, 1, 1, 1 }, // = 3
  { 0, 1, 1, 0, 0, 1, 1, 0 }, // = 4
  { 0, 1, 1, 0, 1, 1, 0, 1 }, // = 5
  { 0, 1, 1, 1, 1, 1, 0, 1 }, // = 6
  { 0, 0, 0, 0, 0, 1, 1, 1 }, // = 7
  { 0, 1, 1, 1, 1, 1, 1, 1 }, // = 8
  { 0, 1, 1, 0, 1, 1, 1, 1 } // = 9
};
/*
//---   7
  |  |  2 6
  ---   1
  |  |  3 5
  ---   4
*/

//Intialisierung
void setup()
{

  pinMode(slider2, INPUT);
  pinMode(slider3, INPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(serial_in, OUTPUT);
  pinMode(led_slider1, OUTPUT);
  pinMode(led_slider2, OUTPUT);
  pinMode(button, INPUT);

}

//Loop
void loop()
{
  //Button entprellen
  buttonState = readButtonState(button);
  if (buttonState == HIGH)
  {
    if (zustand == 0)
    {
      on(led_slider1);
      zustand = 1;
    }
    else
    {
      off(led_slider1);
      zustand = 0;
    }
  }

  //Einlesen des analogen Wertes (Skala: 0-1023)
  changeLedValue(analogRead(slider2), led_slider2);
  writeSevenSegwithShiftRegister(analogRead(slider3) / (112));

}
void writeSevenSegwithShiftRegister(int number)
{
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(serial_in, seven_seg_digits[number][i]);
    digitalWrite(clock, HIGH);
    delay(2);
    digitalWrite(clock, LOW);
  }
}

void changeLedValue( int sensorValue, int pin)
{
  //PWM + Konvertierung zu Skala 0-255
  analogWrite(pin, sensorValue / 4);
}


int readButtonState(int pin)
{
  int buttonState = digitalRead(pin);
  //Entprellung
  if (buttonState != lastButtonState)
  {
    lastButtonState = buttonState;
    delay(100);
  }
  return buttonState;
}

void on(int pin ){
  digitalWrite(pin, HIGH);
}

void off(int pin){
  digitalWrite(pin, LOW);
}

