#ifdef BAKEN
#include <Arduino.h>
#include <rf_receive2.h>
#define IRpin 9

void setup()
{
  noInterrupts();
  Serial.begin(9600);
  rf_receive_init;
  pinMode(IRpin, OUTPUT);
  pinMode(13, OUTPUT);
  TCCR1A = 0;     
  TCCR1B = 0;     
  TCCR1A |= (1 << COM1A0);
  TCCR1B |= (1 << CS11) | (1<< WGM12);  
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = (F_CPU/16)/38500;
}

ISR(TIMER1_COMPA_vect)
{
    static int t;
    digitalWrite(13, t);
    t=!t;
}

void loop()
{
  if(rf_recieve_char_data()==60);
  {
    interrupts();
  }

  else
  {
    
  }
}

#endif