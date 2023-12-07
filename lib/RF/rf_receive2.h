#ifndef RFREC_H
#define RFREC_H

#define RF_RECEIVE_PIN  2

#define RF_RECEIVE_FREQ_HI  1000
#define RF_RECEIVE_FREQ_LOW 900

void rf_receive_init();
void rf_debug(float *freq, float *duty, int *detect);

char rf_receive_get_data_ready( char reset );
float rf_receive_get_data( int bit );

#endif