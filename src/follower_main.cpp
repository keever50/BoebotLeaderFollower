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
  seeker_init_auto();
}

int t;
float beacon_angle=180;
void loop() {
  delay(100);
  //int a = seeker_stepdetect();
  //Serial.println(a);

  //Serial.println(seeker_get_step());


  if(seeker_did_full_revolution(1)==1)
  {
    float avg=0;
    float count=0;
    for(int i=0;i<SEEKER_STEPS_PER_REVOLUTION;i++)
    {
      char det = seeker_get_detections(i);
      if(det)
      {
        Serial.print("Detection on ");
        Serial.println(i);
        avg=avg+i;
        count++;
      }
    }
    avg=avg/count;
    Serial.print("Average: ");
    Serial.println(avg);

    float ratio = avg/(SEEKER_STEPS_PER_REVOLUTION);
    Serial.print("Deg: ");
    beacon_angle=ratio*360;
    Serial.println(beacon_angle);
    

    /*Steering*/
    const float max_steering=0.05;
    float steer = (beacon_angle-180)/(180*8);
    steer=steer*max_steering;
    if(steer>max_steering){steer=max_steering;}
    if(steer<-max_steering){steer=-max_steering;}
    
    pwmgen1_set_duty_A(0.075+steer);
  }




}





#endif

