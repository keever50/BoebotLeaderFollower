// Geschreven door Xander Perry

#ifdef TRANSMITTER

#include <Arduino.h>
#include <rf_transmit.h>
#include <bin.h>

void setup()
{
    pinMode(3, OUTPUT);
    Serial.begin(9600);
    Serial.println("Welkom in de control hub van het Follow the leader project.");
    delay(1000);
    Serial.print("U kan commandos geven door de code ");
    delay(100);
    Serial.println("van de gewenste actie in de seriële input te geven.");
    delay(1000);
    Serial.println("Geef a.u.b. uw eerste input:");
}

char input_buffer[32] = {0};

void loop()
{

    if(Serial.available() > 0)
    {
        for(int i=0;i<15;i++)
        {
            input_buffer[i] = 0;
        }
        Serial.readBytes(input_buffer, 32);
        
        if ((toInt(input_buffer) < 0) || (toInt(input_buffer) > 256))
        {
            Serial.println("Ongeoorloofde input");
        }
        else
        {
            char bitarray[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            fill_binary_array(bitarray, toInt(input_buffer));
            for(int i = 0; i < 5; i++)
            {
                transmit_binary(bitarray, 8);
            }  
        }
    delay(500);
    Serial.println("Geef a.u.b. de volgende input:");
    }
}

#endif