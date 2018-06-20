#pragma once

class Ball;

class Paddle {
public:
	Paddle () {};
	Paddle(int x, int y) : x(x), y(y) {};

	static const int HEIGHT;
	static const int WIDTH;

	int x;
	int y;
};

