#ifndef BALL_AND_PADDLE_H
#define BALL_AND_PADDLE_H

#include <raylib.h>

struct ball;
struct paddle;

struct paddle
{
    float x, y;
    float speed;
    float width, height;
    int difficulty;
    Color color;

    void draw() const;
    void move_up();
    void move_down();
    void move_ai(const ball& ball_obj);
    Rectangle get_rec() const;
};

struct ball
{
    float x, y;
    float speed_x, speed_y;
    float radius;
    Color color;

    void draw() const;
    void check_collision();
    void check_collision(const paddle& paddle_obj, const int direction);
    int check_score() const;
};

#endif // BALL_AND_PADDLE_H

