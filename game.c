#include "game.h"
#include <raylib.h>

void init_board() {
    fading_color = GRAY;
    for(int i = 0; i < HORIZONTAL; i++) {
        // set the blocked cells and empty cells
        for(int j = 0; j < VERTICAL; j++) {
            if((j == VERTICAL - 1) || (i == 0) || (i == HORIZONTAL - 1)) {
                board[i][j] = BLOCKED;
            } else {
                board[i][j] = EMPTY;
            }
        }

        // set the next bit cells to empty
        for(int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                next_two_bit[i][j] = EMPTY;
            }
        }
    }
}

void update_board() {
    if(!game_over) {
        // printf("1frame\n");
        if(IsKeyPressed('P')) { // if the user press the P
            pausing = !pausing; // change the pausing state
        }
        if(!pausing) {
            if(!bit_to_delete) {
                if(!is_bit_active) {
                    // if the bit is not active, create a new bit
                    is_bit_active = create_bit();

                    fast_falling_counter = 0;
                } else {
                    faling_down_counter++;
                    lateral_move_counter++;
                    turn_counter++;
                    fast_falling_counter++;

                    if(IsKeyPressed('A') || IsKeyReleased('D')) {
                        lateral_move_counter = LATERAL_MOVE_SPEED;
                    }
                    if(IsKeyPressed('W')) {
                        turn_counter = TURN_SPEED;
                    }
                    // fall down
                    if(IsKeyDown('S') && (fast_falling_counter > FAST_FALLING_AWAIT_SPEED)) {
                        faling_down_counter = falling_speed;
                    }
                    if(faling_down_counter >= falling_speed) {
                        // check if the bit is colliding with the board
                        check_is_collision(&is_bit_collision);

                        // move the bit down
                        bit_fall(&is_bit_active, &is_bit_collision);

                        // check if the bit complete a line
                        check_complete_line(&bit_to_delete);

                        // reset the faling speed
                        faling_down_counter = 0;
                    }
                    if(lateral_move_counter > LATERAL_MOVE_SPEED) {
                        if(!bit_lateral_move()) {
                            lateral_move_counter = 0;
                        }
                    }
                    if(turn_counter > TURN_SPEED) {
                        if(!bit_turn()) {
                            turn_counter = 0;
                        }
                    }
                }
                // game over condition
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < HORIZONTAL; j++) {
                        if(board[i][j] == ZERO_FULL || board[i][j] == ONE_FULL) {
                            game_over = true;
                        }
                    }
                }
            } else {
                fade_line_counter++;
                if(fade_line_counter%8 < 4) {
                    fading_color = MAROON;
                } else {
                    fading_color = DARKGRAY;
                }
                if(fade_line_counter > FADING_TIME) {
                    int deleted_lines = 0;
                    deleted_lines = delete_line();
                    fade_line_counter = 0;
                    bit_to_delete = false;

                    lines += deleted_lines;
                }
            }
        }
    } else {
        if(IsKeyPressed(KEY_ENTER)) {
            init_board();
            game_over = false;
        }
    }
}

void draw_board() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if(!game_over) {
        Vector2 pos;
        pos.x = window_width/2 - (HORIZONTAL*SQUARE_SIZE/2) - 50;
        pos.y = window_height/2 - ((VERTICAL - 1)*SQUARE_SIZE/2) + SQUARE_SIZE*2; // idk wtf is this
        pos.y -= 50;

        int controller = pos.x;
        for (int j = 0; j < VERTICAL; j++) {
                for (int i = 0; i < HORIZONTAL; i++) {
                    // Draw each square of the grid
                    if (board[i][j] == EMPTY) {
                        DrawLine(pos.x, pos.y, pos.x + SQUARE_SIZE, pos.y, LIGHTGRAY );
                        DrawLine(pos.x, pos.y, pos.x, pos.y + SQUARE_SIZE, LIGHTGRAY );
                        DrawLine(pos.x + SQUARE_SIZE, pos.y, pos.x + SQUARE_SIZE, pos.y + SQUARE_SIZE, LIGHTGRAY );
                        DrawLine(pos.x, pos.y + SQUARE_SIZE, pos.x + SQUARE_SIZE, pos.y + SQUARE_SIZE, LIGHTGRAY );
                        pos.x += SQUARE_SIZE;
                    } else if (board[i][j] == ZERO_FULL) {
                        DrawText("0", pos.x + BIT_OFFSET, pos.y, 20, DARKGRAY);
                        DrawLine(pos.x, pos.y, pos.x + SQUARE_SIZE, pos.y, LIGHTGRAY );
                        pos.x += SQUARE_SIZE;
                    } else if(board[i][j] == ONE_FULL) {
                        DrawText("1", pos.x + BIT_OFFSET, pos.y, 20, DARKGRAY);
                        DrawLine(pos.x, pos.y, pos.x + SQUARE_SIZE, pos.y, LIGHTGRAY );
                        pos.x += SQUARE_SIZE;
                    } else if (board[i][j] == ZERO) {
                        DrawText("0", pos.x + BIT_OFFSET, pos.y, 20, DARKGRAY);
                        DrawLine(pos.x, pos.y, pos.x + SQUARE_SIZE, pos.y, LIGHTGRAY );
                        pos.x += SQUARE_SIZE;
                    } else if(board[i][j] == ONE) {
                        DrawText("1", pos.x + BIT_OFFSET, pos.y, 20, DARKGRAY);
                        DrawLine(pos.x, pos.y, pos.x + SQUARE_SIZE, pos.y, LIGHTGRAY );
                        pos.x += SQUARE_SIZE;
                    } else if (board[i][j] == BLOCKED) {
                        DrawRectangle(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, LIGHTGRAY);
                        pos.x += SQUARE_SIZE;
                    } else if (board[i][j] == FADING) {
                        DrawRectangle(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, fading_color);
                        pos.x += SQUARE_SIZE;
                    }
                }

                pos.x = controller;
                pos.y += SQUARE_SIZE;
            }

            // Draw incoming piece
            pos.x = 500;
            pos.y = 45;

            int controler = pos.x;

            for (int j = 0; j < 2; j++) {
                for (int i = 0; i < 2; i++) {
                    if (next_two_bit[i][j] == EMPTY) {
                        DrawLine(pos.x, pos.y, pos.x + SQUARE_SIZE, pos.y, LIGHTGRAY );
                        DrawLine(pos.x, pos.y, pos.x, pos.y + SQUARE_SIZE, LIGHTGRAY );
                        DrawLine(pos.x + SQUARE_SIZE, pos.y, pos.x + SQUARE_SIZE, pos.y + SQUARE_SIZE, LIGHTGRAY );
                        DrawLine(pos.x, pos.y + SQUARE_SIZE, pos.x + SQUARE_SIZE, pos.y + SQUARE_SIZE, LIGHTGRAY );
                        pos.x += SQUARE_SIZE;
                    } else if (next_two_bit[i][j] == ZERO) {
                        // DrawRectangle(pos.x, pos.y, SQUARE_SIZE, SQUARE_SIZE, GRAY);
                        DrawText("0", pos.x + BIT_OFFSET, pos.y, 20, GRAY);
                        pos.x += SQUARE_SIZE;
                    } else if(next_two_bit[i][j] == ONE) {
                        DrawText("1", pos.x + BIT_OFFSET, pos.y, 20, GRAY);
                        pos.x += SQUARE_SIZE;
                    }
                }
                pos.x = controler;
                pos.y += SQUARE_SIZE;
            }

            DrawText("incoming bit", pos.x, pos.y, 10, GRAY);

            if (pausing) {
                DrawText("game stoped", window_width/2 - MeasureText("game stoped", 40)/2, window_height/2 - 40, 40, GRAY);
            }
    } else {
        DrawText("enter", GetScreenWidth()/2 - MeasureText("enter", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
    }
    EndDrawing();
}

void update_and_draw() {
    update_board();
    draw_board();
}

bool create_bit() {
    bitX = (int)((HORIZONTAL - 4)/2);
    bitY = 0;

    if(begin) {
        get_random_bit();
        begin = false;
    }

    // assign the bit
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            two_bit[i][j] = next_two_bit[i][j];
        }
    }

    // assign the bit to board
    get_random_bit();

    for(int i = bitX; i < bitX + 2; i++) {
        for(int j = 0; j < 2; j++) {
            if(two_bit[i - (int)bitX][j] == ZERO) {
                board[i][j] = ZERO;
                printf("assign bit to board\n");
            }
            else if(two_bit[i - (int)bitX][j] == ONE) board[i][j] = ONE;
        }
    }
    return true;
}

void get_random_bit() {
    int random = GetRandomValue(0, 3);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            next_two_bit[i][j] = EMPTY;
        }
    }
    switch(random) {
        case 0: { next_two_bit[0][0] = ZERO; next_two_bit[0][1] = ZERO; } break; // 00
        case 1: { next_two_bit[0][0] = ZERO; next_two_bit[0][1] = ONE; } break;  // 01
        case 2: { next_two_bit[0][0] = ONE; next_two_bit[0][1] = ZERO; } break;  // 10
        case 3: { next_two_bit[0][0] = ONE; next_two_bit[0][1] = ONE; } break;   // 11
    }
}

void bit_fall(bool *is_bit_active, bool *is_bit_collision) {
    if(*is_bit_collision) {
        printf("bit collision\n");
        for(int j = VERTICAL - 2; j >= 0; j--) {
            for(int i = 1; i < HORIZONTAL - 1; i++) {
                if(board[i][j] == ZERO) {
                    board[i][j] = ZERO_FULL;
                    *is_bit_collision = false;
                    *is_bit_active = false;
                } else if(board[i][j] == ONE) {
                    board[i][j] = ONE_FULL;
                    *is_bit_collision = false;
                    *is_bit_active = false;
                }
            }
        }
    } else { // move down the bit
        printf("bit falling bit Y:%d\n", bitY);
        for(int j = VERTICAL - 2; j >= 0; j--) {
            for(int i = 1; i < HORIZONTAL - 1; i++) {
                if(board[i][j] == ZERO) {
                    board[i][j + 1] = ZERO;
                    board[i][j] = EMPTY;
                } else if(board[i][j] == ONE) {
                    board[i][j + 1] = ONE;
                    board[i][j] = EMPTY;
                }
            }
        }
        bitY++;
    }
}

bool bit_lateral_move() {
    
}

bool bit_turn() {
    
}

void check_is_collision(bool *is_bit_collision) {
    for(int j = VERTICAL - 2; j >= 0; j--) {
        for(int i = 1; i < HORIZONTAL - 1; i++) {
            if((board[i][j] == ZERO || board[i][j] == ONE) && ((board[i][j + 1] == ONE_FULL) || (board[i][j + 1] == ZERO_FULL) || (board[i][j + 1] == BLOCKED))) {
                *is_bit_collision = true;
            }
        }
    }
}


void check_complete_line(bool *bit_to_delete) {
    
}

int delete_line() {

}
