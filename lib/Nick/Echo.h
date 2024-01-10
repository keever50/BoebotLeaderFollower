#pragma once
#define ECHO_TRIGGERPIN 7
#define ECHO_ECHOPIN 4
#define max_tijd 1000
float duration, distance;
float echo_detect();
void echo_innit();
unsigned long echo_tijd();
