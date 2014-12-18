int led_pin = 6;
int button_pin = 2;
int buttonState = 0;
int lastButtonState = 0;
int zustand=0;

void setup()
{
    pinMode(led_pin, OUTPUT);
    pinMode(button_pin, INPUT);
    //digitalWrite(button_pin, HIGH);
}

void loop()
{
    buttonState=readButtonState(button_pin);
    if (buttonState == HIGH)
    {
        if(zustand==0)
        {
            on();
            zustand=1;
        }
        else
        {
            off();
            zustand=0;
        }
    }
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

void on(){
  digitalWrite(led_pin, HIGH);
}

void off(){
  digitalWrite(led_pin, LOW);
}

