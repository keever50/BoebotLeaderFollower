/*Geschreven/Written by Kevin Witteveen*/

#include <seeker.h>
#include <Arduino.h>

/*Configurates pins for basic manual functionality*/
void seeker_init()
{
    pinMode(SEEKER_STEP_PIN, OUTPUT);
    pinMode(SEEKER_EN_PIN, OUTPUT);
    pinMode(SEEKER_DETECT_PIN, INPUT);
    pinMode(SEEKER_DIR_PIN, OUTPUT);

    digitalWrite(SEEKER_EN_PIN, LOW);
}

/*Manual step and detect*/
char seeker_stepdetect()
{
    static int toggle;
    for(int i=0;i<SEEKER_STEPS_PER_READ;i++)
    {
        digitalWrite(SEEKER_STEP_PIN, toggle);
        toggle=!toggle;
        delayMicroseconds(SEEKER_INTERVAL);
    }

    return digitalRead(SEEKER_DETECT_PIN);
}

/*Sets the direction of the seeker. This will not work properly in auto mode.*/
void seeker_direction( char dir )
{
    digitalWrite(SEEKER_DIR_PIN, dir);
}

/*Configurates and starts hardware timers and interrupts for automatic control. (seeker_init() must be called before)*/
void seeker_init_auto()
{
    /*Timer 2 set*/

    /*Reset*/
    TCCR2A=0;
    TCCR2B=0;
    TIMSK2 = 0;

    /*Config*/
    TCCR2A |= 1<<COM2A0; /*Toggle OC2A on compare match*/
    TCCR2A |= 1<<WGM21; /*CTC*/
    TCCR2B |= 1<<CS22 | 1<<CS21 | 1<<CS20; /*Clock set*/

    /*Interrupt enable*/
    TIMSK2 |= 1<<OCF2A;

    pinMode(13, OUTPUT);

    /*Speed set hz=(F_CPU/DIV)/(2*freq)*/
    OCR2A = 5;
}

/*Interrupt for automatic control*/
volatile char seeker_did_full_revolution_flag=0;
volatile char seeker_detect_buffer[SEEKER_STEPS_PER_REVOLUTION];
volatile int seeker_current_step=0;
volatile char seeker_last_detect=0;
volatile char seeker_step_toggler=0;
ISR(TIMER2_COMPA_vect)
{
    if(seeker_step_toggler)
    {
        char det = !digitalRead(8);

        if(det>seeker_last_detect){ /*On rising*/
            seeker_detect_buffer[seeker_current_step]=1;
            digitalWrite(13, 1); 
        }else{
            seeker_detect_buffer[seeker_current_step]=0;
            digitalWrite(13, 0); 
        }
        

        seeker_last_detect=det;
        /*Reset on last step*/
        seeker_current_step++;
        if(seeker_current_step>=SEEKER_STEPS_PER_REVOLUTION)
        {
            seeker_current_step=0;
            seeker_did_full_revolution_flag=1;
        }
    }
    
    seeker_step_toggler=!seeker_step_toggler;
}

/*Returns a detection from auto mode. contains SEEKER_STEPS_PER_REVOLUTION detections*/
char seeker_get_detections( int addr )
{
    if(addr>=0 && addr<SEEKER_STEPS_PER_REVOLUTION)
    {
        return seeker_detect_buffer[addr];
    }else{
        return 0;
    }
}

/*Returns if seeker has made a full revolution in auto mode. This also means new scan data is ready. This flag stays up till reset.*/
char seeker_did_full_revolution( char reset )
{
    char flag = seeker_did_full_revolution_flag;
    if(reset==1){
        seeker_did_full_revolution_flag=0;
    }
    return flag;
}

/*Get current automatic step*/
int seeker_get_step()
{
    return seeker_current_step;
}

/*Converts all detections into an average direction. This is not made for multiple IR sources at once as this will average them into one.*/
float seeker_get_degrees()
{
    float avg=0.0;
    float count=0.0;

    /*Averaging the IR detections*/
    for(int i=0;i<SEEKER_STEPS_PER_REVOLUTION;i++)
    {
      char det = seeker_get_detections(i);
      if(det)
      {
        Serial.print("Detection on ");
        Serial.println(i);
        avg=avg+i;
        count++;
      }
    }

    if(count == 0)
    {
        return SEEKER_NOTHING_FOUND;
    }

    avg=avg/count;

    /*Converting to degrees*/
    float ratio = avg/(SEEKER_STEPS_PER_REVOLUTION);
    float beacon_angle=ratio*360.0; 

    return 180-beacon_angle;
}