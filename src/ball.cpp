/*
 *******************************************************************************
 * File   : ball.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist @ Sylog Sverige AB
 * Brief  : Source file for the pong ball class
 *******************************************************************************
 */

#include "ball.h"

/* Function definitions ------------------------------------------------------*/
/* Constructors */
Ball::Ball(int x, int y) 
{
	_position = {x, y};
	_speed = {0, 0};
}


/* Getters */
const Ball::Position& Ball::getPosition() const
{
	return _position;
};

const Ball::Speed& Ball::getSpeed() const
{
	return _speed;
};

int Ball::getSize() const
{
	return _size; // in pixels
}


/* Setters */
void Ball::setPosition(int x, int y)
{
	_position = {x, y};
}

void Ball::setSpeed(int dx, int dy)
{
	_speed = {dx, dy};
}

void Ball::setSize(int size)
{
	_size = size;
}


/* Gameplay */
void Ball::update()
{
	_position.x += _speed.dx;
	_position.y += _speed.dy;
}

void Ball::render(SDL_Renderer *renderer)
{
	/* Set draw color to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	/* Draw ball as white rectangle */
	SDL_Rect pong_ball = {_position.x, _position.y, _size, _size};
	SDL_RenderFillRect(renderer, &pong_ball);
}

void Ball::setupServe(Ball::ServingPlayer player, PongTable table)
{
	/* Place ball in middle of table */
	int x = (table.getWidth() - _size) / 2;
	int y = (table.getHeight() - _size) / 2;
	_position = {x, y};

	/* Set starting movement */
	int dx;
	int dy = 0;
	if(player == ServingPlayer::One)
		dx = -1;
	if(player == ServingPlayer::Two)
		dx = 1;

	_speed =  {dx, dy};
}

