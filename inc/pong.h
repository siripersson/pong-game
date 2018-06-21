/*
 *******************************************************************************
 * File   : pong.h
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Header file for the pong game-runner class
 *******************************************************************************
 */

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "render.h"
#include "ball.h"
#include "paddle.h"
#include "pongTable.h"
#include <SDL.h>

/* Class declarations --------------------------------------------------------*/
class Pong 
{
private:
	/* SDL entities */
	SDL_Window *window;
	SDL_Renderer *renderer;

	/* Timing */
	int currentFrame;
	
	/* Game actors */
	Ball ball;
	Paddle* left_paddle;
	Paddle* right_paddle;

public:
	Pong(int argc, char *argv[]);
	~Pong();

	/* Game running functions */
	void execute();
	void input();
	void update();
	void render();
};
