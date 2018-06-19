#include "paddle.h"
#include "ball.h"
#include "pong.h"

const int Paddle::HEIGHT = 60;
const int Paddle::WIDTH = 10;

Paddle::Paddle(int x, int y){
	_x = x;
	_y = y;
}

