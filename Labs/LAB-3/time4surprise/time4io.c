/* time4io.c

    This file was written 2022 by J Otieno

   For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ){
    int value = PORTD;
    return (value >> 8) & 0x000F;
}

int getbtns( void ){
    int value = PORTD;
    return (value >> 5) & 0x0007;
}