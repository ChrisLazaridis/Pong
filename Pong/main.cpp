#include <array>
#include <iostream>
#include <string>
#include <cmath>
#include <raylib.h>
#include <cstdlib>

#include "ball_and_paddle.h"

int main()
{
	constexpr int screen_width = 800;
	constexpr int screen_height = 650;
	constexpr float half_screen_width = screen_width / 2;
	constexpr float half_screen_height = screen_height / 2;
	int difficulty;
	constexpr std::array<Color, 11> color_options = { BLACK, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, PINK, SKYBLUE, LIME, WHITE };
	const std::array<std::string, 11> color_names = { "BLACK", "RED", "GREEN", "BLUE", "YELLOW", "ORANGE", "PURPLE", "PINK", "SKYBLUE", "LIME", "WHITE" };
	std::cout << "Color Options:\n";
	for (int i = 0; i < color_options.size(); ++i) {
		std::cout << i << ". " << color_names[i] << "\n";
	}
	int bg_color_index;
	do {
		std::cout << "Enter the index of the background color: ";
		std::cin >> bg_color_index;
	} while (bg_color_index < 0 || bg_color_index >= color_options.size());
	int paddleColorIndex;
	do {
		std::cout << "Enter the index of the paddle/ball color: ";
		std::cin >> paddleColorIndex;
	} while (paddleColorIndex < 0 || paddleColorIndex >= color_options.size());
	const Color bg_color = color_options[bg_color_index];
	Color paddle_color = color_options[paddleColorIndex];
	auto reset_ball = [&](ball& ball_obj, const int scored) {
		ball_obj.x = half_screen_width;
		// pick a random int from 1 to screen_height - 1 for the y value
		ball_obj.y = static_cast<float>(rand() % (screen_height - 1) + 1);
		if(scored == 1)
		{
			ball_obj.speed_x = 300.0f;
		}
		else
		{
			ball_obj.speed_x = -300.0f;
		}
		ball_obj.speed_y = 300.0f;
		ball_obj.radius = 10;
		ball_obj.color = paddle_color;
		};
	std::cout << "Enter difficulty (1-5): ";
	do
	{
		std::cin >> difficulty;
	} while (difficulty <= 0 && difficulty >= 6);
	std::cout << '\n';
	
	constexpr int c = 15;
	InitWindow(screen_width,screen_height, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);
	ball ball = {half_screen_width, half_screen_height, 300.0f, 300.0f, 10, paddle_color};
	paddle left_paddle = {50, half_screen_height, 500.0f + abs(ball.speed_x) / c, 10, 100, 0, paddle_color};
	paddle right_paddle = {screen_width - 50, half_screen_height, 500.0f + abs(ball.speed_x) / c, 10, 100, difficulty, paddle_color};
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
			scored = true;
		}
		else if(point == 2)
		{
			score[0]++;
			scored = true;
		}
		if(scored)
		{
			reset_ball(ball, point);	
		}
        BeginDrawing();
		for (int y = 0; y < screen_height; y += 10)
		{
			const Vector2 start = { half_screen_width, static_cast<float>(y) };
			const Vector2 end = { half_screen_width, static_cast<float>(y + 5) };
			DrawLineV(start, end, GRAY);
		}
		DrawText(TextFormat("%i  %i", score[0], score[1]),static_cast<int>( half_screen_width - 72), 10, 72, Fade(WHITE, 0.5f));
		
        ClearBackground(bg_color);
    	left_paddle.draw();
		right_paddle.draw();
        ball.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
