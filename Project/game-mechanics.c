/* 
    game-mechanics.c

    This file was written 2022 by E Beshir & J otieno

    For copyright and licensing, see file COPYING 

*/
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// Paddle variables 
float pad_height = 8;
float pad_width = 4;
float pad_speed = 1.5;

int leds = 0x0;

// player variables
float pad1_pos_X = 0;       
float pad1_pos_Y = 32 / 2 - 5;

float pad2_pos_X = 127 - 4;
float pad2_pos_Y = 32 / 2 - 5;

// Ball variables
float ball_size = 3;         
float ball_speed_X = -1;
float ball_speed_Y = 0;
float ball_pos_X = 128 / 2 - 2;
float ball_pos_Y = 16;
float max_ball_speed_X = 3;


/*
    This functions enables movement of padels using the IO buttons (btn).
    It increases and decreases vertical position of padels when corresponding 
    btn is pressed
 */
void player_movement(void)
{ 
  /* Player 2 - increases vertical position of padel 2 when btn1 is pressed */
    if (default_mode && (getbtns() & 0x1) && (pad2_pos_Y < (31 - pad_height)))
    {
        pad2_pos_Y += pad_speed;
    }
  // Player 2 - decrease vertical position of padel 2 when btn2 is pressed
    else if (default_mode && (getbtns() & 0x2) && (pad2_pos_Y > 0))
    {
        pad2_pos_Y -= pad_speed;
    }

  /* Player 1 - increases vertical position of padel 1 when btn4 is pressed */
    if ((getbtns() & 0x4) && (pad1_pos_Y < (31 - pad_height)))
    {
        pad1_pos_Y += pad_speed;
    }
  /* Player 1 - decrease vertical position of padel 2 when btn3 is pressed */
    else if ((getbtns() & 0x8) && (pad1_pos_Y > 0))
    {
        pad1_pos_Y -= pad_speed;
    }
}


void ball_mechanics(void)
{
    /*--- PADEL RIGHT ---*/

  // check if collision 
    if (ball_speed_X < 0 && (ball_pos_X >= pad1_pos_X) && (ball_pos_X <= (pad1_pos_X + pad_width)) && ((ball_pos_Y + ball_size) > pad1_pos_Y) && (ball_pos_Y < (pad1_pos_Y + pad_height)))
    {
    // change direction 
        ball_speed_X *= -1;
    // increase speed if under speed limit
        if (ball_speed_X < max_ball_speed_X)
        {
      // increase speed
            ball_speed_X += 0.5;
        }

    // checks if ball comes from above and hits pad its trajectory should angle down
        if ((ball_pos_Y + ball_size / 2) < pad1_pos_Y + pad_height / 2 && ball_speed_Y > -1.5)
        {
            if (ball_speed_X < -2)
            {
                ball_speed_Y -= 0.55;
            }
            else
            {
                ball_speed_Y -= 0.35;
            }
        }
    // check if ball is approaching from below (ball is moving up) towards pad position 
        else if ((ball_pos_Y + ball_size / 2) > pad1_pos_Y + 2 * pad_height / 2 && ball_speed_Y < 1.5)
        {
    
            if (ball_speed_X < -2)
            {
                ball_speed_Y += 0.55;
            }
            else
            {
                ball_speed_Y += 0.35;
            }
        }
    // Survival score increment
        if (infinity_mode)
        {
            infinity_score++;
        }
    }
    /*--- PADEL LEFT ---*/
    else if (ball_speed_X > 0 && ((ball_pos_X + ball_size) >= pad2_pos_X) && ((ball_pos_X + ball_size) <= pad2_pos_X + pad_width) && (((ball_pos_Y + ball_size) > pad2_pos_Y)) && (ball_pos_Y < (pad2_pos_Y + pad_height)))
    {
        ball_speed_X *= -1;
        if (ball_speed_X > -max_ball_speed_X)
        {
            ball_speed_X -= 0.5;
        }
        if ((ball_pos_Y + ball_size / 2) < pad2_pos_Y + pad_height / 2 && ball_speed_Y > -1.5)
        {
            if (ball_speed_X > 2)
            {
                ball_speed_Y -= 0.55;
            }
            else
            {
                ball_speed_Y -= 0.35;
            }
        }
        else if ((ball_pos_Y + ball_size / 2) > pad2_pos_Y + 2 * pad_height / 2 && ball_speed_Y < 1.5)
        {
            if (ball_speed_X > 2)
            {
                ball_speed_Y += 0.55;
            }
            else
            {
                ball_speed_Y += 0.35;
            }
        }
    }

    if ((ball_pos_X + ball_size) < 0 || ball_pos_X > 128)
    {
        quicksleep(1 << 16);
        goal();
    }
}

