#include "pong.h"
#include "ball.h"
#include "paddle.h"
#include "render.h"

const int Pong::SCREEN_WIDTH = 640;
const int Pong::SCREEN_HEIGHT = 480;

Pong::Pong(int argc, char *argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	ball = new Ball(SCREEN_WIDTH/2-ball->LENGTH/2, SCREEN_HEIGHT/2-ball->LENGTH/2);
	left_paddle = new Paddle(40, SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
	right_paddle = new Paddle(SCREEN_WIDTH-(40+Paddle::WIDTH), SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);

}

Pong::~Pong() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Pong::execute() {
	render();
	SDL_Delay(3000);
}


void Pong::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect paddle1 = { left_paddle->_x, left_paddle->_y, Paddle::WIDTH, Paddle::HEIGHT };
	SDL_RenderFillRect(renderer, &paddle1);

	SDL_Rect paddle2 = { right_paddle->_x, right_paddle->_y, Paddle::WIDTH, Paddle::HEIGHT };
	SDL_RenderFillRect(renderer, &paddle2);

	SDL_Rect pong_ball = { ball->_x, ball->_y, ball->LENGTH, ball->LENGTH };
	SDL_RenderFillRect(renderer, &pong_ball);

	SDL_RenderPresent(renderer);

}
