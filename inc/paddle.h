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

	// Buttons associated with the paddle element, can be abstracted into a controller object associated with the paddle
	//uint32_t buttonUp;
	//uint32_t buttonDown;

	void updatePaddlePosition(int new_y);
	//void Paddle::movePaddle(int gamepadDirection, uint32_t buttonUp, uint32_t buttonDown, Keyboard* keyboard);

};

