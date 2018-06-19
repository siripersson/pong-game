#pragma once
#include <SDL.h>

class Paddle;

class Ball {
public:
	Ball(int x, int y);
	~Ball() {}

	static const int LENGTH;

	int _x;
	int _y;

};
