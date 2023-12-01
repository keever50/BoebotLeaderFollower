/*
TODO 0: Voeg functie toe die returnt hoeveel bytes er beschikbaar is om te lezen.
    Doe dit met behulp van rf_receive_ISR, waar de byte_count op nul wordt gezet.
    DIT HELPT TODO 1
*/

/*
TODO 1: Wanneer je de buffer leest, mag er geen andere interrupt een onderbreking maken.
    Gebruik noInterrupts(); en interrupts(); om interrupts aan en uit te zetten.
    Maak eventueel ook een kopie van de buffer naar een andere buffer, zodat deze niet tijdens het lezen veranderdt.
*/

#ifndef RF_H
#define RF_H
#include <Arduino.h>

//Pins
#define RF_R_PIN    3

//Config
#define RF_MODULATION_FREQUENCY_HZ      1000

#define RF_FREQUENCY_TOLERANCE_HZ       50
#define RF_PWM_TOLERANCE                0.10
#define RF_R_DATA_BUFFER_SIZE           128

int rf_receive_data_buffer( int pos );
bool rf_receive_data_ready( bool reset );
bool rf_receive_data_incoming();

void rf_receive_init();

void rf_receive_ISR();

#endif