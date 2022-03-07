/* 
  mipslabwork.c

  This file written 2015 by F Lundevall
  Updated 2017-04-21 by F Lundevall
  This file was edited 2022 by E Beshir & J Otieno

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include <stdio.h>
#include <stdlib.h>

float random_number = 0;

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr(void)
{
  if (IFS(0) & 0x100)
  {
    timeoutcount++;
    IFSCLR(0) = 0x100;
    if (timeoutcount == 10)
    { // timeoutcount wraps at 10
      timeoutcount = 0;
    }
  }
}

// Set the necessary settings before the program starts
void labinit(void)
{
  volatile int *trise = (volatile int *)0xbf886100;
  TRISECLR = 0xff;  // Set as output (LED:S)
  TRISDSET = 0xfe0; // Set as input (BTN 2-4, SW 1-4)
  TRISFSET = 0x2;   // Set as input (BTN 1)
  PORTE = 0x0;      // LED:s
}

// We use the TIMER to get randomness
void getRandom()
{
  random_number = TMR2 % 5;
  random_number /= 10;
  random_number += 0.5;
  random_number *= getRandomSign();
}

int getRandomSign()
{
  if (TMR2 % 10 < 5)
  {
    return -1;
  }
  return 1;
}

/* This function is called repetitively from the main program */
void labwork()
{
  quicksleep(1 << 15);
  // if program is in game 
  if (in_game)
  {
    set_in_game();
    if (infinity_mode)
    {
      set_infinity_mode();
    }
    else if (ai_mode)
    {
      set_ai_mode();
    }
    set_pixel(ball_pos_X, ball_pos_Y, ball_size, ball_size);
    convert_to_display();
    if (!end_of_game)
    {
      display_image(0, oled_display);
    }
    player_movement();
    ball_mechanics();
    updateGame();
    ledControl();
    quit_game();
    // initiate game
    if (start_of_game)
    {
      quicksleep(1 << 23);
      start_of_game = 0;
      getRandom();
      ball_speed_Y = random_number;
      ball_speed_X = getRandomSign();
    }
    clear_array_display();
  }
  /* MENU OPTIONS */
  else if (in_menu)
  {
    show_menu();
  }
  else if (in_mode_menu)
  {
    show_modes_menu();
  }
  else if (in_scoreboard)
  {
    show_scoreboard();
  }
}
