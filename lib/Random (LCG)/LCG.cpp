//Gemaakt door Xander


#include <Arduino.h>
#include <EEPROM.h>
char seedlocation = 0;

long LCG(void);
char update_seed(void);

static long value = EEPROM.read(seedlocation);

char update_seed(void)
{
  char newseed = EEPROM.read(seedlocation)+1;
  EEPROM.put(seedlocation, newseed);
  return newseed;
}

long LCG(void)
{
  //	modulus > 0
  //	0 < multiplier < modulus
  //	0 <= increment < modulus
  //	0 <= seed <modulus
  long m = 5234; //modulus
  long x = 4425; //multiplier
  long p = 3782; //increment

	value = (x * value + p) % m;
	return value;
}

