#include "paddle.h"
#include "ball.h"
#include "pong.h"

const int Paddle::HEIGHT = 60;
const int Paddle::WIDTH = 10;

Paddle::Paddle(int new_x, int new_y){
	x = new_x;
	y = new_y;
}
