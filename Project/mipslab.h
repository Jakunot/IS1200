/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */

/* Written as part of asm lab: delay, time2string */

void delay(int);
void time2string( char *, int );

/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

/* Written as part of project: main-menu functions*/
void menu(int);
void mainMenuFunctions(void);
/* Written as part of project: main-menu variables*/
extern float currentMenu;
extern float settingsMenu;

/* Written as part of project: display functions*/
void setPixelArray(int, int, int, int);
void translateToImage(void);
void clearDisplay(void);
void clearString(void);

/*Written as part of project: display variables*/

extern uint8_t display[32][128];
extern uint8_t oled_display[512];


/* Written as part of project: game mechanics variables*/
//paddle movements 
extern float paddle_height;
extern float paddle_width;
extern float paddle_speed;

extern float paddle1_xPos;
extern float paddle1_yPos;
extern int player1Points;

extern float paddle2_xPos;
extern float paddle2_yPos;
extern int player2Points;

//ball movements
extern float ball_size;
extern float ball_speedX;
extern float ball_speedY;
extern float ball_xPos;
extern float ball_yPos;
extern float max_ball_speedX;

//CPU-movements
extern float ai_paddle_speed;
extern float randomNumber;
/* Written as part of project: game mechanics functions*/
void player1_movement(void);
void player2_movement(void);
void collide(void);
void updateGame(void);
void goal(void);
void resetGame();
void difficulty();
void getRandom();
int getRandomSign();

