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
	const int screen_width = pongTable.getWidth();
	const int screen_height = pongTable.getHeight();

	/* Create window for game, and associate a graphics renderer */
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* Initialize Padles */
	left_paddle.setTopLeftCornerPosition(
		40, (screen_height/2 - left_paddle.getHeigth()/2));
	
	right_paddle.setTopLeftCornerPosition(
		screen_width - 40, screen_height/2 - right_paddle.getHeigth()/2);

	/* Setup first round */
	ball.setupServe(Ball::ServingPlayer::One, pongTable);

}

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

	while(userRequestExit != true)
	{
		/* Get time stamp at frame start */
		Uint32 frameStartMilliseconds = SDL_GetTicks();
		currentFrame++;

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
	ball.update(left_paddle, right_paddle);
}

/* Renders all graphic onto the screen for current frame */
void Pong::render() 
{
	/* Draw black background */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


	/* Set draw color to white and draw actors */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	left_paddle.render(renderer);
	right_paddle.render(renderer);
	ball.render(renderer);

	SDL_RenderPresent(renderer);

}
