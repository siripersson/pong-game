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

	// Instantiate game objects.
	ball = new Ball(SCREEN_WIDTH/2-ball->LENGTH/2, SCREEN_HEIGHT/2-ball->LENGTH/2);
	left_paddle = new Paddle(40, SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
	right_paddle = new Paddle(SCREEN_WIDTH-(40+Paddle::WIDTH), SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);

}

Pong::~Pong() {
    // Destroy renderer and window.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Shuts down SDL.
    SDL_Quit();
}

void Pong::execute() {
	render();
	SDL_Delay(3000);
}

void Pong::render() {
	// Clear screen (background color).
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Paddle color.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Render ball.
	SDL_Rect pong_ball = { ball-> _x, ball-> _y, ball->LENGTH, ball->LENGTH };
	SDL_RenderFillRect(renderer, &pong_ball);

	// Swap buffers.
	SDL_RenderPresent(renderer);

}
