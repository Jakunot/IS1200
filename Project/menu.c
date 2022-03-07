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

// variables to keep track of current screen
int in_menu = 1;  
int in_game = 0;  
int in_mode_menu = 0; 
int in_scoreboard = 0;

// cursors for menu options
int menu_option = 0;
int modes_option = 0;

// game modes
int default_mode = 1; 
int ai_mode = 0;
int infinity_mode = 0;

// Variables that are needed for (quicksleeps/delays) in the start and end of every screen
int start_of_menu = 1;
int start_of_modes = 0;
int start_of_scoreboard = 0;
int start_of_game = 1;
int end_of_game = 0;


/* ----------------------------MAIN MENU-------------------------------*/

/* Show main menu and its options. */
void show_menu()
{
    set_menu();
    if (start_of_menu)
    {
        start_of_menu = 0;
        menu_option = 0;
        move_menu_cursor();
    }
}

/* Displays cursor movement in main menu */
void move_menu_cursor(void)
{
    display_string(0, "  - PONG MENU -");
    switch (menu_option)
    {
    case 0:
        display_string(1, "> START");
        display_string(2, "  GAME MODES");
        display_string(3, "  SCOREBOARD");
        break;
    case 1:
        display_string(1, "  START");
        display_string(2, "> GAME MODES");
        display_string(3, "  SCOREBOARD");
        break;
    case 2:
        display_string(1, "  START");
        display_string(2, "  GAME MODES");
        display_string(3, "> SCOREBOARD");
        break;
    }
    display_update();
}

/* Set menu state based on which menu option is selected by user */
void set_menu(void)
{
    quicksleep(1 << 20);
  // if cursor is on "Start" and btn1 is pressed -> set following states
    if (getbtns() & 0x1 && menu_option == 0)
    {
        in_menu = 0;
        menu_option = 0;
        start_of_game = 1;
        in_game = 1;
        // leds = 0xf;
    }
    else if (getbtns() & 0x1 && menu_option == 1)
    {
        in_menu = 0;
        menu_option = 0;
        in_mode_menu = 1;
        start_of_modes = 1;
    }
    else if (getbtns() & 0x1 && menu_option == 2)
    {
        in_menu = 0;
        menu_option = 0;
        in_scoreboard = 1;
        start_of_scoreboard = 1;
    }
    else if ((getbtns() & 0x4) && menu_option != 2)
    {
        menu_option++;
        move_menu_cursor();
    }
    else if ((getbtns() & 0x8) && menu_option != 0)
    {
        menu_option--;
        move_menu_cursor();
    }
}

/* ----------------------------MODES-------------------------------*/

/* Show Modes Menu */
void show_modes_menu()
{
    set_mode();
    if (start_of_modes) 
    {
        start_of_modes = 0;
        modes_option = 0;
        move_modes_cursor();
    }
}

/* Displays cursor movement in modes menu */
void move_modes_cursor()
{
    display_string(0, "  - MODES -");
    switch (modes_option)
    {
    case 0:
        display_string(1, "> 1 vs 1");
        display_string(2, "  Player vs Comp");
        display_string(3, "  Infinity");
        break;
    case 1:
        display_string(1, "  1 vs 1");
        display_string(2, "> Player vs Comp");
        display_string(3, "  Infinity");
        break;
    case 2:
        display_string(1, "  1 vs 1");
        display_string(2, "  Player vs Comp");
        display_string(3, "> Infinity");
        break;
    }
    display_update();
}

/* Set mode state based on which mode-menu option is selected by user */
void set_mode()
{
    quicksleep(1 << 20); //! can we replace quicksleep with delay?
  // when cursor is on first option (1 vs 1) and btn1 is pressed game is selected (1v1 is ON) 
    if (getbtns() & 0x1 && modes_option == 0)
    {
        start_of_menu = 1;
        in_menu = 1;
        default_mode = 1;

        in_mode_menu = 0;
        modes_option = 0;
        ai_mode = 0;
        infinity_mode = 0;
    }
  // when cursor is on second option (Player vs AI) and btn1 is pressed game is selected (AI is ON)
    else if (getbtns() & 0x1 && modes_option == 1)
    {
        start_of_menu = 1;
        in_menu = 1;
        ai_mode = 1;

        in_mode_menu = 0;
        modes_option = 0;
        default_mode = 0;
        infinity_mode = 0;
    }
  // when cursor is on third option (infinity) and btn1 is pressed game is selected (infinity mode is on)
    else if (getbtns() & 0x1 && modes_option == 2)
    {
        start_of_menu = 1;
        in_menu = 1;
        infinity_mode = 1;

        in_mode_menu = 0;
        modes_option = 0;
        default_mode = 0;
        ai_mode = 0;
    }
  // move cursor down
    else if ((getbtns() & 0x4) && modes_option != 2)
    {
        modes_option++;
        move_modes_cursor();
    }
  // move cursor up
    else if ((getbtns() & 0x8) && modes_option != 0)
    {
        modes_option--;
        move_modes_cursor();
    }
}


/* ----------------------------SCOREBOARD-------------------------------*/

/* Show scoreboard and its values. */
void show_scoreboard()
{
    scoreboard();
    if (start_of_scoreboard)
    {
        display_string(0, scoreboard_pos1); // Convert elements to string!
        display_string(1, scoreboard_pos2);
        display_string(2, scoreboard_pos3);
        display_string(3, "<< BTN1");
        display_update();
        start_of_scoreboard = 0;
    }
}


void scoreboard()
{
    quicksleep(1 << 20);
    if (getbtns() & 0x1)
    {
        in_menu = 1;
        in_scoreboard = 0;
        start_of_menu = 1;
    }
}

/* ----------------------------IN GAME-------------------------------*/

// quit game by switching SW4
void quit_game()
{
    if (in_game && (getsw() & 0x8))
    {
        reset_game();
        game_end();
    }
}