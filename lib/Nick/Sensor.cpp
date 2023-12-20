#include <Arduino.h>
//Test IR sensor
const int Sensor = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(Sensor, OUTPUT);
  Serial.print("Start uitlezen\n");
}

void loop()
{
  
}
