//#define FOLLOWER
//#define LEADER

#ifdef FOLLOWER
#include <Arduino.h>
#include <pwmgen1.h>
#include <zoeker.h>

//Consumption: 0.36A @ 12.0V

void setup() {

  Serial.begin(115200);
  
  pwmgen1_clock_mode( 2 );
  pwmgen1_start();
  
  
  pwmgen1_set_frequency( 50 );
  pwmgen1_set_duty_A(0.075-0.0);
  pwmgen1_set_duty_B(0.075+0.0);
  
  seeker_init();

}

int t;
void loop() {
  //delayMicroseconds(1);
  int a = seeker_stepdetect();
  Serial.println(a);

}





#endif

