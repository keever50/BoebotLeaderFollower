/*
    Made by Kevin Witteveen 
*/

#pragma once

#define PWMGEN1_DEFAULT_CLK_SEL 2;

void pwmgen1_start();

void pwmgen1_set_clock_bits( char bits );

void pwmgen1_set_frequency( int freq );

void pwmgen1_set_duty_A( float duty );

void pwmgen1_set_duty_B( float duty );

void pwmgen1_clock_mode( char mode );