#ifdef TESTING

#include <Arduino.h>
#include <pwmgen1.h>

void setup()
{
    pwmgen1_clock_mode( 2 );
    pwmgen1_start();
    pwmgen1_set_frequency(38500);
    pwmgen1_set_duty_A(0.5);
    
}

void loop()
{
    
}

#ifdef DEBUG
int test = 2;
#endif

#endif