#ifndef RFTrans_H
#define RFTrans_H
#include <Arduino.h>

//Definitions
#define transmissietijd_ms 1000

void transmit(char pin, double freq, char duty_cycle);


#endif