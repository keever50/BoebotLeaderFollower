#ifdef BAKEN
#include <Arduino.h>
#include <rf_receive2.h>
#define BLAUW_pin 3
#define GROEN_pin 4
#define ROOD_pin 5
#define Servo_pin 7
#define IRpin 9
void LED_uit();
void LED_aan();
char i;
char aan = 0;

void setup()
{
  pinMode(BLAUW_pin, OUTPUT);
  pinMode(GROEN_pin, OUTPUT);
  pinMode(ROOD_pin, OUTPUT);
  pinMode(Servo_pin, OUTPUT);
  noInterrupts();
  Serial.begin(9600);
  rf_receive_init();
  pinMode(IRpin, OUTPUT);
  pinMode(13, OUTPUT);
  TCCR1A = 0;     
  TCCR1B = 0;
  TIMSK1 = 0;    
  TCCR1B |= (1 << CS11) | (1<< WGM12);  
  OCR1A = (F_CPU/16)/38500;
  interrupts();
  LED_uit();
}

ISR(TIMER1_COMPA_vect)
{
    static int t;
    digitalWrite(IRpin, t);
    t=!t;
}

int toggle_IR=1;
void loop()
{
  if (toggle_IR==0)
  {
    LED_aan();
  }

  if (toggle_IR==1)
  {
    LED_uit();
  }
  switch(rf_receive_char_data())
  {
  case 60:
  {
    if(toggle_IR)
    {
      TIMSK1 |= (1 << OCIE1A);
      toggle_IR=0;
    }
    else{
      TIMSK1 = 0;
      toggle_IR=1;
    }

    break;
  }
  default:
  {
    break;
  }
   break;
  }
  }

void LED_uit()
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

void LED_aan()
{
   digitalWrite(BLAUW_pin, LOW);
    digitalWrite(GROEN_pin, LOW);
    digitalWrite(ROOD_pin, HIGH);
    delay(100);
    digitalWrite(ROOD_pin, LOW);
    delay(100);
    digitalWrite(Servo_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(Servo_pin, LOW);
    delay(10);
}

#endif