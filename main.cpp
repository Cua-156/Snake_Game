#include <raylib.h>
#include <iostream>
#include <deque>

using namespace std;

Color green = { 170,200,96,255 };
Color darkGreen = { 40,50,25,255 };

int cellSize = 30;
int cellCount = 25;

class Snake {
	public:
		deque<Vector2> body = {Vector2(6,9), Vector2(5,9), Vector2(4,9)}; //Deque (double ended queue) to store the body parts of the snake

		void Draw() {
			for (Vector2 part : body) {
				float x = part.x;
				float y = part.y;
				cout << "x is" << x << " y is " << y << endl;
				//DrawRectangle(x*cellSize, y*cellSize, cellSize, cellSize, darkGreen);
				Rectangle rec = { x * cellSize, y * cellSize, (float)cellSize, (float)cellSize };
				DrawRectangleRounded(rec, 0.5, 6, darkGreen);
			}
		}
};

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
	Snake snake = Snake();

	while (WindowShouldClose() == false) { //Game Loop

		BeginDrawing();

		//Drawing screen
		ClearBackground(green);

		apple.Draw();
		snake.Draw();

		EndDrawing();

	}

	CloseWindow(); // Closes the window for our game

    return 0;
}