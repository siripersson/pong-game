/*
 *******************************************************************************
 * File   : ball.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist @ Sylog Sverige AB
 * Brief  : Source file for the pong ball class
 *******************************************************************************
 */

#include "ball.h"

/* Constructors --------------------------------------------------------------*/
Ball::Ball(int x, int y) 
{
	_topLeftCornerPosition = {x, y};
	_speed = {0, 0};
}

Ball::Ball(int x, int y, int size) 
{
	_topLeftCornerPosition = {x, y};
	_speed = {0, 0};
	_size = size;
}


/* Getters -------------------------------------------------------------------*/
const Ball::Position& Ball::getTopLeftCornerPosition() const
{
	return _topLeftCornerPosition;
};

const Ball::Speed& Ball::getSpeed() const
{
	return _speed;
};

int Ball::getSize() const
{
	return _size; // in pixels
}

Ball::Position Ball::getPositionOfCenter() const
{
	int x = _topLeftCornerPosition.x + _size/2;
	int y = _topLeftCornerPosition.y + _size/2;
	return {x, y};
}


/* Setters -------------------------------------------------------------------*/
void Ball::setTopLeftCornerPosition(int x, int y)
{
	_topLeftCornerPosition = {x, y};
}

void Ball::setSpeed(int dx, int dy)
{
	_speed = {dx, dy};
}

void Ball::setSize(int size)
{
	_size = size;
}


/* Gameloop functions --------------------------------------------------------*/
void Ball::update()
{
	_topLeftCornerPosition.x += _speed.dx;
	_topLeftCornerPosition.y += _speed.dy;
}

void Ball::render(SDL_Renderer *renderer)
{
	/* Set draw color to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	/* Draw ball as white rectangle */
	SDL_Rect pong_ball = {_topLeftCornerPosition.x, _topLeftCornerPosition.y, _size, _size};
	SDL_RenderFillRect(renderer, &pong_ball);
}


/* Movement ------------------------------------------------------------------*/
void Ball::setupServe(Ball::ServingPlayer player, PongTable table)
{
	/* Place ball in middle of table */
	int x = (table.getWidth() - _size) / 2;
	int y = (table.getHeight() - _size) / 2;
	_topLeftCornerPosition = {x, y};

	/* Set starting movement */
	int dx;
	int dy = 0;
	if(player == ServingPlayer::One)
		dx = -serveBallSpeed;
	if(player == ServingPlayer::Two)
		dx = serveBallSpeed;

	_speed =  {dx, dy};
}

/* Collision detection -------------------------------------------------------*/
bool Ball::isOverlappingPaddle(Paddle& paddle)
{
	bool overlap = false;
	int paddle_x = paddle.getPosition().x;
	int paddle_y = paddle.getPosition().y;
	int paddle_width = paddle.getDimensions().width;
	int paddle_heigth = paddle.getDimensions().heigth;
	int ball_x = _topLeftCornerPosition.x;
	int ball_y = _topLeftCornerPosition.y;

	/* Check overlap with bottom right corner */
	if((ball_y < (paddle_y + paddle_heigth)) 
		&& (ball_x < (paddle_x + paddle_width)))
	{
		overlap = true;
	}

	return overlap;
}
