#ifdef BAKEN
#include <Arduino.h>

void setup()
{
Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
  TCCR1A |= (1 << COM1A0);
  TCCR1B |= (1 << CS11) | (1<< WGM12);  // 8 prescaler
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = (F_CPU/16)/38500;
}

ISR(TIMER1_COMPA_vect)//timer1 interrupt 1Hz toggles pin 13 (LED
{
    static int t;
    digitalWrite(13, t);
    t=!t;
}

void loop()
{
    delay(500);
}

#endif