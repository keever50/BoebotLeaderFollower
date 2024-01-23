#ifdef BAKEN
#include <Arduino.h>
#include <rf_receive2.h>    //Include de library voor het ontvangen van de RF
                            //Defenities verschillende pins:
#define BLAUW_pin 3         //-Blauwe LED pin
#define GROEN_pin 4         //-Groene LED pin
#define ROOD_pin 5          //-Rode LED pin
#define Servo_pin 7         //-Servo pin
#define IRpin 9             //-Infrarood LED's pin
void LED_uit();      //Defenities voor functies
void LED_aan();
char i;           //Variabele i aangemaakt
char toggle_IR = 1;   //Vatiabele voor de toggle van de ir LED's aangemaakt en gedefineërd

void setup()
{
  Serial.begin(9600);     //begin serieële communicatie
  pinMode(BLAUW_pin, OUTPUT);     //defineer blauwe pin als output
  pinMode(GROEN_pin, OUTPUT);     //defineer groene pin als output
  pinMode(ROOD_pin, OUTPUT);      //defineer rode pin als output
  pinMode(Servo_pin, OUTPUT);     //defineer servo pin als output
  pinMode(IRpin, OUTPUT);         //defineer IR pin als output
  rf_receive_init();

  noInterrupts();       //Disable interrupts
  TCCR1A = 0;     
  TCCR1B = 0;
  TIMSK1 = 0;    
  TCCR1B |= (1 << CS11) | (1<< WGM12);  
  OCR1A = (F_CPU/16)/38500;
  interrupts();       //Enable interrupts

}

ISR(TIMER1_COMPA_vect)
{
    static int t;
    digitalWrite(IRpin, t);
    t=!t;
}

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