#pragma once

class Ball;

class Paddle {
public:
	int x;
	int y;

public:
	Paddle(int x, int y);

	static const int HEIGHT;
	static const int WIDTH;
};
