// Geschreven door Xander Perry

#ifdef LEADER
#include <Arduino.h>
#include <rf_receive2.h>

#define IR_leds 9
#define buzzer 4

#define speedr 10
#define motorr 12
#define speedl 6
#define motorl 7

int IR_status = 0;

void toggle_drive();
void drive(char speed1, char speed2);


void setup()
{
Serial.begin(9600);

pinMode(2, INPUT);
pinMode(IR_leds, OUTPUT);
digitalWrite(IR_leds, LOW);

pinMode(buzzer, OUTPUT);
digitalWrite(buzzer, LOW);

pinMode(motorr, OUTPUT);
pinMode(motorl, OUTPUT);

pinMode(11, OUTPUT);
pinMode(13, OUTPUT);
digitalWrite(11, LOW);
digitalWrite(13, LOW);

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
    static int speed = 0;
    static int command;
    command = rf_receive_char_data();

    switch (command)
    {
    case 0: // pass if no incoming command
        break;
    case 60: // l:   toggle leds
    {
        static char toggle_led = 1;
        if(toggle_led)
        {
            TIMSK2 = 0;
            digitalWrite(IR_leds, LOW);
            toggle_led = 0;
        }
        else
        {
            TIMSK2 |= (1 << OCIE2A);
            digitalWrite(IR_leds, HIGH);
            toggle_led = 1;
        }
        break;
    }

    case 66: // r:    Reverse drive direction 
        toggle_drive();
        break;
        
    case 71: // w:    Accelerate
        if (speed >= 70)
        {
            speed += 10;
        }
        else
        {
            speed = 70;
        }
        drive(speed, speed);
        break;

    case 67: // s:     Decelerate
        if (speed > 70)
        {
            speed -= 10;
        }
        else
        {
            speed = 0;
        }
        drive(speed, speed);
        break;
    
    case 49: // a:      Turn left
        drive(70, 100);
        delay(1500);
        drive(speed, speed);
        break;
    
    case 52: // d:     Turn right
        drive(100, 70);
        delay(1500);
        drive(speed, speed);
        break;
    
    case 53: // e:     Stop driving
        drive(0, 0);
        speed = 0;
        break;

    default: // Signal for unknown command
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);
        break;
    }
}

void toggle_drive(void)
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
    analogWrite(speedl, speed1);
    analogWrite(speedr, speed2);
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