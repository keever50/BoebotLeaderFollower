#include <Arduino.h>
#include <Stepper.h>
void Stepper_innit()
{
    Serial.begin(9600);
    pinMode(Stap_pin, OUTPUT);
}

void Stepper()
{
  digitalWrite(Stap_pin, HIGH);
  delay(1);
  digitalWrite(Stap_pin, LOW);
  delay(1);
}