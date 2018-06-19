#pragma once

#include <SDL.h>

class Ball;
class Paddle;

class Pong {
private:
	 SDL_Window *window;
	 SDL_Renderer *renderer;

	 Ball* ball;
	 Paddle* left_paddle;
	 Paddle* right_paddle;

public:
   static const int SCREEN_WIDTH;
   static const int SCREEN_HEIGHT;

   Pong(int argc, char *argv[]);
   ~Pong();
   void execute();
   void render();
};
