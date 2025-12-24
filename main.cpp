#include "raylib.h"

int main() {
    // 1. Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Test Screen");

    SetTargetFPS(60); // Set the game to run at 60 frames-per-second

    // 2. Main Game Loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // 3. Update (Handle logic here)

        // 4. Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! Raylib is working.", 190, 200, 20, LIGHTGRAY);
        DrawCircle(screenWidth / 2, 300, 40, MAROON);

        EndDrawing();
    }

    // 5. De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}