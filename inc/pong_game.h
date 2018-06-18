#pragma once

#include <SDL.h>                       // SDL library.

class Ball;

class Pong {
private:
	 SDL_Window *window;
	 SDL_Renderer *renderer;

	 Ball* ball;

public:
   // Screen resolution.
   static const int SCREEN_WIDTH;
   static const int SCREEN_HEIGHT;
};
