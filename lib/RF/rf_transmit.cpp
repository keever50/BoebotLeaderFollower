//Gemaakt door Xander Perry

#include <Arduino.h>
#include <rf_transmit.h>


void transmit_single(char high_low)
{
  float periode_us;
  float t_hoog;
  float t_laag;
  char duty_cycle = 50;

  //binair signaal vertalen naar duty cycle
  if(high_low == 0){duty_cycle = 25;}
  else if(high_low == 1){duty_cycle = 75;}
  else{duty_cycle = 50;}

  //tijd van een periode berkenen
  periode_us = 1000000/freq;

  //hoog en laag tijd berekenen
  t_hoog = (periode_us * duty_cycle)/100;
  t_laag = (periode_us * (100 - duty_cycle)) / 100;

  /*
  Serial.print(periode_us);
  Serial.print("  ");
  Serial.print(t_hoog);
  Serial.print("  ");
  Serial.println(t_laag);
  */

  //signaal verzenden
    digitalWrite(trans_pin, LOW);
    delayMicroseconds(t_hoog);
    digitalWrite(trans_pin, HIGH);
    delayMicroseconds(t_laag);
}


void transmit_binary(char *array, int size)
{
  for(int i = 0; i < 5; i++)
  {
    transmit_single(2);
  }

  for(int i = 0; i <= size; i++)
  {
    transmit_single(array[i]);
  }

  for(int i = 0; i < 5; i++)
  {
    transmit_single(2);
  }

  digitalWrite(trans_pin, LOW);

}
