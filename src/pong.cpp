﻿/*
 *******************************************************************************
 * File   : pong.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Source file for the pong game-runner class
 *******************************************************************************
 */
#include "pong.h"
#include "ball.h"
#include "paddle.h"
#include "keyboard.h"
#include "render.h"

using namespace std;

/* Top level class, hosts all actors and runs the pong-game*/
Pong::Pong(int argc, char *argv[])
{
	const int screen_width = pongTable.getWidth();
	const int screen_height = pongTable.getHeight();

	/* Create window for game, and associate a graphics renderer */
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	/* Create all game actors */
	leftPaddle.setPosition(40, screen_height/2 - Paddle::HEIGHT/2);
	rightPaddle.setPosition(screen_width-(40 + Paddle::WIDTH), screen_height/2 - Paddle::HEIGHT/2);
	keyboard = new Keyboard();

	/* Setup first round */
	ball.setupServe(Ball::ServingPlayer::One, pongTable);
	exit = false;
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
	while(!exit)
	{
		/* Get time stamp at frame start */
		Uint32 frameStartMilliseconds = SDL_GetTicks();
		currentFrame++;

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
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		exit = keyboard->checkIfPressedQuit(event);
		keyboard->handleKeyboardEvent(event);
	}
}

/* Update game state based one frame */
void Pong::update()
{
	ball.update();

	if(keyboard->isPressed("SDLK_UP") && keyboard->isPressed("SDLK_w"))
	{
		if(!rightPaddle.isOutsideUpperBorder() )
			rightPaddle.update(rightPaddle.getSpeed() * -1);
		if(!leftPaddle.isOutsideUpperBorder() )
			leftPaddle.update(leftPaddle.getSpeed() * -1);
	}
	else if(keyboard->isPressed("SDLK_UP") && keyboard->isPressed("SDLK_s"))
	{
		if(!rightPaddle.isOutsideUpperBorder())
			rightPaddle.update(rightPaddle.getSpeed() * -1);
		if(!leftPaddle.isOutsideLowerBorder())
			leftPaddle.update(leftPaddle.getSpeed());
	}
	else if(keyboard->isPressed("SDLK_DOWN") && keyboard->isPressed("SDLK_w"))
	{
		if(!rightPaddle.isOutsideLowerBorder())
			rightPaddle.update(rightPaddle.getSpeed());
		if(!leftPaddle.isOutsideUpperBorder())
			leftPaddle.update(leftPaddle.getSpeed() * -1);
	}
	else if(keyboard->isPressed("SDLK_DOWN") && keyboard->isPressed("SDLK_s"))
	{
		if(!rightPaddle.isOutsideLowerBorder())
			rightPaddle.update(rightPaddle.getSpeed());
		if(!leftPaddle.isOutsideLowerBorder())
			leftPaddle.update(leftPaddle.getSpeed());
	}

	else if(keyboard->isPressed("SDLK_UP") && !rightPaddle.isOutsideUpperBorder())
		rightPaddle.update(rightPaddle.getSpeed() * -1);

	else if(keyboard->isPressed("SDLK_DOWN") && !rightPaddle.isOutsideLowerBorder())
		rightPaddle.update(rightPaddle.getSpeed());

	else if(keyboard->isPressed("SDLK_w") && !leftPaddle.isOutsideUpperBorder())
		leftPaddle.update(leftPaddle.getSpeed() *-1);

	else if(keyboard->isPressed("SDLK_s") && !leftPaddle.isOutsideLowerBorder())
		leftPaddle.update(leftPaddle.getSpeed());
}

/* Renders all graphic onto the screen for current frame */
void Pong::render() 
{
	/* Draw black background */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	/* Set draw color to white and draw actors */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	leftPaddle.render(renderer);
	rightPaddle.render(renderer);
	ball.render(renderer);

	SDL_RenderPresent(renderer);

}
