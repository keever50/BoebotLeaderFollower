#include <Arduino.h>
#include <Echo.h>

void setup()
{
    Serial.begin(9600);
    pinMode(ECHO_ECHOPIN, INPUT);
    pinMode(ECHO_TRIGGERPIN, OUTPUT);
}

void loop()
{
  echo_detect();
}

float echo_detect()
{
    digitalWrite(ECHO_TRIGGERPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ECHO_TRIGGERPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ECHO_TRIGGERPIN, LOW);
    
    duration= pulseIn(ECHO_ECHOPIN, HIGH);
    distance= (duration * 0.0343)/2;
    Serial.print("Afstand: \n");
    Serial.print(distance);
    Serial.println();
    delay(100);
}