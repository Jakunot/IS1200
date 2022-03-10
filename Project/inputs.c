/* 
    inputs.c

    This file was written 2022 by E Beshir & J otieno

    For copyright and licensing, see file COPYING 

*/
#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

/*
The four least significant bits of the return value should contain data from switches
SW4, SW3, SW2, and SW1. SW1 corresponds to the least significant bit. All other bits
of the return value must be zero.
*/
int getsw(void)
{
    return ((PORTD >> 8) & 0xf);
}

/*
The 3 least significant bits of the return value must contain current data from push
buttons BTN4, BTN3, BTN2, and BTN1.
*/
int getbtns(void)
{
    return ((((PORTD >> 5) & 0x7) << 1) | ((PORTF >> 1) & 0x1));
}
