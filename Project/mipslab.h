/* mipslab.h
   
   Header file for all labs.

   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall
   Latest update 2022-03-03 by E Beshir & J Otineo


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
const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
const uint8_t const icon[128];
/* Declare text buffer for display output */
char textbuffer[4][16];

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

// display = a matrix for the pixel dimensions is 32 pixels in height (y) and 128 pixels in width (x)
uint8_t display[32][128];
// oled_display = a matrix that can be interpreted by the hardware
uint8_t oled_display[512];

// Variables to keep track of navigation between different screens
extern int in_menu;
extern int in_game;
extern int in_mode_menu;
extern int in_scoreboard;
extern int menu_option;
extern int modes_option;

// Modes
extern int default_mode;
extern int ai_mode;
extern int infinity_mode;

// AI difficulty variables
extern float aiPadelSpeed5;

// Variables that are needed for (quicksleeps/delays) in the start and end of every screen
extern int start_of_menu;
extern int start_of_modes;
extern int start_of_scoreboard;
extern int start_of_game;
extern int end_of_game;

// Highscore specific variables
extern int infinity_score;
extern int current_scoreboard_list[];

// Highscore int to char array
extern char scoreboard_pos1[];
extern char scoreboard_pos2[];
extern char scoreboard_pos3[];
extern char buffer1[];
extern char buffer2[];
extern char buffer3[];

extern float ai_pad_speed;

extern char concat_score[];
extern char space_the_score[];

// Padel and player variables
extern float pad_height;
extern float pad_width;
extern float pad_speed ;
extern int leds;

extern float pad1_pos_X;
extern float pad1_pos_Y;
extern int player1_score;

extern float pad2_pos_X;
extern float pad2_pos_Y;
extern int player2_score;

// Ball variables
extern float ball_size;
extern float ball_speed_X;
extern float ball_speed_Y;
extern float ball_pos_X;
extern float ball_pos_Y;
extern float max_ball_speed_X;

extern float random_number;

extern int timeoutcount;
extern int tickCounter;

/* Function */ 

/* Display */
void set_pixel(int, int, int, int);
void clear_string_display(void);
void convert_to_display(void);
void clear_array_display(void);


/* Game Mechanics */
void ball_mechanics(void);
void player_movement(void);

/* Game State */
void clear_array_display(void);
void reset_game(void);
void goal(void);
void game_end(void);

void show_menu(void);
void show_modes_menu(void);
void show_scoreboard(void);

void set_in_game(void);
void set_ai_difficulty(void);
void set_infinity_mode(void);
void set_ai_mode(void);

/* Menu */ 
void move_menu_cursor(void);
void set_menu(void);
void scoreboard(void);
void move_modes_cursor(void);
void set_mode(void);
void quit_game(void);

/* Game Lights */
void ledControl(void);
void lightshow(int); 





