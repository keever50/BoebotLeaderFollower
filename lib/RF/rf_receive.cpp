#include <rf_receive.h>
#include <Arduino.h>

volatile bool rf_data_incoming=0;
volatile bool rf_data_ready = 0;
volatile int rf_signal_buffer[RF_R_DATA_BUFFER_SIZE]={0};

/*
Returns the data received using the parameter int pos.
The amount of bytes to be received is max RF_R_DATA_BUFFER_SIZE.
*/
int rf_receive_data_buffer( int pos )
{
    if(pos >=0 && pos<RF_R_DATA_BUFFER_SIZE)
    {
        return rf_signal_buffer[pos];
    }
    return 0;
}

/*Return true when data is ready to be read. 
Set reset to true, when this data_ready flag has to be set back to zero automatically.*/
bool rf_receive_data_ready( bool reset ) 
{
    bool rdy = rf_data_ready;
    if(reset)
    {
        rf_data_ready = 0;
    }
    return rdy;
}

bool rf_receive_data_incoming()
{
    return rf_data_incoming;
}

void rf_receive_init( )
{
    pinMode(RF_R_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RF_R_PIN), rf_receive_ISR, CHANGE);
}



void rf_receive_ISR()
{
    static unsigned long t_previously;
    static unsigned long t_start;
    static unsigned long wave_period;
    static float wave_frequency;
    static int byte_count;
    static float duty;

    //When the pin changed is high AND bytes we stored is less than the buffer size
    int state = digitalRead(RF_R_PIN);
    if(state == HIGH && byte_count < RF_R_DATA_BUFFER_SIZE)
    {
        t_start = micros();
        wave_period = (t_start - t_previously);
        wave_frequency = (1000000/wave_period);
        t_previously = t_start;
        
        //When the wave frequency matches within tolerances
        if(abs(wave_frequency-RF_MODULATION_FREQUENCY_HZ)<RF_FREQUENCY_TOLERANCE_HZ)
        {
            //Check if PWM received matches either 25,50 or 75%, within tolerances
            //OFF Store zeros
            if(duty >= 0.25-RF_PWM_TOLERANCE && duty <= 0.25+RF_PWM_TOLERANCE)
            {
                rf_data_incoming=true;
                rf_signal_buffer[byte_count]=0;
                byte_count++;
            }
            //NONE Do nothing, just listen
            if(duty >= 0.50-RF_PWM_TOLERANCE && duty <= 0.50+RF_PWM_TOLERANCE)
            {
                
                rf_data_incoming=true;    
            }
            //ON Store ones
            if(duty >= 0.75-RF_PWM_TOLERANCE && duty <= 0.75+RF_PWM_TOLERANCE)
            {
                rf_data_incoming=true;
                rf_signal_buffer[byte_count]=1; 
                byte_count++;              
            }          
        //If the frequency does not match
        }else{
            //Reset variables and set data ready flag to true
            rf_data_incoming=false;
            if(byte_count>0)
            {
                rf_data_ready=true;
            }
            byte_count = 0;
        }

    }else{
        float delta = micros()-t_start;
        duty = delta/wave_period;
    } 
}