#ifdef LEADER
#include <Arduino.h>
#include <rf_receive2.h>

#define IR_leds 9

int IR_status = 0;

void setup()
{
Serial.begin(9600);
pinMode(2, INPUT);
pinMode(IR_leds, OUTPUT);

noInterrupts();
rf_receive_init();

// Setup timer interrupt op 38kHz voor IR signaal
TCCR0A = 0;
TCCR0B = 0;
TCCR0B |= (1 << WGM01);
TIMSK0 |= (1 << OCIE0A);
OCR0A = 8;
TCCR0B |= (1 << CS01);

interrupts();


}
 
void loop(void)
{
     static int last_data = rf_receive_char_data();
    
    
    // if (last_data == 195)
    // {
    //     digitalWrite(led, HIGH);
    // }
    // else if(last_data == 196)
    // {
    //     digitalWrite(led, LOW);
    // }
    // else if(last_data != 0)
    // {
    //     Serial.println(last_data);
    // }
    // else
    // {
    //     Serial.println("No data");
    // }
    // delay(1000);
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

//interrupt voor de IR leds op 38 kHz
ISR(TIMER0_COMPA_vect)
{
    if(IR_status)
    {
        IR_status = 0;
    }
    else
    {
        IR_status = 1;
    }
    digitalWrite(IR_leds, IR_status);
    TCNT0 = 0;
}

#endif