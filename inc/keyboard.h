#pragma once

#include <SDL.h>
#include<string>
#include <map>

class Paddle;

class Keyboard {
public:
	Keyboard(){};
	~Keyboard() {}

	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

	std::map<std::string, std::string> keyStates; // = {{"SDLK_UP", "RELEASED"}, {"SDLK_DOWN", "RELEASED"}, {"SDLK_w", "RELEASED"}, {"SDLK_s", "RELEASED"}};

	void handleKeyboardEvent(SDL_Event event);
	bool isPressed(std::string keycode);
	void checkWhichKeyIsPressed();
	bool checkIfPressedQuit(SDL_Event event);

private:
	Paddle* leftPaddle;
	Paddle* rightPaddle;
};


