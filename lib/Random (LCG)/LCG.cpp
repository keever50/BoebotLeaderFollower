long LCG(void);
update_seed(void);

static long value = 93456; //seed definiëren

update_seed(void)
{
  value = analogRead(0);
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

