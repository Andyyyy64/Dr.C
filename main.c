#include "raylib.h"



int main() {
    InitWindow(800, 450, "Only two digit!!!");

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("YOYOYOYOYOYOYOY", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
