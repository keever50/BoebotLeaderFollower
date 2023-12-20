#include <Arduino.h>
#include <Stepper.h>
{
    Serial.begin(9600);
    pinMode(Stap_pin, OUTPUT);
    pinMode(Richting, OUTPUT);
}

void loop()
{
  Stepper();
}

void Stepper()
{
  digitalWrite(Stap_pin, HIGH);
  delay(1);
  digitalWrite(Stap_pin, LOW);
  delay(1);
}