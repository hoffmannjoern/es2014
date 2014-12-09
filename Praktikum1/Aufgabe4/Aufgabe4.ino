const int led = 11;
const int slider = A2;

int currentSliderValue = 0;

int lastRead;

void setup() {
  pinMode(led, OUTPUT);
  lastRead = millis();
}

void loop() {
  // only read every 100 ms
  if(millis() - lastRead > 100) {
    currentSliderValue = analogRead(slider);
    lastRead = millis();
  }
  
  // pwm
  digitalWrite(led, HIGH);
  delayMicroseconds(1024 - currentSliderValue);
  digitalWrite(led, LOW);
  delayMicroseconds(currentSliderValue + 1);
}
