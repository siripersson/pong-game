#pragma once

class Ball;

class Paddle {
private:
	int _x;
	int _y;

public:
	Paddle(int x, int y);

	static const int HEIGHT;
	static const int WIDTH;
};
