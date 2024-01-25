#ifdef BAKEN
#include <Arduino.h>
#include <rf_receive2.h>    //Include de library voor het ontvangen van de RF

#define BLAUW_pin 3
#define GROEN_pin 4
#define ROOD_pin 5
#define Servo_pin 7
#define IRpin 9

void Baken_uit();
void Baken_aan();
char i;
char toggle_IR = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(BLAUW_pin, OUTPUT);
  pinMode(GROEN_pin, OUTPUT);
  pinMode(ROOD_pin, OUTPUT);
  pinMode(Servo_pin, OUTPUT);
  pinMode(IRpin, OUTPUT);
  rf_receive_init();

  noInterrupts();       //Disable interrupts
  TCCR1A = 0;     
  TCCR1B = 0;
  TIMSK1 = 0;    
  TCCR1B |= (1 << CS11) | (1<< WGM12);  
  OCR1A = (F_CPU/16)/38500;     //Berekening om de IR-LED's op de juiste frequentie te pulsen
  interrupts();       //Enable interrupts

}

ISR(TIMER1_COMPA_vect)
{
    static int t;        //In deze functie wordt de IR
    digitalWrite(IRpin, t);
    t=!t;
}

void loop()
{
  if (toggle_IR==0)
  {
    Baken_aan();
  }

  if (toggle_IR==1)
  {
    Baken_uit();
  }
  switch(rf_receive_char_data())
  {
  case 50:
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
  }
  }

void Baken_uit()
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

void Baken_aan()
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