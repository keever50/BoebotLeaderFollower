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
  delay(10);
  //int a = seeker_stepdetect();
  //Serial.println(a);

  //Serial.println(seeker_get_step());


  if(seeker_did_full_revolution(1)==1)
  {
    float beacon_angle = seeker_get_degrees();
    

    /*Steering*/
    const float max_input=0.05;
    const float max_steer=0.001;
    const float steering_sensitivity=50.0;
    const float max_throttle=0.001;
    const int angle_to_steer=50;
    float input_L=0;
    float input_R=0;
    
    float steer = (beacon_angle-180.0)/(180.0*steering_sensitivity);
    if(steer>max_steer){steer=max_steer;}
    if(steer<-max_steer){steer=-max_steer;}
    
    if(steer>0)
    {
      input_L=input_L+steer;
    }else{
      input_R=input_R-steer;    
    }

    if(abs(beacon_angle-180)<angle_to_steer)
    {
      input_L=input_L-max_throttle;   
      input_R=input_R-max_throttle;   
    }  


    if(input_L>max_input){input_L=max_input;}
    if(input_L<-max_input){input_L=-max_input;}
    if(input_R>max_input){input_R=max_input;}
    if(input_R<-max_input){input_R=-max_input;}


    pwmgen1_set_duty_A(0.075+input_L);
    pwmgen1_set_duty_B(0.075-input_R);

  }




}





#endif

