#include <Echo.h>
#include <Arduino.h>

void echo_innit()
{
    Serial.begin(9600);
    pinMode(ECHO_ECHOPIN, OUTPUT);
    pinMode(ECHO_TRIGGERPIN, INPUT);
}

float echo_detect()
{
    digitalWrite(ECHO_TRIGGERPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ECHO_ECHOPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ECHO_TRIGGERPIN, LOW);
    
    duration= pulseIn(ECHO_ECHOPIN, HIGH);
    distance= (duration * .0343)/2;
    Serial.print("Afstand: ");
    Serial.print(distance);
    delay(100);
}