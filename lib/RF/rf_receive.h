#ifndef RF_H
#define RF_H

#include <Arduino.h>

#define RF_R_PIN    3

#define RF_PWM_TOLERANCE 0.10
#define RF_R_DATA_BUFFER_SIZE   128

int rf_receive_data_buffer( int pos );
bool rf_receive_data_ready( bool reset );
bool rf_receive_data_incoming();
float rf_receive_freq();
float rf_receive_duty();

void rf_recieve_init();

void rf_receive_ISR();

#endif