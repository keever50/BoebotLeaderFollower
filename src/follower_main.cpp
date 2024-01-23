/*Geschreven door Kevin Witteveen*/
/*Written by Kevin Witteveen*/

#ifdef FOLLOWER
#include <Arduino.h>
#include <pwmgen1.h>
#include <seeker.h>
#include <echo.h>

//Consumption: 0.36A @ 12.0V

#define WHEELS_MAX_VARIATION  0.05

/*Navigation angle hysteresis*/
#define NAVIGATION_BIG_ANGLE  25 /*Above this angle, do a big turn*/
#define NAVIGATION_SMALL_ANGLE 10 /*Below this angle, do a normal turn and move*/

#define NAVIGATION_BIG_ANGLE_STEERING_SPEED 0.03f
#define NAVIGATION_STEERING_MULTIPLIER 0.001f
#define NAVIGATION_FORWARD_SPEED  0.04f
#define NAVIGATION_FRONT_CLEARANCE  30

/*State machine state cases*/
#define STATE_SEARCH        0
#define STATE_BIG_TURN      1
#define STATE_MOVE_TOWARDS  2
#define STATE_BLOCKED       3

/*Simple beep function*/
void beep(int freq, int len)
{
  static int t;
  for(int i=0;i<len;i++)
  {
    delayMicroseconds(1000000/freq);
    digitalWrite(13, t);
    t=!t;
  }

  digitalWrite(13, 0);
}

float limit(float in, float min, float max )
{
  if(in>max) in=max;
  if(in<min) in=min;
  return in;
}

/*from -1 to 1.*/
void wheels( float L, float R )
{
  L=L*WHEELS_MAX_VARIATION;
  R=R*WHEELS_MAX_VARIATION;

  limit(L,-WHEELS_MAX_VARIATION,WHEELS_MAX_VARIATION);
  limit(R,-WHEELS_MAX_VARIATION,WHEELS_MAX_VARIATION);
  pwmgen1_set_duty_A(0.075-L);
  pwmgen1_set_duty_B(0.075+R);
}


void setup() {

  Serial.begin(115200);
  
  /*Initialize servos*/
  pwmgen1_clock_mode( 2 );
  pwmgen1_start();
  pwmgen1_set_frequency( 50 );
  pwmgen1_set_duty_A(0.075-0.0);
  pwmgen1_set_duty_B(0.075+0.0);
  
  /*Initialize steppers and seeker*/
  seeker_init();
  seeker_init_auto();

  /*Initialize echo*/
  echo_init();
  
  beep(1000, 300);
  beep(2000, 400);
  beep(3000, 500);
  beep(4000, 600);

  delay(1000);
}

int state;
int prev_state;
float nav_degrees=SEEKER_NOTHING_FOUND;
void loop() {
  delay(10);


  /*Navigation state machine*/
  switch(state)
  {
    
    /*When nothing has been detected, stand still and look around*/
    case STATE_SEARCH:
    {
      if(seeker_did_full_revolution(SEEKER_READ_FLAG))
      {
        /*On detection do*/
        nav_degrees=seeker_get_degrees();
        if(nav_degrees!=SEEKER_NOTHING_FOUND)
        {
          state = STATE_BIG_TURN;
          break;
        }

        seeker_did_full_revolution(SEEKER_RESET_FLAG);
      }else{
        delay(2500);
        beep(500, 100);
      }
      break;
    }

    /*The target is not infront of me. I will turn fast without moving*/
    case STATE_BIG_TURN:
    {
      if(seeker_did_full_revolution(SEEKER_READ_FLAG))
      {
        /*On detection do*/
        nav_degrees=seeker_get_degrees();

        if(nav_degrees==SEEKER_NOTHING_FOUND)
        {
          state=STATE_SEARCH;
          wheels(0,0);
          break;
        }

        /*Navigation angle hysteresis*/
        if(abs(nav_degrees)<NAVIGATION_SMALL_ANGLE)
        {
          beep(4000, 100);
          beep(3000, 100);
          state = STATE_MOVE_TOWARDS;
          break;
        }

        /*Steering*/
        if(nav_degrees>0)
        {
          wheels(NAVIGATION_BIG_ANGLE_STEERING_SPEED,0);
        }else{
          wheels(0,NAVIGATION_BIG_ANGLE_STEERING_SPEED);
        }

        seeker_did_full_revolution(SEEKER_RESET_FLAG);
      }     
      break;
    }

    /*The target is infront of me. I will move towards target and turn slightly*/
    case STATE_MOVE_TOWARDS:
    {
      if(seeker_did_full_revolution(SEEKER_READ_FLAG))
      {
        /*On detection do*/
        nav_degrees=seeker_get_degrees();
        if(nav_degrees==SEEKER_NOTHING_FOUND)
        {
          state=STATE_SEARCH;
          wheels(0,0);
          break;
        }

        /*Obstacle detect*/
        if(echo_detect() < NAVIGATION_FRONT_CLEARANCE)
        {
          state = STATE_BLOCKED;
          break;
        }

        /*Navigation angle hysteresis*/
        if(abs(nav_degrees)>NAVIGATION_BIG_ANGLE)
        {
          beep(1000, 200);
          state = STATE_BIG_TURN;
          break;
        }

        /*Steering*/
        float steer = abs(nav_degrees)*NAVIGATION_STEERING_MULTIPLIER;
        if(nav_degrees>0)
        {
          wheels(steer+NAVIGATION_FORWARD_SPEED,NAVIGATION_FORWARD_SPEED);
        }else{
          wheels(NAVIGATION_FORWARD_SPEED,steer+NAVIGATION_FORWARD_SPEED);
        }        

        seeker_did_full_revolution(SEEKER_RESET_FLAG);
      }   
      break;   
    }

    /*Something is infront of me. Dont move*/
    case STATE_BLOCKED:
    {
      delay(250);
      beep(5000,50);
      if(echo_detect() > NAVIGATION_FRONT_CLEARANCE)
      {
        state = STATE_MOVE_TOWARDS;
        break;
      }else{
        wheels(0,0);
      }
      break;
    }
  }



}





#endif

