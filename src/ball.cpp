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


// TODO remove const make new Position and return that 
const Ball::Position& Ball::getTopLeftCornerPosition() const
{
	return _topLeftCornerPosition;
};

Ball::Position Ball::getTopRightCornerPosition() const
{
	int x = _topLeftCornerPosition.x + _size;
	int y = _topLeftCornerPosition.y;
	return {x, y};
}

Ball::Position Ball::getBottomLeftCornerPosition() const
{
	int x = _topLeftCornerPosition.x;
	int y = _topLeftCornerPosition.y + _size;
	return {x, y};
}

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

void Ball::setTopRightCornerPosition(int x, int y)
{
	_topLeftCornerPosition = {x - _size, y};
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


/* Update functions ----------------------------------------------------------*/
void Ball::setupServe(Ball::ServingPlayer player, PongTable table)
{
	/* Place ball in middle of table */
	int x = (table.getWidth() - _size) / 2;
	int y = (table.getHeight() - _size) / 2;
	_topLeftCornerPosition = {x, y};

	/* Set starting speed */
	int dy = 0;
	int dx;
	if(player == ServingPlayer::One)
		dx = -serveBallSpeed;
	if(player == ServingPlayer::Two)
		dx = serveBallSpeed;

	_speed =  {dx, dy};
}

void Ball::moveAndStopIfNextTo(Paddle& paddle)
{
	int step = (_speed.dx < 0) ? -1 : 1;

	for(int i = 0; i < std::abs(_speed.dx); i++)
	{
		if(this->wouldOverlapHorizontallyWith(paddle))
			break;
		else
			_topLeftCornerPosition.x += step;
	}
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
/* Checks if moving at one step horizontally would cause an overlap */
bool Ball::wouldOverlapHorizontallyWith(Paddle& paddle)
{
	bool wouldOverlap;
	Position initialPosition = _topLeftCornerPosition;

	int step = (_speed.dx < 0) ? -1 : 1;

	_topLeftCornerPosition.x += step;	
	wouldOverlap = isOverlappingPaddle(paddle);

	_topLeftCornerPosition = initialPosition;

	return wouldOverlap;
}

bool Ball::wouldOverlapVerticallyWith(Paddle& paddle)
{
	bool wouldOverlap;
	Position initialPosition = _topLeftCornerPosition;

	int step = (_speed.dy < 0) ? -1 : 1;

	_topLeftCornerPosition.y += step;	
	wouldOverlap = isOverlappingPaddle(paddle);

	_topLeftCornerPosition = initialPosition;

	_topLeftCornerPosition = initialPosition;

	return wouldOverlap;
}