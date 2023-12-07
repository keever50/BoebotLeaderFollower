#include <rf_receive2.h>
#include <Arduino.h>

volatile float rf_debug_frequency;
volatile float rf_debug_duty;
volatile int rf_detection;

volatile char rf_receive_data_ready;
volatile float rf_receive_bitbuffer[8]={0};

char rf_receive_get_data_ready( char reset )
{
    char flag = rf_receive_data_ready;
    if(reset)
    {
        rf_receive_data_ready=0;
    }
    return flag;
}

float rf_receive_get_data( int bit )
{
    return rf_receive_bitbuffer[bit];
}

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
    static int bit_count=0;

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

        //If no data has been received before
        if(rf_receive_data_ready==0)
        {
            //Target frequency
            if(wave_frequency>RF_RECEIVE_FREQ_LOW && wave_frequency < RF_RECEIVE_FREQ_HI)
            {
                digitalWrite(LED_BUILTIN, HIGH);

                //Target duty
                if(duty > 0.60 || duty < 0.40)
                {
                    if(bit_count<8)
                    {
                        bit_count=bit_count+1;
                        rf_receive_bitbuffer[bit_count]=duty;
                    }
                }

            }else{
                digitalWrite(LED_BUILTIN, LOW);
                if(bit_count>0)
                {
                    rf_receive_data_ready=1;
                    bit_count=0;
                }
                
                
            }
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

