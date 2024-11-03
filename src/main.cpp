#include <Arduino.h>

void blink() {
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);     
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  log_d("blink");
  blink();
  blink();
  delay(1000);
}
