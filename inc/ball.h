#pragma once
#include <SDL.h>

class Ball;

// Declaration
class Ball {
public:
	Ball(){};
	Ball(int x, int y) : x(x), y(y) {};
	~Ball() {} 

	// Dimension
	static const int LENGTH;

	// Position
	int x;
	int y;

};
