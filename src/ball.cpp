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
Ball::Ball(int x, int y) 
{
	_position = {x, y};
	_speed = {0, 0};
}

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

void Ball::setCoordinates(int x, int y)
{
	_position = {x, y};
}

void Ball::setSize(int size)
{
	_size = size;
}

void Ball::setupRound(Ball::ServingPlayer, PongTable table)
{
	/* Place ball in middle of table */
	int x = (table.getWidth() - _size) / 2;
	int y = (table.getHeight() - _size) / 2;
	_position = {x, y};

	/* Set starting movement */
	int dx = -1;
	int dy = 0;
	_speed =  {dx, dy};
}

void Ball::render(SDL_Renderer *renderer)
{
	/* Set draw color to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	/* Draw ball as white rectangle */
	SDL_Rect pong_ball = {_position.x, _position.y, _size, _size};
	SDL_RenderFillRect(renderer, &pong_ball);
}