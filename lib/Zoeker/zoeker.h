#pragma once

/*For the old code*/
#define SEEKER_INTERVAL    300 //In uS interval
#define SEEKER_STEPS_PER_READ   10
char seeker_stepdetect();
void seeker_direction(char dir); 
////////////////////


#define SEEKER_STEP_PIN    11
#define SEEKER_EN_PIN      3
#define SEEKER_DETECT_PIN  8
#define SEEKER_DIR_PIN     12

#define SEEKER_STEPS_PER_REVOLUTION 200*4

void seeker_init();


void seeker_init_auto();
void seeker_get_angle();

char seeker_get_detections( int addr );
char seeker_did_full_revolution( char reset );
int seeker_get_step();
float seeker_get_degrees();