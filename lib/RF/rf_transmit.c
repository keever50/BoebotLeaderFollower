#define transmissietijd_ms 1000

void transmit(char pin, double freq, char duty_cycle)
{
  float periode_us;
  float t_hoog;
  float t_laag;
  unsigned char herhalingen;

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

  //herhalingen berkenen
  herhalingen = transmissietijd_ms/periode_us;

  //signaal verzenden
  int i;
  for(i = 0; i <= herhalingen; i++)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(t_hoog);
    digitalWrite(pin, LOW);
    delayMicroseconds(t_laag);
  }
}
