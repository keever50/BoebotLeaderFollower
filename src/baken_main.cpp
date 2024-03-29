#ifdef BAKEN
#include <Arduino.h>
#include <rf_receive2.h>    //Include de library voor het ontvangen van de RF

#define BLAUW_pin 3
#define GROEN_pin 4
#define ROOD_pin 5
#define Servo_pin 7
#define IRpin 9
#define Buzzerpin 12

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
  pinMode(Buzzerpin, OUTPUT);
  rf_receive_init();

  noInterrupts();       //Disable interrupts
  TCCR1A = 0;     
  TCCR1B = 0;
  TIMSK1 = 0;         //Timer is 0 baken staat uit in de beginfase
  TCCR1B |= (1 << CS11) | (1<< WGM12);  
  OCR1A = (F_CPU/16)/38500;     //Berekening om de IR-LED's op de juiste frequentie te pulsen (38,5 kHz)
  interrupts();       //Enable interrupts

}

ISR(TIMER1_COMPA_vect)     
{
    static int t;        //In deze functie worden de IR lampjes gepulst op een frequentie van 38,5 kHz
    digitalWrite(IRpin, t);
    t=!t;
}

void loop()
{
  if (toggle_IR==0)   //Als de IR_toggle gelijk is aan 0, staat de baken aan
  {
    Baken_aan();
  }

  if (toggle_IR==1)     //Als de toggle gelijk is aan 1, staat de baken uit
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

void Baken_uit()        //Functie als de baken geen RF singaal ontvangt
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

void Baken_aan()      //Functie als de baken een RF signaal ontvangt
{
    int j;
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
    tone(Buzzerpin, 1000, 500);
}

#endif