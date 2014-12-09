/**
 * Aufgabe 1.1
 */

void setup() {
  // LED 2 on danger board is connected to digital pin 5
  pinMode(5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH);
  delay(1000);
  digitalWrite(5, LOW);
  delay(1000);
}
