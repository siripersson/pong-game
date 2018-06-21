#include "keyboard.h"
#include "pong.h"
#include "ball.h"
#include "paddle.h"
#include "render.h"


#include <string>
#include <iostream>

using namespace std;

const int Pong::SCREEN_WIDTH = 640;
const int Pong::SCREEN_HEIGHT = 480;

Pong::Pong(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	ball = new Ball(SCREEN_WIDTH/2-ball->LENGTH/2, SCREEN_HEIGHT/2-ball->LENGTH/2);
	leftPaddle = new Paddle(40, SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
	rightPaddle = new Paddle(SCREEN_WIDTH-(40+Paddle::WIDTH), SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
	keyboard = new Keyboard();

	exit = false;
	gamepadDirection = 3;

}

Pong::~Pong() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Pong::execute() {
	while(!exit){
	input();
	render();
	SDL_Delay(10);
	}
}

void Pong::input() {
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			exit = true;

		switch(event.type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyboard->handleKeyboardEvent(event);
			break;
		}
	}

	if(keyboard->isPressed("SDLK_UP") && keyboard->isPressed("SDLK_w"))
	{
		rightPaddle->updatePaddleDirection(gamepadDirection * -1);
		leftPaddle->updatePaddleDirection(gamepadDirection * -1);
	}
	if(keyboard->isPressed("SDLK_UP") && keyboard->isPressed("SDLK_s"))
	{
			rightPaddle->updatePaddleDirection(gamepadDirection * -1);
			leftPaddle->updatePaddleDirection(gamepadDirection);
	}
	if(keyboard->isPressed("SDLK_DOWN") && keyboard->isPressed("SDLK_w"))
	{
			rightPaddle->updatePaddleDirection(gamepadDirection);
			leftPaddle->updatePaddleDirection(gamepadDirection * -1);
	}
	if(keyboard->isPressed("SDLK_DOWN") && keyboard->isPressed("SDLK_s"))
	{
			rightPaddle->updatePaddleDirection(gamepadDirection);
			leftPaddle->updatePaddleDirection(gamepadDirection);
	}

	if(keyboard->isPressed("SDLK_UP"))
		rightPaddle->updatePaddleDirection(gamepadDirection * -1);

	if(keyboard->isPressed("SDLK_DOWN"))
		rightPaddle->updatePaddleDirection(gamepadDirection);

	if(keyboard->isPressed("SDLK_w"))
		leftPaddle->updatePaddleDirection(gamepadDirection *-1);

	if(keyboard->isPressed("SDLK_s"))
		leftPaddle->updatePaddleDirection(gamepadDirection);
}


void Pong::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect paddle1 = { leftPaddle->x, leftPaddle->y, Paddle::WIDTH, Paddle::HEIGHT };
	SDL_RenderFillRect(renderer, &paddle1);

	SDL_Rect paddle2 = { rightPaddle->x, rightPaddle->y, Paddle::WIDTH, Paddle::HEIGHT };
	SDL_RenderFillRect(renderer, &paddle2);

	SDL_Rect pong_ball = { ball->x, ball->y, ball->LENGTH, ball->LENGTH };
	SDL_RenderFillRect(renderer, &pong_ball);

	SDL_RenderPresent(renderer);

}
