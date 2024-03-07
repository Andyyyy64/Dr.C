#ifndef GAME_H
#define GAME_H

#define ROWS 10
#define COLS 10
#define CELL_SIZE 40
#define FALING_SPEED 500

int board[ROWS][COLS];
int failing_row, faling_col, failing_digit;

void init_board(int board[ROWS][COLS], int level); // initialize the board based on the level
int count_virus(int board[ROWS][COLS]); // count the number of virus on the board
void remove_virus(int board[ROWS][COLS]); // remove the virus from the board when there are 4 or more matches in a row
void remove_matches(int board[ROWS][COLS]); // remove the matches from the board when there is a 4 or more matches in a row
int check_matches(int board[ROWS][COLS]); // check if there are any matches in the board

void display_game(); // display the game with opengl
void handle_input(unsigned char key, int x, int y); // handle the input from the keyboard

void init_game(int level); // initialize the game

#endif
