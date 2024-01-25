//Gemaakt door Kevin

#pragma once

#define RF_RECEIVE_PIN  2

#define RF_RECEIVE_FREQ_HI  500
#define RF_RECEIVE_FREQ_LOW 400

void rf_receive_init();
void rf_debug(float *freq, float *duty, int *detect);

char rf_receive_get_data_ready( char reset );
float rf_receive_get_data( int bit );
void rf_break(int time);

int rf_receive_char_data(void);
