#include "game.h"

int main() {
    InitWindow(window_width, window_height, "Only two digit!!!");
    init_board();
    SetTargetFPS(GAME_FPS);
    while(!WindowShouldClose()) {
     update_and_draw();
    }

    CloseWindow();

    return 0;
}
