/*
 *******************************************************************************
 * File   : paddle.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Source file for the paddle actor-class
 *******************************************************************************
 */

#include "paddle.h"

const int Paddle::HEIGHT;
const int Paddle::WIDTH;

Paddle::Paddle()
{
	_position = {0, 0};
	_speed = 10;
}


Paddle::Paddle(int x, int y)
{
	_position = {x, y};
	_speed = 3;
}


/* Getters */
const Paddle::Position& Paddle::getPosition() const
{
	return _position;
};
const int Paddle::getSpeed() const
{
	return _speed;
};

/* Setters */
void Paddle::setPosition(int x, int y)
{
	_position = {x, y};
}
void Paddle::setSpeed(int dy)
{
	_speed = dy;
}



/* Gameplay functions */
void Paddle::update(int dy)
{
	_position.y += dy;

	// Paddle not allowed to go above or below the pongtable
	if(_position.y < 0)
		_position.y = 0;
	else if(_position.y + HEIGHT > pongTable.getHeight())
		_position.y = pongTable.getHeight() - HEIGHT;

}

void Paddle::render(SDL_Renderer *renderer)
{
	/* Set draw color to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	/* Draw paddle as white rectangle */
	SDL_Rect paddle = {_position.x, _position.y, WIDTH, HEIGHT};
	SDL_RenderFillRect(renderer, &paddle);
}


