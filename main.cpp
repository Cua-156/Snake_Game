#include <raylib.h>
#include <iostream>

using namespace std;

int main() {
	cout << "Opening Snake Game Window..." << endl;

	InitWindow(800, 600, "Snake Game"); //Creates the window for our game
	SetTargetFPS(60); //Sets the target FPS for our game

	while (WindowShouldClose() == false) { //Game Loop

		BeginDrawing();

		EndDrawing();

	}

	CloseWindow(); // Closes the window for our game

    return 0;
}