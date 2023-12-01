#include <rf_receive.h>
#include <Arduino.h>

bool rf_data_incoming=0;
bool rf_data_ready = 0;
float rf_freq=0;
float rf_duty=0;
int rf_signal_buffer[RF_R_DATA_BUFFER_SIZE]={0};

int rf_receive_data_buffer( int pos )
{
    return rf_signal_buffer[pos];
}

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

float rf_receive_freq()
{
    return rf_freq;
}

float rf_receive_duty()
{
    return rf_duty;
}

void rf_recieve_init( )
{
    pinMode(RF_R_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(RF_R_PIN), rf_receive_ISR, CHANGE);
}



void rf_receive_ISR()
{
    static unsigned long t_prev;
    static unsigned long t_on;
    static unsigned long t_total;
    static float f;
    static float duty;
    static int byte_count;

    int state = digitalRead(RF_R_PIN);
    if(state == HIGH)
    {
        t_on = micros();
        t_total = (t_on - t_prev);
        f = (1000000/t_total);
        t_prev = t_on;
        rf_freq = f;
        
        if(abs(f-1000)<50)
        {
            
            
            //OFF
            if(rf_duty > 0.25-RF_PWM_TOLERANCE && rf_duty < 0.25+RF_PWM_TOLERANCE)
            {
                rf_data_incoming=true;
                rf_signal_buffer[byte_count]=0;
                byte_count++;
            }
            //NONE
            if(rf_duty > 0.50-RF_PWM_TOLERANCE && rf_duty < 0.50+RF_PWM_TOLERANCE)
            {
                rf_data_incoming=true;    
                
            }
            //ON
            if(rf_duty > 0.75-RF_PWM_TOLERANCE && rf_duty < 0.75+RF_PWM_TOLERANCE)
            {
                rf_data_incoming=true;
                rf_signal_buffer[byte_count]=1; 
                byte_count++;              
            }          

            if(byte_count>=RF_R_DATA_BUFFER_SIZE-1)
            {
                byte_count=0;
            }  


        }else{
            rf_data_incoming=false;
            if(byte_count>0)
            {
                rf_data_ready=true;
            }
            byte_count = 0;
        }

    }else{
        float delta = micros()-t_on;
        duty = delta/t_total;
        rf_duty = duty;
    } 
}