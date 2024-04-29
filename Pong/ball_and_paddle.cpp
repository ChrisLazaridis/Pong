#include "ball_and_paddle.h"
#include <complex>
void paddle::draw() const
{
    DrawRectangleRec(get_rec(), color);
}

void paddle::move_up()
{
    if (y - height / 2 >= 0)
    {
        y -= speed * GetFrameTime();
    }
}

void paddle::move_down()
{
    if (y + height / 2 <= static_cast<float>(GetScreenHeight()))
    {
        y += speed * GetFrameTime();
    }
}

void paddle::move_ai(const ball& ball_obj)
{
	const float error = ball_obj.y - y;

	const float speed_adjustment = difficulty * error * 5 ;

    y += speed_adjustment * GetFrameTime();
}

Rectangle paddle::get_rec() const
{
    return { x - width / 2, y - height / 2, width, height };
}

void ball::draw() const
{
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, color);
}

void ball::check_collision()
{
    if (y - radius <= 0 || y + radius >= static_cast<float>(GetScreenHeight()))
    {
        speed_y = -speed_y;
    }
}

void ball::check_collision(const paddle& paddle_obj, const int direction)
{
    if (CheckCollisionCircleRec(Vector2{ x, y }, radius, paddle_obj.get_rec()))
    {
        if (speed_x < 0 && direction == 0)
        {
            speed_x *= -1.1f;
            speed_y = (y - paddle_obj.y) / (paddle_obj.height / 2) * speed_x;
        }
        else if (speed_x > 0 && direction == 1)
        {
            speed_x *= -1.1f;
            speed_y = (y - paddle_obj.y) / (paddle_obj.height / 2) * (-1 * speed_x);
        }

    }
}

int ball::check_score() const
{
    if (x - radius <= 0)
    {
        return 1;
    }
    if (x + radius >= static_cast<float>(GetScreenWidth()))
    {
        return 2;
    }
    return 0;
}