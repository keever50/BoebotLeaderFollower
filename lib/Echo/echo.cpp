/*Geschreven door Nick*/

#include <Arduino.h>
#include <echo.h>

// void setup()
// {
//     Serial.begin(9600);
//     pinMode(ECHO_ECHOPIN, INPUT);
//     pinMode(ECHO_TRIGGERPIN, OUTPUT);
// }

// void loop()
// {
//   echo_detect();
// }

void echo_init()
{
  pinMode(ECHO_ECHOPIN, INPUT);
  pinMode(ECHO_TRIGGERPIN, OUTPUT); 
}

float echo_detect()
{
    digitalWrite(ECHO_TRIGGERPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(ECHO_TRIGGERPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ECHO_TRIGGERPIN, LOW);
    
    unsigned long duration = echo_tijd();
    float distance = ((float)duration * 0.0343)/2.0;
    // Serial.print("Afstand: \n");
    // Serial.print(distance);
    // Serial.println();
    // delay(100);
    return distance;
}

unsigned long echo_tijd()
{
  unsigned long duration=0;
  unsigned long starttijd = micros();
  while (digitalRead(ECHO_ECHOPIN) == LOW)
  {
    if (micros()-starttijd > max_tijd)
    {
      return 999;
    }
  }
  starttijd = micros();
  while (digitalRead(ECHO_ECHOPIN) == HIGH)
  {
    if (micros()-starttijd > max_tijd){
      return 888;
    }
    duration = micros() - starttijd;
  }
  return duration;


}