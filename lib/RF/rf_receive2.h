#ifndef RFREC_H
#define RFREC_H

#define RF_RECEIVE_PIN  2



void rf_receive_init();
void rf_debug(float *freq, float *duty, int *detect);

#endif