#include <rf_receive2.h>
#include <Arduino.h>

volatile float rf_debug_frequency;
volatile float rf_debug_duty;
volatile int rf_detection;

void rf_debug(float *freq, float *duty, int *detect)
{
    *freq=rf_debug_frequency;
    *duty=rf_debug_duty;
    if(rf_detection == 1)
    {
        *detect=rf_detection;
        rf_detection = 0;
    }
    
}

void rf_receive_ISR()
{
    static float start_time=0;
    static float end_time=0;
    static float wave_period;
    static float wave_frequency;

    int state = digitalRead(RF_RECEIVE_PIN);
    if(state==0)
    {
        //Calculate frequency
        wave_period = (micros() - start_time);
        wave_frequency = (1000000/wave_period);      
        start_time = micros();

        //Calculate duty
        float pulse_high = start_time-end_time;
        float duty = pulse_high/wave_period;

        //debug
        rf_debug_frequency=wave_frequency;
        rf_debug_duty=duty;
        if(wave_frequency>900 && wave_frequency < 1000)
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }else{
            digitalWrite(LED_BUILTIN, LOW);
        }


    }else{
        end_time=micros();
    }
}

void rf_receive_init( )
{
    pinMode(RF_RECEIVE_PIN, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(RF_RECEIVE_PIN), rf_receive_ISR, CHANGE);
}

