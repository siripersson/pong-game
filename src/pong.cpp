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
	const int screen_width = PongTable::TABLE_WIDTH;
	const int screen_heigth = PongTable::TABLE_HEIGHT;

	/* Create window for game, and associate a graphics renderer */
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, screen_width, screen_heigth, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* Create all game actors */
	Ball();
	left_paddle = new Paddle(40, screen_heigth/2 - Paddle::HEIGHT/2);
	right_paddle = new Paddle(screen_width-(40+Paddle::WIDTH), screen_heigth/2 - Paddle::HEIGHT/2);

	/* Setup first round */
	ball.setupRound(Ball::Player::Player_1);

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
	// todo
}

/* Renders all graphic onto the screen for current frame */
void Pong::render() 
{
	// todo: make meaningful comment for what these function calls do
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	/* Render actors */
	SDL_Rect paddle1 = {left_paddle->x, left_paddle->y, Paddle::WIDTH, Paddle::HEIGHT};
	SDL_RenderFillRect(renderer, &paddle1);
    
	SDL_Rect paddle2 = {right_paddle->x, right_paddle->y, Paddle::WIDTH, Paddle::HEIGHT};
	SDL_RenderFillRect(renderer, &paddle2);

	ball.render(renderer);

	SDL_RenderPresent(renderer);

}
