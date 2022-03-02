#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

// paddle movements
float paddle_height = 7;
float paddle_width = 4;
float paddle_speed = 1;

float paddle1_xPos = 0;
float paddle1_yPos = 32 / 2 - 5;
int player1Points = 0;

float paddle2_xPos = 127 - 4;
float paddle2_yPos = 32 / 2 - 5;
int player2Points = 0;

// ball movements
float ball_size = 3;
float ball_speedX = 1;
float ball_speedY = 0;
float ball_xPos = 128 / 2 - 2;
float ball_yPos = 16;
float max_ball_speedX = 4;

// CPU-movements
float randomNumber = 0;
float ai_paddle_speed = 0.75;

void collide(void)
{
    // paddle 1
    if (ball_speedX < 0 && (ball_xPos >= paddle1_xPos) && (ball_xPos <= (paddle1_xPos + paddle_width)) && ((ball_yPos + ball_size) > paddle1_yPos) && (ball_yPos < (paddle1_yPos + paddle_height)))
    {
        ball_speedX *= -1;
        if (ball_speedX < max_ball_speedX)
        {
            ball_speedX += 0.5;
        }
        if ((ball_yPos + ball_size / 2) < paddle1_yPos + paddle_height / 2 && ball_speedY > -1.5)
        {
            if (ball_speedX < -2)
            {
                ball_speedY -= 0.55;
            }
            else
            {
                ball_speedY -= 0.35;
            }
        }
        else if ((ball_yPos + ball_size / 2) > paddle1_yPos + 2 * paddle_height / 2 && ball_speedY < 1.5)
        {
            if (ball_speedX < -2)
            {
                ball_speedY += 0.55;
            }
            else
            {
                ball_speedY += 0.35;
            }
        }
        // Survival score increment
        if (survivalMode)
        {
            survivalScore++;
        }
    }
    // paddle 2
    else if (ball_speedX > 0 && ((ball_xPos + ball_size) >= paddle2_xPos) && ((ball_xPos + ball_size) <= paddle2_xPos + paddle_width) && (((ball_yPos + ball_size) > paddle2_yPos)) && (ball_yPos < (paddle2_yPos + paddle_height)))
    {
        ball_speedX *= -1;
        if (ball_speedX > -max_ball_speedX)
        {
            ball_speedX -= 0.5;
        }
        if ((ball_yPos + ball_size / 2) < paddle2_yPos + paddle_height / 2 && ball_speedY > -1.5)
        {
            if (ball_speedX > 2)
            {
                ball_speedY -= 0.55;
            }
            else
            {
                ball_speedY -= 0.35;
            }
        }
        else if ((ball_yPos + ball_size / 2) > paddle2_yPos + 2 * paddle_height / 2 && ball_speedY < 1.5)
        {
            if (ball_speedX > 2)
            {
                ball_speedY += 0.55;
            }
            else
            {
                ball_speedY += 0.35;
            }
        }
    }

    if ((ball_xPos + ball_size) < 0 || ball_xPos > 128)
    {
        quicksleep(1 << 16);
        goal();
    }
}

// enable paddle movement
void player1_movement(void)
{
    if (defaultMode && (getbtns() & 0x1) && (paddle2_yPos < (31 - paddle_height)))
    {
        paddle2_yPos += paddle_speed;
    }
    else if (defaultMode && (getbtns() & 0x2) && (paddle2_yPos > 0))
    {
        paddle2_yPos -= paddle_speed;
    }
}


void player2_movement(void)
{
    if ((getbtns() & 0x4) && (paddle1_yPos < (31 - paddle_height)))
    {
        paddle1_yPos += paddle_speed;
    }
    else if ((getbtns() & 0x8) && (paddle1_yPos > 0))
    {
        paddle1_yPos -= paddle_speed;
    }
}

void updateGame(void)
{
    ball_xPos += ball_speedX;
    ball_yPos += ball_speedY;
    if (ball_yPos < 0 || ball_yPos > (31 - ball_size))
    {
        ball_speedY *= -1;
    }
}

void goal()
{

    if (ball_xPos < 0)
    {
        leds = ((leds << 1) | 0x1);
        player2Points++;
    }
    else if (ball_xPos > (128 - ball_size))
    {
        leds >>= 1;
        player2Points++;
    }
    resetGame();
    if (leds == 0x0 || leds == 0xff)
    {
        endGame();
    }
}

/* Seting all variables back to default */
void resetGame()
{
    paddle1_xPos = 0;
    paddle1_yPos = 32 / 2 - paddle_height / 2;

    paddle2_xPos = 127 - paddle_width;
    paddle2_yPos = 32 / 2 - paddle_height / 2;

    ball_xPos = 128 / 2 - ball_size / 2;
    ball_yPos = 16;

    clearDisplay();
    setPixelArray(paddle1_xPos, paddle1_yPos, paddle_width, paddle_height);
    setPixelArray(paddle2_xPos, paddle2_yPos, paddle_width, paddle_height);
    setPixelArray(ball_xPos, ball_yPos, ball_size, ball_size);
    translateToImage();
    display_image(0, oled_display);

    startOfGame = 1;
}

/* setting switches for different CPU-difficulty */

void difficulty()
{
    if (aiMode)
    {
        if (getsw() & 0x1)
        {
            ai_paddle_speed = 0.9;
        }
        else if (getsw() & 0x2)
        {
            ai_paddle_speed = 1.05;
            max_ball_speedX = 4.5;
        }
        else if (getsw() & 0x4)
        {
            ai_paddle_speed = 1.20;
            max_ball_speedX = 5;
        }
        else
        {
            ai_paddle_speed = 0.75;
        }
    }
}

void getRandom()
{
    randomNumber = TMR2 % 5;
    randomNumber /= 10;
    randomNumber += 0.5;
    randomNumber *= getRandomSign();
}

int getRandomSign()
{
    if (TMR2 % 10 < 5)
    {
        return -1;
    }
    return 1;
}
