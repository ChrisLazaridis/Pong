#include <iostream>
#include <string>
#include <cmath>
#include <raylib.h>
#include <vector>

#include "ball_and_paddle.h"

int main()
{
	int difficulty;
	std::cout << "Enter difficulty (the lower the number the higher the difficulty)(>=0): ";
	do
	{
		std::cin >> difficulty;
	} while (difficulty < 0);
	std::cout << '\n';
	const std::vector<Color> colorOptions = { BLACK, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, PINK, SKYBLUE, LIME };
	const std::vector<std::string> colorNames = { "BLACK", "RED", "GREEN", "BLUE", "YELLOW", "ORANGE", "PURPLE", "PINK", "SKYBLUE", "LIME" };
	std::cout << "Color Options:\n";
	for (int i = 0; i < colorOptions.size(); ++i) {
		std::cout << i << ". " << colorNames[i] << "\n";
	}
	int bgColorIndex;
	do {
		std::cout << "Enter the index of the background color: ";
		std::cin >> bgColorIndex;
	} while (bgColorIndex < 0 || bgColorIndex >= colorOptions.size());
	int paddleColorIndex;
	do {
		std::cout << "Enter the index of the paddle/ball color: ";
		std::cin >> paddleColorIndex;
	} while (paddleColorIndex < 0 || paddleColorIndex >= colorOptions.size());
	Color bgColor = colorOptions[bgColorIndex];
	Color paddleColor = colorOptions[paddleColorIndex];
	const int c = 18;
	InitWindow(800, 650, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);
	ball ball = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2, 300.0f, 300.0f, 10, paddleColor};
	paddle left_paddle = {50, static_cast<float>(GetScreenHeight()) / 2, 500.0f + abs(ball.speed_x) / c, 10, 100, 0, paddleColor};
	paddle right_paddle = {static_cast<float>(GetScreenWidth()) - 50, static_cast<float>(GetScreenHeight()) / 2 , 500.0f + abs(ball.speed_x) / c, 10, 100, difficulty, paddleColor};
	int score [2] = {0, 0};
	
    while (!WindowShouldClose())
    {
	    ball.x += ball.speed_x * GetFrameTime();
        ball.y += ball.speed_y * GetFrameTime();
		ball.check_collision();
		if (IsKeyDown(KEY_W))
		{
			left_paddle.move_up();
		}
		if (IsKeyDown(KEY_S))
		{
			left_paddle.move_down();
		}
		right_paddle.move_ai(ball);
		ball.check_collision(left_paddle, 0);
		ball.check_collision(right_paddle, 1);
		left_paddle.speed = 500.0f + abs(ball.speed_x)/c;
		right_paddle.speed = 500.0f + abs(ball.speed_x)/c;
		int point = ball.check_score();
		bool scored = false;
		if(point == 1)
		{
			score[1]++;
			ball = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2, 300.0f, 300.0f, 10, paddleColor};
			scored = true;
		}
		else if(point == 2)
		{
			score[0]++;
			ball = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2, -300.0f, 300.0f, 10, paddleColor};
			scored = true;
		}
        BeginDrawing();
		for (int y = 0; y < GetScreenHeight(); y += 10)
		{
			const Vector2 start = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(y) };
			const Vector2 end = { static_cast<float>(GetScreenWidth() / 2), static_cast<float>(y + 5) };
			DrawLineV(start, end, GRAY);
		}
		DrawText(TextFormat("%i  %i", score[0], score[1]), GetScreenWidth() / 2 - 72, 10, 72, Fade(WHITE, 0.5f));
		
        ClearBackground(bgColor);
    	left_paddle.draw();
		right_paddle.draw();
        ball.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
