#include <zoeker.h>
#include <Arduino.h>

void seeker_init()
{
    pinMode(SEEKER_STEP_PIN, OUTPUT);
    pinMode(SEEKER_EN_PIN, OUTPUT);
    pinMode(SEEKER_DETECT_PIN, INPUT);
    pinMode(SEEKER_DIR_PIN, OUTPUT);

    digitalWrite(SEEKER_EN_PIN, LOW);
}

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

void seeker_direction( char dir )
{
    digitalWrite(SEEKER_DIR_PIN, dir);
}