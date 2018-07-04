/*
 *******************************************************************************
 * File   : ball.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist @ Sylog Sverige AB
 * Brief  : Source file for the pong ball class
 *******************************************************************************
 */

#include "ball.h"

// This will prevent linker errors in case the same
// names are used in other files.
namespace {
    std::random_device rd;
    std::mt19937 gen(rd());
}

/* Function definitions ------------------------------------------------------*/
/* Constructors */
Ball::Ball(int x, int y) 
{
	_position = {x, y};
	_movement = {0, 0};
	_speed = 8;
	_angle = 0.0f;
}


/* Getters */
const Ball::Position& Ball::getPosition() const
{
	return _position;
};

const Ball::Movement& Ball::getMovement() const
{
	return _movement;
};

const int Ball::getSpeed() const
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

void Ball::setMovement(int dx, int dy)
{
	_movement = {dx, dy};
}

void Ball::setSpeed(int speed)
{
	_speed = speed;
}

void Ball::setSize(int size)
{
	_size = size;
}


/* Gameplay */
void Ball::updatePosition()
{
	_position.x += _movement.dx;
	_position.y += _movement.dy;
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

	setSpeed(8); // OBS! Set the speed

	int dx;
	int dy = 0;
	/* Set starting movement */
	if(player == ServingPlayer::One)
		dx = - serveBallSpeed;
	if(player == ServingPlayer::Two)
		dx = serveBallSpeed;

	_movement =  {dx, dy};
}

bool Ball::wallCollision()
{
    return (getPosition().y + getMovement().dy < 0) || (getPosition().y + _size + getMovement().dy >= pongTable.getHeight());
}

void Ball::reverseBallYdirection ()
{
	_movement = {getMovement().dx, getMovement().dy * -1};  // Reverse ball direction on y-axis.
}

bool Ball::collidesWith(Paddle paddle)
{
	 // Check if collision with left paddle occurs in next frame
	if(paddle.getPosition().x < pongTable.getWidth() / 2)
	{
		if(getPosition().x > paddle.getPosition().x + Paddle::WIDTH || getPosition().x < paddle.getPosition().x ||
				!(getPosition().y + _size > paddle.getPosition().y && getPosition().y + Paddle::HEIGHT))
			return false;
		else
			return true;

	} else {
		 // Check if collision with right paddle occurs in next frame.
		 if (getPosition().x + _size < paddle.getPosition().x || getPosition().x > paddle.getPosition().x + Paddle::WIDTH ||
				 !(getPosition().y + _size > paddle.getPosition().y && getPosition().y <= paddle.getPosition().y + Paddle::HEIGHT))
			 return false;
		 else
			 return true;
	}
}
void Ball::bouncesOff(Paddle paddle)
{
	int sign = ( paddle.getPosition().x < pongTable.getWidth() / 2 ) ? 1 : -1;
	int distanceToPaddle = getPosition().y - paddle.getPosition().y + _size;
	_angle = 2.14f * distanceToPaddle - 75.0f;

	int dx = sign * _speed * std::cos(_angle * M_PI / 180.0f); // convert angle to radians
	int dy = _speed * std::sin(_angle * M_PI * 180.0f);

	_movement =  {dx, dy};
}

