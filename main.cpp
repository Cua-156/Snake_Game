#include <raylib.h>
#include <iostream>
#include <deque>
#include <rayMath.h>

using namespace std;

Color green = { 170,200,96,255 };
Color darkGreen = { 40,50,25,255 };

int cellSize = 30;
int cellCount = 25;

int offset = 75;

double lastUpdateTime = 0;

bool eventTriggered(double interval) {
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}
	return false;
}

bool CheckDequeElement(Vector2 element, deque<Vector2> deque) {
	for (int i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], element)) {
			return true;
		}
	}
	return false;
}

class Snake {
	public:
		deque<Vector2> body = {Vector2(6,9), Vector2(5,9), Vector2(4,9)}; //Deque (double ended queue) to store the body parts of the snake
		Vector2 direction = { 1,0 };
		bool addSeg = false;

		void Draw() {
			for (Vector2 part : body) {
				float x = part.x;
				float y = part.y;
				//cout << "x is" << x << " y is " << y << endl;
				//DrawRectangle(x*cellSize, y*cellSize, cellSize, cellSize, darkGreen);
				Rectangle rec = { offset + x * cellSize, offset + y * cellSize, (float)cellSize, (float)cellSize };
				DrawRectangleRounded(rec, 0.5, 6, darkGreen);
			}
		}

		void Update() {
			body.push_front(Vector2Add(body[0], direction));
			if (addSeg == true){
				addSeg = false;

			}
			else {
				body.pop_back();
			}
		}

		void Reset() {
			body = { Vector2(6,9), Vector2(5,9), Vector2(4,9) };
			direction = { 1,0 };
			addSeg = false;
		}
};

class Food {

	public:
		Vector2 pos; //Vector with {x, y} used for postion of our food
		//Texture2D texture; // Apple is too large will not be loading any images

		Food(deque <Vector2> snakeBody) {
			pos = randPos(snakeBody);
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
			// center the circle inside the grid cell
			DrawCircle(offset + pos.x * cellSize + cellSize/2.0f, offset + pos.y * cellSize + cellSize/2.0f, cellSize/2, RED);
			//DrawTexture(texture, pos.x*cellSize, pos.y*cellSize); // Apple is too large will not be loading any images
		}

		Vector2 GenerateRandomPos() {
			int x = GetRandomValue(0, cellCount - 1);
			int y = GetRandomValue(0, cellCount - 1);
			return Vector2{ (float)x, (float)y };
		}

		Vector2 randPos(deque<Vector2> snakeBody) {
			Vector2 pos = GenerateRandomPos();

			while (CheckDequeElement(pos, snakeBody)) {
				pos = GenerateRandomPos();
			}

			return pos;
		}

};

class Game {
	public:
		Snake snake = Snake();
		Food food = Food(snake.body);
		bool running = true;
		int score = 0;

		void Draw() {
			food.Draw();
			snake.Draw();
		}

		void Update() {
			if (running) {
				snake.Update();
				CheckCollisionFood();
				CheckCollisionWall();
				CheckCollisionSelf();
			}
		}


		void CheckCollisionFood() {
			//Check collision between snake and food
			if (Vector2Equals(snake.body[0], food.pos)){
				//cout << "Eating Food" << endl;
				food.pos = food.randPos(snake.body);
				snake.addSeg = true;
				score++;
			}
		}

		void CheckCollisionWall() {
			//Check collision between snake and wall
			if (snake.body[0].x == cellCount || snake.body[0].x == -1 || snake.body[0].y == cellCount || snake.body[0].y == -1) {
				GameOver();
			}
		}

		void CheckCollisionSelf() {
			//Check collision between snake and itself
			for (int i = 1; i < snake.body.size(); i++) {
				if (Vector2Equals(snake.body[0], snake.body[i])) {
					GameOver();
				}
			}
		}

		void GameOver() {
			cout << "Game Over!" << endl;
			snake.Reset();
			food.pos = food.randPos(snake.body);
			running = false;
			score = 0;
		}
};

int main() {
	cout << "Opening Snake Game Window..." << endl;

	InitWindow(2*offset + (cellSize*cellCount), 2*offset + (cellSize * cellCount), "Snake Game"); //Creates the window for our game
	SetTargetFPS(60); //Sets the target FPS for our game

	Game game = Game();

	while (WindowShouldClose() == false) { //Game Loop

		BeginDrawing();

		//Drawing screen
		ClearBackground(green);

		if (eventTriggered(0.2)) {
			//cout << "Updating Snake Position..." << endl;
			game.Update();
		}

		if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.direction.y != 1) {
			game.snake.direction = { 0,-1 };
			game.running = true;
		}
		if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.direction.y != -1) {
			game.snake.direction = { 0,1 };
			game.running = true;
		}
		if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.direction.x != 1) {
			game.snake.direction = { -1,0 };
			game.running = true;
		}
		if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.direction.x != -1) {
			game.snake.direction = { 1,0 };
			game.running = true;
		}

		ClearBackground(GRAY);
		DrawRectangle((float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, cellSize * cellCount + 10, green);
		DrawText("Snake Game", offset - 5, 20, 40, BLACK);
		DrawText(TextFormat("%i", game.score), cellSize * cellCount - 5 , 20, 40, BLACK);
		game.Draw();

		EndDrawing();

	}

	CloseWindow(); // Closes the window for our game

    return 0;
}