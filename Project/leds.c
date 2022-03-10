/* 
    leds.c

    This file was written 2022 by E Beshir & J otieno

    For copyright and licensing, see file COPYING 

*/

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

void ledControl()
{
    PORTE = leds;
}

// lightshow winner is 0 for left player and 1 for right player. Lights that move back and forth along one of the sides of the 8-LED lights.
int shiftDir = 1; // Höger
void lightshow(int winner)          // test if left side (0) or right side (1) wins
{
    PORTE = 0x8;
    int count = 0;
    if (!winner)                      // NOT winner == 0
    { // LEFT
        PORTE <<= 4;
        while (count < 48)
        {
            if (PORTE & 0x10)
            {
                shiftDir = 0;
            }
            else if (PORTE & 0x80)
            {
                shiftDir = 1;
            }
            if (shiftDir)
            {
                PORTE >>= 1;
            }
            else if (!shiftDir)
            {
                PORTE <<= 1;
            }
            count++;
            quicksleep(1 << 19);
        }
    }
    else
    { // RIGHT
        while (count < 48)
        {
            if (PORTE & 0x1)
            { 
                shiftDir = 0;
            }
            else if (PORTE & 0x8)
            {
            shiftDir = 1;
            }
            if (shiftDir)
            {
                PORTE >>= 1;
            }
            else if (!shiftDir)
            {
                PORTE <<= 1;
            }
            count++;
            quicksleep(1 << 19);
        }
    }
}