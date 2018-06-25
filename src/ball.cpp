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
const Ball::Speed& Ball::getSpeed() const
{
	return _speed;
};

const Ball::Position& Ball::getTopLeftCornerPosition() const
{
	return _topLeftCornerPosition;
};

Ball::Position Ball::getBottomRightCornerPosition() const
{
	int x = _topLeftCornerPosition.x + _size;
	int y = _topLeftCornerPosition.y + _size;
	return {x, y};
}

Ball::Position Ball::getPositionOfCenter() const
{
	int x = _topLeftCornerPosition.x + _size/2;
	int y = _topLeftCornerPosition.y + _size/2;
	return {x, y};
}

int Ball::getSize() const
{
	return _size; // in pixels
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
	Position position = _topLeftCornerPosition;
	SDL_Rect pong_ball = {position.x, position.y, _size, _size};
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


/* Padel overlap detection ---------------------------------------------------*/
bool Ball::isOverlappingPaddle(Paddle& paddle)
{
	bool isOverlapping;

	if(this->isWithinHorizontalBounds(paddle))
	{
		if(this->isBellowPaddleTopSide(paddle) && this->isAbovePaddleBottomSide(paddle))
			isOverlapping = true;
	}
	else if(this->isWithinVerticalBounds(paddle))
	{
		if(this->isRightOfPaddleLeftSide(paddle) && this->isLeftOfPaddleRightSide(paddle))
			isOverlapping = true;
	}
	else
	{
		isOverlapping = false;
	}

	return isOverlapping;
}

// note: this function might be assuming that the ball is always smaller than
// the paddle is, so there should be a test for this function with the case 
// that the ball is bigger than the paddle!
bool Ball::isWithinHorizontalBounds(Paddle& paddle)
{
	bool isOverlapping;

	if(this->isRightOfPaddleLeftSide(paddle) && this->isLeftOfPaddleRightSide(paddle))
		isOverlapping = true;
	else
		isOverlapping = false;

	return isOverlapping;
}

bool Ball::isWithinVerticalBounds(Paddle& paddle)
{
	bool isOverlapping;

	if(this->isBellowPaddleTopSide(paddle) && this->isAbovePaddleBottomSide(paddle))
		isOverlapping = true;
	else
		isOverlapping = false;

	return isOverlapping;
}

bool Ball::isRightOfPaddleLeftSide(Paddle& paddle)
{
	int ballRightSide = _topLeftCornerPosition.x + _size;
	int horizontalBoundLeftSide = paddle.getTopLeftCornerPosition().x;

	return (ballRightSide > horizontalBoundLeftSide);
}

bool Ball::isLeftOfPaddleRightSide(Paddle& paddle)
{
	int ballLeftSide = _topLeftCornerPosition.x;
	int horizontalBoundRightSide = paddle.getTopLeftCornerPosition().x + paddle.getDimensions().width;

	return (ballLeftSide < horizontalBoundRightSide);
}

bool Ball::isBellowPaddleTopSide(Paddle& paddle)
{
	int ballBottomSide = _topLeftCornerPosition.y + _size;
	int verticalBoundTopSide = paddle.getTopLeftCornerPosition().y;

	return (ballBottomSide > verticalBoundTopSide);
}

bool Ball::isAbovePaddleBottomSide(Paddle& paddle)
{
	int ballTopSide = _topLeftCornerPosition.y;
	int verticalBoundBottomSide = paddle.getTopLeftCornerPosition().y + paddle.getDimensions().heigth;

	return (ballTopSide < verticalBoundBottomSide);
}

/* Padel collision detection -------------------------------------------------*/
bool Ball::wouldCollideHorizontally(Paddle& paddle)
{
	return true;
}