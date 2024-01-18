/*
    Made by Kevin Witteveen 
*/

#include <pwmgen1.h>
#include <Arduino.h>

char _pwmgen1_clk_select=PWMGEN1_DEFAULT_CLK_SEL;
unsigned long _pwmgen1_clock_frequency;

void pwmgen1_start()
{
    //Pin set mode
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    //Clear control registers
    TCCR1A=0;
    TCCR1B=0;
    TCCR1C=0;

    TCCR1A = 1<<COM1A1 | 1<<COM1B1; //Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when down counting
    TCCR1B = 1<<WGM13; //Mode 8 PWM, phase and frequency correct

    //Clock select bits
    switch(_pwmgen1_clk_select)
    {
        case 0:
                TCCR1B = TCCR1B | 0<<CS12 | 0<<CS11 | 0<<CS10; 
                _pwmgen1_clock_frequency=0;
            break;
        case 1:
            TCCR1B = TCCR1B | 0<<CS12 | 0<<CS11 | 1<<CS10; 
            _pwmgen1_clock_frequency=F_CPU/1;
            break;
        case 2:
            TCCR1B = TCCR1B | 0<<CS12 | 1<<CS11 | 0<<CS10; 
            _pwmgen1_clock_frequency=F_CPU/8;
            break;
        case 3:
            TCCR1B = TCCR1B | 0<<CS12 | 1<<CS11 | 1<<CS10; 
            _pwmgen1_clock_frequency=F_CPU/64;
            break;
        case 4:
            TCCR1B = TCCR1B | 1<<CS12 | 0<<CS11 | 0<<CS10;
            _pwmgen1_clock_frequency=F_CPU/256;
            break;
        case 5:
            TCCR1B = TCCR1B | 1<<CS12 | 0<<CS11 | 1<<CS10;
            _pwmgen1_clock_frequency=F_CPU/1024;
            break;

    }
}

void pwmgen1_set_frequency( int freq )
{
    ICR1=_pwmgen1_clock_frequency/(2*freq);
}

void pwmgen1_set_duty_A( float duty )
{
    OCR1A=ICR1*duty;
}

void pwmgen1_set_duty_B( float duty )
{
    OCR1B=ICR1*duty;
}

void pwmgen1_clock_mode( char mode )
{
    if(_pwmgen1_clk_select<6)
    {
        _pwmgen1_clk_select=mode;
    }
}