#pragma once

#define SEEKER_INTERVAL    3000 //In uS interval

#define SEEKER_STEPS_PER_READ   10
#define SEEKER_STEP_PIN    2
#define SEEKER_EN_PIN      3
#define SEEKER_DETECT_PIN  8
#define SEEKER_DIR_PIN     12

void seeker_init();
char seeker_stepdetect();
void seeker_direction(char dir); 

void seeker_init_auto();
void seeker_get_angle();

