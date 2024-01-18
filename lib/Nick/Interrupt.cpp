#include <Arduino.h>
#define output1 8

unsigned char flag = 0;
volatile unsigned int tijd_1 = 300;
volatile unsigned int tijd_2 = 120;
volatile unsigned int Servo_total_time= 1250;

void setup() {

  //set pins as outputs
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  // initialize timer 1
  noInterrupts();
  TCCR1A = 0;     // set entire TCCR1A register to 0
  TCCR1B = 0;     // same for TCCR1B
  // 2 Hz preload value
  TCNT1  = 34286; // preload timer 65536-16MHz/256/2Hz first trip value (berekening is belangrijk!)
  TCCR1B |= (1 << CS12);  // 256 prescaler
  TIMSK1 |= (1 << TOIE1); //enable timer overflow interrupt
  interrupts();
}

ISR(TIMER1_OVF_vect)//timer1 interrupt 1Hz toggles pin 13 (LED
{
  if (flag == 0)
  {
    TCNT1 = 65535 - tijd_1;
    flag = 1;
    digitalWrite(10, HIGH);
  }
  else if (flag == 1)
  {
    TCNT1 = 65535 - tijd_2;
    flag = 2;
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if (flag == 2)
  {
    TCNT1 = 65535 - (Servo_total_time - tijd_2 - tijd_1);
    flag = 0;
    digitalWrite(11, LOW);
  }
}

void loop()
{
}
