#pragma once

#include <string>

class Ball;
class Keyboard;

class Paddle {
public:
	Paddle () {};
	Paddle(int x, int y) : x(x), y(y) {};

	static const int HEIGHT;
	static const int WIDTH;

	int x;
	int y;

	void updatePaddlePosition(int new_y);

};

