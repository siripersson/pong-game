#include "keyboard.h"
#include "paddle.h"
#include <iostream>
#include <map>
#include <string>

std::map<std::string, std::string> keyStates = {{"SDLK_UP", "RELEASED"}, {"SDLK_DOWN", "RELEASED"}, {"SDLK_w", "RELEASED"}, {"SDLK_s", "RELEASED"}};

void Keyboard::handleKeyboardEvent(SDL_Event event) {
	if( event.type == SDL_KEYDOWN )
	{
		if( event.key.keysym.sym == SDLK_UP )
		{
			keyStates["SDLK_UP"] ="PRESSED";
		}
		if( event.key.keysym.sym == SDLK_DOWN )
			keyStates["SDLK_DOWN"] ="PRESSED";

		if( event.key.keysym.sym == SDLK_w )
			keyStates["SDLK_w"] ="PRESSED";

		if( event.key.keysym.sym == SDLK_s )
			keyStates["SDLK_s"] ="PRESSED";

	}

	if( event.type == SDL_KEYUP )
	{
		if( event.key.keysym.sym == SDLK_UP )
			keyStates["SDLK_UP"] ="RELEASED";

		if( event.key.keysym.sym == SDLK_DOWN )
			keyStates["SDLK_DOWN"] ="RELEASED";

		if( event.key.keysym.sym == SDLK_w )
			keyStates["SDLK_w"] ="RELEASED";

		if( event.key.keysym.sym == SDLK_s )
			keyStates["SDLK_s"] ="RELEASED";
	}
}

bool Keyboard::isPressed(std::string keycode){
	return keyStates[keycode] == "PRESSED";
}

