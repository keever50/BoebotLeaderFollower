//#define FOLLOWER
//#define LEADER

#ifdef FOLLOWER
#include <Arduino.h>
#include <zoeker.h>


void setup() {
  Serial.begin(115200);

  seeker_init();
}

int t;
void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<100;i++)
  {
    int det = seeker_stepdetect();
    Serial.print(det);
    Serial.println("");
  }
  seeker_direction(t);
  t=!t;
  //delay(200);
}



#endif

