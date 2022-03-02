/* mipslabwork.c

  This file written 2015 by F Lundevall
  Updated 2017-04-21 by F Lundevall

  
  This file was modified 2017-04-31 by Ture Teknolog 
  This file was modified 2022-02-16 by J Otieno

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int timeoutcount = 0;


/* Interrupt Service Routine */
void user_isr( void )
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
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trise = (volatile int*) 0xbf886100; //For TRISE for setting input or output
  *trise &= ~0xff;  //set first 8 bits to zero, setting them as output pins

  TRISD = TRISD & 0x0fe0; //initializing PORTD, set bits 11-5 as input (button 2-4, switch 1-4)
  TRISF = TRISF & 0x2; //initializing PORTF, set bit 2 as input (button 1)


  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  
  int btns = getbtns();
  int sw = getsw();

  menu(btns);

  
}
