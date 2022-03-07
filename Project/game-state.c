/* 
    game-state.c

    This file was written 2022 by E Beshir & J otieno

    For copyright and licensing, see file COPYING 

*/
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

/* global variables to update the score of the players. */
int player1_score = 0;
int player2_score = 0;

/* variables to update the score and initialize an array to save  highscores. */
int infinity_score = 0;
int current_scoreboard_list[3] = {0, 0, 0};

/* variables to display scoreboard - int to char array */
char scoreboard_pos1[10] = " #1 ";
char scoreboard_pos2[10] = " #2 ";
char scoreboard_pos3[10] = " #3 ";


char buffer1[sizeof(int) * 3 + 2];
char buffer2[sizeof(int) * 3 + 2];
char buffer3[sizeof(int) * 3 + 2];

// AI difficulty
float ai_pad_speed = 0.75;

char concat_score[16];
char space_the_score[7] = "       ";

/* Game Logic */
void updateGame(void)
{
    ball_pos_X += ball_speed_X;
    ball_pos_Y += ball_speed_Y;
  // Roof and floor ball bounce
    if (ball_pos_Y < 0 || ball_pos_Y > (31 - ball_size))
    {
        ball_speed_Y *= -1;
    }
}

/* Reset all the variables back to their default values. */
void reset_game()
{
  // reset and center the pong components
    pad1_pos_X = 0;
    pad1_pos_Y = 32 / 2 - pad_height / 2;

    pad2_pos_X = 127 - pad_width;
    pad2_pos_Y = 32 / 2 - pad_height / 2;

    ball_pos_X = 128 / 2 - ball_size / 2;
    ball_pos_Y = 16;

    clear_array_display();
    set_pixel(pad1_pos_X, pad1_pos_Y, pad_width, pad_height);
    set_pixel(pad2_pos_X, pad2_pos_Y, pad_width, pad_height);
    set_pixel(ball_pos_X, ball_pos_Y, ball_size, ball_size);

    convert_to_display();
    display_image(0, oled_display);

    start_of_game = 1;
}

/* check if goal - if ball passed player-pad */
void goal()
{
  // Check for goals condition if ball is less than 0
    if (ball_pos_X < 0)
    {
        player2_score++;
    }
    else if (ball_pos_X > (128 - ball_size))
    {
        player1_score++;
    }
    reset_game();
    if (player1_score == 4 || player2_score == 4)
    {
        game_end(); 
    }

  /* present player score from infinity mode */
    if (infinity_mode && (player2_score == 1 || player1_score == 1))
    {
        display_string(0, "");
        display_string(1, "   Your score!");
        display_string(2, concat_score);
        display_update();
        game_end();
    } 
}

/* display who wins through text and set the scoreboard if in survival mode. */
void game_end(void)
{
    if (player1_score == 2)
    {
        display_string(0, "");
        display_string(1, "LEFT SIDE WINS!");
        display_string(2, "      <<<");
        display_string(3, "");
        display_update();
        lightshow(0); // triggers lightshow
    }
    else if (player2_score == 2)
    {
        display_string(0, "");
        display_string(1, "RIGHT SIDE WINS!");
        display_string(2, "      >>>");
        display_string(3, "");
        display_update();
        lightshow(1);
    }

  // update the scoreboard:
    if (infinity_mode == 1)
    {
        if (current_scoreboard_list[0] < infinity_score)
        {
      // if there is values on the scoreboard
            if (current_scoreboard_list[0] != 0)
            {

                strcpy(scoreboard_pos1, " #1 ");

                strcpy(scoreboard_pos2, " #2 ");
                snprintf(buffer2, sizeof buffer2, "%d", current_scoreboard_list[0]);
                strcat(scoreboard_pos2, buffer2);

                strcpy(scoreboard_pos3, " #3 ");
                snprintf(buffer3, sizeof buffer3, "%d", current_scoreboard_list[1]);
                strcat(scoreboard_pos3, buffer3);

                current_scoreboard_list[2] = current_scoreboard_list[1];
                current_scoreboard_list[1] = current_scoreboard_list[0];
            }
            snprintf(buffer1, sizeof buffer1, "%d", infinity_score);
            strcat(scoreboard_pos1, buffer1);
            current_scoreboard_list[0] = infinity_score;
        }
        else if (current_scoreboard_list[1] < infinity_score)
        {
            if (current_scoreboard_list[1] != 0)
            {
        // copy and save '#2' of scoreboard_pos2 to strcpy
                strcpy(scoreboard_pos2, " #2 ");
        // copy and save '#3' of scoreboard_pos3 to strcpy
                strcpy(scoreboard_pos3, " #3 ");
        // save value of pos2 to buffer3
                snprintf(buffer3, sizeof buffer3, "%d", current_scoreboard_list[1]);
        // concatenate value in buffer3 to scoreboard_pos3 ('#3')
                strcat(scoreboard_pos3, buffer3);
        // now assign current value in pos2 to pos3
                current_scoreboard_list[2] = current_scoreboard_list[1];
            }
      // save value of infinity score in buffer2
        snprintf(buffer2, sizeof buffer2, "%d", infinity_score);
      // concat value of buffer2 to scoreboard_pos2 ('#2')
        strcat(scoreboard_pos2, buffer2);
      // now assign current value of infnity_score to list1
            current_scoreboard_list[1] = infinity_score;
        }
        else if (current_scoreboard_list[2] < infinity_score)
        {
            if (current_scoreboard_list[2] != 0)
            {
                strcpy(scoreboard_pos3, " #3 ");
            }
        snprintf(buffer3, sizeof buffer3, "%d", infinity_score);
        strcat(scoreboard_pos3, buffer3);
            current_scoreboard_list[2] = infinity_score;
        }
    infinity_score = 0;
    }
  // set variables to correct values
    in_game = 0;
    in_menu = 1;
    start_of_menu = 1;
    start_of_game = 1;
    player1_score = 0;
    player2_score = 0;
}

// sets basic components for any game
void set_in_game()
{
    clear_string_display();
    set_pixel(pad1_pos_X, pad1_pos_Y, pad_width, pad_height);
    set_pixel(pad2_pos_X, pad2_pos_Y, pad_width, pad_height);
}

// Set AI padel speeds for higher difficulties using switches
void set_ai_difficulty()
{
    if (ai_mode)
    {
        if (getsw() & 0x1)
        {
            ai_pad_speed = 1;
        }
        else if (getsw() & 0x2)
        {
            ai_pad_speed = 1.5;
            max_ball_speed_X = 3.5;
        }
        else if (getsw() & 0x4)
        {
            ai_pad_speed = 2;
            max_ball_speed_X = 4;
        }   
        else
        {
            ai_pad_speed = 0.80;
        }
    }
}

void set_infinity_mode()
{
    if (ball_pos_Y < pad_height / 2)
    {
        pad2_pos_Y = 0;
    }
    else if ((ball_pos_Y + ball_size) > (31 - pad_height / 2))
    {
        pad2_pos_Y = 31 - pad_height;
    }
    else
    {
        pad2_pos_Y = ball_pos_Y + ball_size / 2 - pad_height / 2;
    }
    strcpy(concat_score, space_the_score);
    strcat(concat_score, itoaconv(infinity_score));
    display_string(0, concat_score);
}


void set_ai_mode()
{
    set_ai_difficulty();
    if (ball_pos_X > 127 / 2)
    {
        if ((pad2_pos_Y + pad_height / 2) < (ball_pos_Y + ball_size / 2) && pad2_pos_Y < (31 - pad_height))
        {
            pad2_pos_Y += ai_pad_speed;
        }
        else if ((pad2_pos_Y + pad_height / 2) > (ball_pos_Y + ball_size / 2) && pad2_pos_Y > 0)
        {
            pad2_pos_Y -= ai_pad_speed;
        }
    }
    else
    {
        if ((pad2_pos_Y + pad_height / 2) < 14.8)
        {
            pad2_pos_Y += 0.1;
        }
        else if ((pad2_pos_Y + pad_height / 2) > 15.2)
        {
            pad2_pos_Y -= 0.1;
        }
    }
}