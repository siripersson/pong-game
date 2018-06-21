#include "keyboard.h"
#include "paddle.h"
#include <iostream>
#include <map>
#include <string>
/*
const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

void handleKeyboardEvent(SDL_Event event) {
	keyboardState[event.key] = SDL_GetModState;
}

bool isPressed(const Uint8* keyCode) {
	return (keyboardState[keyCode] == SDL_KEYDOWN);
}

bool isReleased(const Uint8* keyCode) {
	return (keyboardState[keyCode] == SDL_KEYUP);
} */

/*KeyboardHandler::KeyboardHandler() {
leftPaddle = new Paddle(40, SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
rightPaddle = new Paddle(SCREEN_WIDTH-(40+Paddle::WIDTH), SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
} */

std::map<std::string, std::string> keyStates = {{"SDLK_UP", "RELEASED"}, {"SDLK_DOWN", "RELEASED"}, {"SDLK_w", "RELEASED"}, {"SDLK_s", "RELEASED"}};

void Keyboard::handleKeyboardEvent(SDL_Event event) {
	if( event.type == SDL_KEYDOWN ) {
		if( event.key.keysym.sym == SDLK_UP ){
			keyStates["SDLK_UP"] ="PRESSED";
			//std::cout << keyStates["SDLK_UP"] << std::endl;
		}
		if( event.key.keysym.sym == SDLK_DOWN )
			keyStates["SDLK_DOWN"] ="PRESSED";
		if( event.key.keysym.sym == SDLK_w )
			keyStates["SDLK_w"] ="PRESSED";
		if( event.key.keysym.sym == SDLK_s )
			keyStates["SDLK_s"] ="PRESSED";

	}
	if( event.type == SDL_KEYUP ) {
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

bool Keyboard::isReleased(std::string keycode){
	return keyStates[keycode] == "RELEASED";

}

		/* Uint32 keystate [];
		if( event.type == SDL_KEYDOWN )
			keystate[0] = event.type;

		if( event.type == SDL_KEYDOWN ){
			cout << "keydown" <<endl;
			if( event.key.keysym.sym == SDLK_UP )
				upPressed =true;
			//if( event.key.keysym.sym == SDLK_DOWN)
			//	downPressed =true;
			if( event.key.keysym.sym == SDLK_w)
				wPressed =true;
			//if( event.key.keysym.sym == SDLK_s)
				//sPressed =true;
		}

		if( event.type == SDL_KEYUP ){
			cout << "keyup" << endl;
			if( event.key.keysym.sym == SDLK_UP )
				upPressed =false;
			//if( event.key.keysym.sym == SDLK_DOWN)
				//downPressed =false;
			if( event.key.keysym.sym == SDLK_w)
				wPressed =false;
		//	if( event.key.keysym.sym == SDLK_s)
			//	sPressed =false;
		}
		cout << "upPressed: " << upPressed <<endl;
		cout << "wPressed: " << wPressed <<endl;

		if(upPressed){
			//cout << "upPressed: "<< endl;
			//cout << upPressed<< endl;
			rightPaddle->updatePaddleDirection(gamepadDirection * -1);
		}

	if(downPressed){
			//cout << "downPressed: "<< endl;
		//	cout << downPressed<< endl;
			rightPaddle->updatePaddleDirection(gamepadDirection );
				}
		if(wPressed){
			//cout << "wPressed: "<< endl;
		//	cout << wPressed<< endl;
			leftPaddle->updatePaddleDirection(gamepadDirection * -1);
						}
	if(sPressed){
		//	cout << "sPressed: "<< endl;
		//	cout << sPressed<< endl;
			leftPaddle->updatePaddleDirection(gamepadDirection );
		}
		if(upPressed && wPressed){
			cout << "both up and wPressed: "<< endl;
			cout << upPressed<< endl;
			cout << wPressed<< endl;
			rightPaddle->updatePaddleDirection(gamepadDirection * -1);
			leftPaddle->updatePaddleDirection(gamepadDirection * -1);
							}

} */

