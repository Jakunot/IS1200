/* inputs.c

    This file was written 2022 by J Otieno

    this file initializes the switches and buttons.

   For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/* input for the switches */

int getsw( void ){
    int value = PORTD;
    return (value >> 8) & 0x000F;
}

/* inputs for the buttons */

int getbtns( void ){
    int value = PORTD;
    return ((((value >> 5) & 0x0007)  <<1)| ((PORTF >> 1) & 0x1)); 
}