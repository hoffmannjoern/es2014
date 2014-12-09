int ledState = LOW;

const int led = 11;
const int button = 2;

void setup() {
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, ledState);
}

void loop() {
  int buttonState = digitalRead(button);
  
  if(buttonState == HIGH) {
    ledState = 1 - ledState;
    digitalWrite(led, ledState);
    // wait for 250 to debounce the button
    delay(250);
  }
}
