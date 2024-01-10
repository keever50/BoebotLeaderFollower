#ifdef TRANSMITTER

#include <Arduino.h>
#include <rf_transmit.h>

void setup()
{
    Serial.begin(9600);
}

char bitarray[8] = {1, 1, 0, 0, 0, 0, 1, 1};

void loop()
{
    

    transmit_binary(bitarray, 8);
    delay(10); 
    
    delay(5000);
}

#endif