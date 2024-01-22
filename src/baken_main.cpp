#ifdef BAKEN
#include <Arduino.h>
#include <rf_receive2.h>
#define IRpin 9
char i;
char flag = 60;

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  noInterrupts();
  Serial.begin(9600);
  rf_receive_init();
  pinMode(IRpin, OUTPUT);
  pinMode(13, OUTPUT);
  TCCR1A = 0;     
  TCCR1B = 0;     
  TCCR1A |= (1 << COM1A0);
  TCCR1B |= (1 << CS11) | (1<< WGM12);  
  TIMSK1 |= (1 << OCIE1A);
  OCR1A = (F_CPU/16)/38500;
  interrupts();
}

ISR(TIMER1_COMPA_vect)
{
    static int t;
    digitalWrite(13, t);
    t=!t;
}

void loop()
{
  if(flag==60)
  {
    i=5;
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
    delay(100);
  }

  else
  {
    for(i=3; i<=4; i++)
    {
      digitalWrite(i, HIGH);
      delay(200);
      digitalWrite(i, LOW);
      delay(200);
      digitalWrite(i, HIGH);
      digitalWrite(i, HIGH);
      delay(200);
    }
  }
   
}

#endif