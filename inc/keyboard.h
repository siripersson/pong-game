#pragma once
#include <SDL.h>
#include<string>

class Paddle;

class Keyboard {
public:
	Keyboard(){};
	~Keyboard() {}
	void handleKeyboardEvent(SDL_Event event);
	bool isPressed(std::string keycode);
	bool isReleased(std::string keycode);
	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

private:
	Paddle* leftPaddle;
	Paddle* rightPaddle;
};


