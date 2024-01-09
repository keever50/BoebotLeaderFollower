//Gemaakt door Xander

#pragma once
#include <Arduino.h>

//Definitions
#define transmissietijd_ms 1000
#define freq 500
#define trans_pin 3

void transmit_single(char high_low);
void transmit_binary(char *array, int size);

