#include <raylib.h>
#include <iostream>

using namespace std;

Color green = { 170,200,96,255 };
Color darkGreen = { 40,50,25,255 };

int cellSize = 30;
int cellCount = 25;

class Food {

	public:
		Vector2 pos; //Vector with {x, y} used for postion of our food
		//Texture2D texture; // Apple is too large will not be loading any images

		Food() {
			pos = randPos();
			/* 
			Apple is too large will not be loading any images
			Image image = LoadImage("Graphics/apple.png");
			texture = LoadTextureFromImage(image);
			UnloadImage(image);
			*/
		}

		~Food() {
			//UnloadTexture(texture);
		}

		void Draw() {
			//Draw food here
			DrawCircle(pos.x*cellSize,pos.y*cellSize,cellSize/2,RED);
			//DrawTexture(texture, pos.x*cellSize, pos.y*cellSize); // Apple is too large will not be loading any images
		}

		Vector2 randPos() {
			int x = GetRandomValue(0, cellCount - 1);
			int y = GetRandomValue(0, cellCount - 1);

			return Vector2{(float)x, (float)y};
		}

};

int main() {
	cout << "Opening Snake Game Window..." << endl;

	InitWindow(cellSize*cellCount, cellSize * cellCount, "Snake Game"); //Creates the window for our game
	SetTargetFPS(60); //Sets the target FPS for our game

	Food apple = Food();

	while (WindowShouldClose() == false) { //Game Loop

		BeginDrawing();

		//Drawing screen
		ClearBackground(green);

		apple.Draw();

		EndDrawing();

	}

	CloseWindow(); // Closes the window for our game

    return 0;
}