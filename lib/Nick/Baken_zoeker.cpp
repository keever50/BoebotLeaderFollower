#include <Arduino.h>
#include <Stepper.h>

//Test IR sensor
const int Ir_Sensorpin = 8;
void Aflezen_Ir_sensor();

void setup()
{
  Serial.begin(9600);
  pinMode(Ir_Sensorpin, INPUT);
  pinMode(Stap_pin, OUTPUT);
  Serial.print("Start uitlezen\n");
}

void loop()
{
  digitalWrite(Stap_pin, HIGH);
  delayMicroseconds(250);
  digitalWrite(Stap_pin, LOW);
  delayMicroseconds(250);
Aflezen_Ir_sensor();
}

void Aflezen_Ir_sensor()
{
  if (digitalRead(Ir_Sensorpin)>0)
  {
  Serial.print(digitalRead(Ir_Sensorpin));
  Serial.println();
  }
}