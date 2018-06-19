#pragma once

class Ball;

class Paddle {
public:
	Paddle(int x, int y);

	static const int HEIGHT;
	static const int WIDTH;

	int _x;
	int _y;
};
