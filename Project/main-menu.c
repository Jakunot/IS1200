#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include <stdio.h>
#include <stdlib.h>

float menu = 1;

void menu(int btns){
    delay(200);
    if (menu == 1){
        display_string(0, "> Player 1 Mode");
        display_string(1, "  Player 2 Mode");
        display_string(2, "  Settings");
    
        if(getbtns() & 0x1)
        {
        /* add once we have decided game mode
            basically here is were the  game starts
            once defined in other functions
            variable example
            game mode = 1 player*/
        }
    }else if(menu == 2){

        display_string(0, "  Player 1 Mode");
        display_string(1, "> Player 2 Mode");
        display_string(2, "  Settings");

        if(getbtns() & 0x1){
        /* add once we have decided game mode
            basically here is were the  game starts
            once defined in other functions
            variable example
            game mode = 2 players*/
        }
    }else if(menu == 3){

        display_string(0, "  Player 1 Mode");
        display_string(1, "  Player 2 Mode");
        display_string(2, "> Settings");

        if(getbtns() & 0x1){
        /* add later what setting we would like*/
        }
    }
    if((getbtns() & 0x2) && (menu < 3)){
        menu++;
    }
    if((getbtns() & 0x4) && (menu > 1)){
        menu--;
    }
    display_update();
}