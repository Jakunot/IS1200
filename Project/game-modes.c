#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>


int in_game = 0;
int arcade_mode = 0;
int player1_score = 0;
int player2_score = 0;

void onePlayer(btns)
{
    player1_movement(btns);
    updateGame();
    difficulty();
    collide();

    clearDisplay();
    setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
    setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
    setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
    translateToImage();
    display_image(0, oled_display);

}