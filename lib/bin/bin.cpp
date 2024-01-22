// Geschreven door Kevind en Xander

#include <stdio.h>

// Geschreven door Kevin
int toInt( char* str )
{
    /*Get length*/
    int length=0;
    while(str[++length]);

    /*Convert chars to int*/
    int multiplier=1;
    int result=0;
    for(int i=length-1;i>=0;i--)
    {
        int n = str[i]-48;
        n=n*multiplier;
        result=result+n;
        multiplier=multiplier*10;
    }

    return result;
}

// Geschreven door Xander
void fill_binary_array(char* array, int input)
{
    for(int i=0; i<8; i++)
    {
        array[i] = (input >> i) & 1;
    }
}