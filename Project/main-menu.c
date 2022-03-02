#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

float currentMenu = 1;
float settingsMenu = 0;

void menu(int btns)
{
    delay(200);
    display_string(0, " PONG-22");
    if (currentMenu == 1)
    {
        display_string(1, "> Player 1 Mode");
        display_string(2, "  2 Player Mode");
        display_string(3, "  Settings");
    }
    else if (currentMenu == 2)
    {
        display_string(1, "  Player 1 Mode");
        display_string(2, "> 2 Player Mode");
        display_string(3, "  Settings");
    }
    else if (currentMenu == 3)
    {
        display_string(1, "  Player 1 Mode");
        display_string(2, "  2 Player Mode");
        display_string(3, "> Settings");
    }
    display_update();
}

void mainMenuFunctions(void)
{
    if (getbtns() & 0x1 && currentMenu == 1)
    {    
        currentMenu = 0;
    }
    else if (getbtns() & 0x1 && currentMenu == 2)
    {
        currentMenu = 0;
    }
    else if (getbtns() & 0x1 && currentMenu == 3)
    {
        currentMenu = 0;
    }
    else if ((getbtns() & 0x2) && currentMenu != 2)
    {
        currentMenu++;
        menu();
    }
    else if ((getbtns() & 0x4) && currentMenu != 0)
    {
        currentMenu--;
        menu();
    }
}