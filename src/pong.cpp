/*
 *******************************************************************************
 * File   : pong.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Source file for the pong game-runner class
 *******************************************************************************
 */

#include "pong.h"

/* Top level class, hosts all actors and runs the pong-game*/
Pong::Pong(int argc, char *argv[]) 
{
	/* Create window for game, and associate a graphics renderer */
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* Initialize game loop timer */


	/* Create all game actors */
	ball = new Ball(SCREEN_WIDTH/2-ball->LENGTH/2, SCREEN_HEIGHT/2-ball->LENGTH/2);
	left_paddle = new Paddle(40, SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);
	right_paddle = new Paddle(SCREEN_WIDTH-(40+Paddle::WIDTH), SCREEN_HEIGHT/2 - Paddle::HEIGHT/2);

}

/* Destructor run once at end of program */
Pong::~Pong() 
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/* Continously runs game until quit */
void Pong::execute() 
{
	// maybe these should be declared somewhere else?
	SDL_Event e; 
	bool userRequestExit = false;

	// DEVELOPER TEST: RUN GAME FOR SOME FRAMES
	while(userRequestExit != true)
	{
		/* Get time stamp at frame start */
		Uint32 frameStartMilliseconds = SDL_GetTicks();
		this->currentFrame++;

		// DEVELOPER TEST: CHECK IF USER WANTS TO EXIT
		if((SDL_PollEvent(&e) == true)  && e.type == SDL_QUIT)
		{
			userRequestExit = true;
		}

		/* Run current frame */
		input();
		update();
		render();

		/* Wait until end of frame */
		while(SDL_GetTicks() - frameStartMilliseconds < 33);	
	}
}


/* Read all keyboard inputs */
void Pong::input()
{
	// todo
}

/* Update game state based one frame */
void Pong::update()
{
	// ugly test
	if(this->currentFrame % 60 == 0)
		left_paddle->x = 20;
	else if((this->currentFrame + 30) % 60 == 0)
		left_paddle->x = 200;
}

/* Renders all graphic onto the screen for current frame */
void Pong::render() 
{
	// todo: make meaningful comment for what these function calls do
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect paddle1 = {left_paddle->x, left_paddle->y, Paddle::WIDTH, Paddle::HEIGHT};
	SDL_RenderFillRect(renderer, &paddle1);

	SDL_Rect paddle2 = {right_paddle->x, right_paddle->y, Paddle::WIDTH, Paddle::HEIGHT};
	SDL_RenderFillRect(renderer, &paddle2);

	SDL_Rect pong_ball = {ball->x, ball->y, ball->LENGTH, ball->LENGTH};
	SDL_RenderFillRect(renderer, &pong_ball);

	SDL_RenderPresent(renderer);

}
