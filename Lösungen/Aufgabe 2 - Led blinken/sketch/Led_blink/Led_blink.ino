//Pins
byte led_pin = 6;

//Initialisierung
void setup()
{                
    pinMode(led_pin, OUTPUT);     
}

//Loop Routine starten
void loop()
{
    blink(led_pin,1000);
}

//Funktion zum Blinken einer LED für Zeitraum time
void blink(byte pin, int time)
{
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
    delay(time);
}
