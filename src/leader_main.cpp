#ifdef LEADER
#include <Arduino.h>
#include <rf_receive2.h>

#define IR_leds 9
#define IR_switch 7

#define speedr 10
#define motorr 12
#define speedl 11
#define motorl 13

int IR_status = 0;

void toggle_drive();
void drive(char speedl, char speedr);


void setup()
{
Serial.begin(9600);

pinMode(2, INPUT);
pinMode(IR_leds, OUTPUT);
digitalWrite(IR_leds, LOW);

pinMode(IR_switch, OUTPUT);
digitalWrite(IR_switch, LOW);

pinMode(motorr, OUTPUT);
pinMode(motorl, OUTPUT);

noInterrupts();
rf_receive_init();

// Setup timer interrupt op 38kHz voor IR signaal
TCCR2A = 0;
TCCR2B = 0;
TCCR2B |= (1 << WGM21);
TIMSK2 |= (1 << OCIE2A);
OCR2A = 8;
TCCR2B |= (1 << CS11);

interrupts();


}
 
void loop(void)
{
    static char mode = 0;
    static int command;
    command = rf_receive_char_data();
    Serial.println(command);
    delay(1000);
    
    switch (command)
    {
    case 0: //do nothing
        break;
    case 1: //leader stand by
        mode = 0;
        TIMSK2 &= (0 << OCIE2A);
        Serial.println("stand by");
        break;
    case 2: //leader IR off
        TIMSK2 &= (0 << OCIE2A);
        digitalWrite(IR_leds, LOW);
        digitalWrite(IR_switch, LOW);
        Serial.println("IR off");
        break;
    case 3: //leader IR on
        TIMSK2 |= (1 << OCIE2A);
        digitalWrite(IR_leds, HIGH);
        digitalWrite(IR_switch, HIGH);
        Serial.println("IR on");
        break;
    case 4: //drive mode random
        mode = 1;
        break;
    case 5: //speed low
        drive(100, 100);
        break;
    case 6: //speed medium
        drive(150, 150);
        break;
    case 7: //speed high
        drive(200, 200);
        break;
    case 8: 
        drive(0, 100);
        break;
    case 9:
        drive(0, 0);
        break;
    case 10:
        toggle_drive();
        break;

    }

    switch (mode)
    {
    case 0:// stand by
        /* code */
        break;
    
    case 1:// drive mode random
        /* code */
        break;
    }
}

void toggle_drive()
{
    static char toggle = 0;
    if(toggle)
    {
        digitalWrite(motorr, LOW);
        digitalWrite(motorl, LOW);
        toggle = 0;
    }
    else
    {
        digitalWrite(motorr, HIGH);
        digitalWrite(motorl, HIGH);
        toggle = 1;
    }
}

void drive(char speed1, char speed2)
{
    analogWrite(speed1, speedl);
    analogWrite(speed2, speedr);
}

//interrupt voor de IR leds op 38 kHz
 ISR(TIMER2_COMPA_vect)
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
    TCNT2 = 0;
}

#endif




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
//
// Serial.println();
// }
// else
// {
//     Serial.println("No data");    
// }
// delay(1000);
// }