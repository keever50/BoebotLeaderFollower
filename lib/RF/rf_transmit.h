#ifndef RFTrans_H
#define RFTrans_H
#include <Arduino.h>

//Definitions
#define transmissietijd_ms 1000
#define freq 1000
#define trans_pin 3

void transmit_single(char high_low);
void transmit_binary(char *array, int size);


#endif