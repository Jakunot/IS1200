/* mipslabwork.c

  This file written 2015 by F Lundevall
  Updated 2017-04-21 by F Lundevall

  
  This file was modified 2017-04-31 by Ture Teknolog 
  This file was modified 2022-02-16 by J Otieno

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trise = (volatile int*) 0xbf886100; //For TRISE for setting input or output
  *trise &= ~0xff;  //set first 8 bits to zero, setting them as output pins

  TRISD = TRISD & 0x0fe0; //initializing PORTD, set bits 11-5 as input

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = (volatile int*) 0xbf886110; //For PORTE for reading and writing data
  
  
  int btns = getbtns();
  int sw = getsw();

  //button 2
  if (btns & 1) {
    mytime = (sw << 4) | (mytime & 0xff0f);
  }
  //button 3
  if (btns & 2) {
    mytime = (sw << 8) | (mytime & 0xf0ff);
  }
  //button 4
  if (btns & 4) {
    mytime = (sw << 12) | (mytime & 0x0fff);
  }

  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
  *porte += 0x1;
}
