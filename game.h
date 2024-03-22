#include "raylib.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef GAME_H
#define GAME_H

#define GAME_FPS 60

#define SQUARE_SIZE 20
#define HORIZONTAL 11
#define VERTICAL 20
#define LATERAL_MOVE_SPEED 10
#define TURN_SPEED 12
#define FAST_FALLING_AWAIT_SPEED 30
#define FADING_TIME 10
#define VIRUS_NUM 30
#define BIT_OFFSET 25

// globals
static int window_width = 800;
static int window_height = 450;

static bool game_over = false;
static bool pausing = false;

// type def for cell type
typedef enum { EMPTY, ZERO, ONE, ZERO_FULL, ONE_FULL, BLOCKED, VIRUS, FADING } CellType;

// borads
static CellType board[HORIZONTAL][VERTICAL];
static CellType two_bit[2][2];
static CellType next_two_bit[2][2];
static CellType virus[2][2];

// bit position
static int bitX = 0;
static int bitY = 0;

static Color fading_color;

static bool begin = true;
static bool is_bit_active = false;
static bool is_bit_collision = false;
static bool bit_to_delete = false;
static bool virus_to_delete = false;

static int level = 1;
static int lines = 0;

// counters
static int faling_down_counter = 0;
static int lateral_move_counter = 0;
static int turn_counter = 0;
static int fast_falling_counter = 0;

static int fade_line_counter = 0;

static int falling_speed = 30;

// functions related to the board
void init_board(); // initialize the board
void update_board(); // update the board
void draw_board(); // draw the board using raylib
void update_and_draw(); // update and draw the game(just a wrapper for update_board and draw_board)

// functions related to the bit
bool create_bit(); // create a new bit
void get_random_bit(); // get a random bit
void bit_fall(bool *is_bit_active, bool *is_bit_collision); // make the bit fall or stop it
bool bit_lateral_move(); // move the bit to the left or right
bool bit_turn(); // turn the bit
void check_is_collision(bool *is_bit_collison); // check if the bit is detected
void check_complete_line(bool *bit_to_delete); // check if the line is complete
int delete_line(); // delete the line when it is full

// functions related to the virus
void create_virus(); // create a new virus
void delete_virus(); // delete the virus

#endif
