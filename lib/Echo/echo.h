/*Geschreven door Nick*/

#pragma once
#define ECHO_TRIGGERPIN 7
#define ECHO_ECHOPIN 4
#define max_tijd 100000

float echo_detect();
void echo_init();
unsigned long echo_tijd();
