#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef GAME_H
#define GAME_H

#define SQUARE_SIZE 20
#define ROWS 12
#define COLS 20
#define LATERAL_MOVE_SPEED 10
#define TURN_SPEED 12
#define FAST_FALLING_AWAIT_SPEED 30
#define VIRUS_NUM 3

// globals
static int window_width = 800;
static int window_height = 450;

static bool game_over = false;
static bool pausing = false;

// type def for cell type
typedef enum { EMPTY, MOVING, FULL, BLOCKED, VIRUS, FADING } CellType;;

// borads
static CellType board[ROWS][COLS];
static CellType two_bit[2][2];
static CellType next_two_bit[2][2];
static CellType virus[2][2];

// bit position
static int bitX = 0;
static int bitY = 0;

static Color fading_color;

static bool begin = true;
static bool bit_active = false;
static bool bit_detect = false;
static bool bit_to_delete = false;
static bool virus_to_delete = false;

static int level = 1;
static int lines = 0;

// counters
static int faling_down_counter = 0;
static int lateral_move_counter = 0;
static int turn_counter = 0;
static int fast_falling__counter = 0;

static int fade_line_counter = 0;

static int falling_speed = 30;

// functions related to the board
void init_board(); // initialize the board
void update_board(); // update the board
void draw_board(); // draw the board using raylib
void update_and_draw(); // update and draw the game(just a wrapper for update_board and draw_board)

// functions related to the bit
void create_bit(); // create a new bit
void get_random_bit(); // get a random bit
void bit_fall(bool *bit_active, bool *bit_detect); // make the bit fall or stop it
void bit_lateral_move(); // move the bit to the left or right
void bit_turn(); // turn the bit
void check_detect(bool *bit_detect); // check if the bit is detected
void check_complete_line(bool *bit_to_delete); // check if the line is complete
void delete_line(); // delete the line when it is full

// functions related to the virus
void create_virus(); // create a new virus
void delete_virus(); // delete the virus

#endif
