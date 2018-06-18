#pragma once
#include <SDL.h>

class Ball;

// Declaration
class Ball {
public:
	Ball(int x, int y); // Construct
	~Ball() {} // Destruct

	// Dimension
	static const int LENGTH;

	// Position
	int x;
	int y;

};
