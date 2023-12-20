#pragma once
#define ECHO_TRIGGERPIN 7
#define ECHO_ECHOPIN 4
float duration, distance;
float echo_detect();
void echo_innit();
