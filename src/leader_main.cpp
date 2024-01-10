#ifdef LEADER
#include <Arduino.h>
#include <rf_receive2.h>
#define led 4

void setup()
{
Serial.begin(9600);
pinMode(led, OUTPUT);
pinMode(2, INPUT);
digitalWrite(led, LOW);

rf_receive_init();
}
 
void loop(void)
{
    int last_data = rf_receive_char_data();
    if (last_data != 0)
    {
        Serial.println(last_data);
    }
    else
    {
        Serial.println("No data");
    }
    delay(1000);
}

// if (rf_receive_get_data_ready(1))
// {
//     char bin_array[8];
//     for(int i = 0; i < 8; i++)
//     {
//         bin_array[i]=(rf_receive_get_data(i)<0.5);
//     }

//     for(int i = 0; i < 8; i++)
//     {
//         Serial.print((int)bin_array[i]);
//         Serial.print(" ");
//     }

// Serial.println();
// }
// else
// {
//     Serial.println("No data");    
// }
// delay(1000);
// }

#endif