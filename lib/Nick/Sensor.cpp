#include <Arduino.h>
//Test IR sensor
const int Sensor = 8;

void setup()
{
  Serial.beign(9600);
  pinMode(Sensor, OUTPUT);
  Serialprint("Start uitlezen\n");
}

void loop()
{
  
}
