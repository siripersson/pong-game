#pragma once

#include <SDL.h>

class Ball;
class Paddle;
class Keyboard;

class Pong {
private:
	 SDL_Window *window;
	 SDL_Renderer *renderer;

	 Ball* ball;
	 Paddle* leftPaddle;
	 Paddle* rightPaddle;
	 Keyboard* keyboard;

	 bool exit;
	 int gamepadDirection;

public:
   static const int SCREEN_WIDTH;
   static const int SCREEN_HEIGHT;

   Pong(int argc, char *argv[]);
   ~Pong();
   void execute();
   void input();
   void update();
   void render();
};

