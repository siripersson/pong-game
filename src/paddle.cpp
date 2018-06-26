/*
 *******************************************************************************
 * File   : paddle.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Source file for the paddle actor-class
 *******************************************************************************
 */

#include "paddle.h"



/* Constructors --------------------------------------------------------------*/
Paddle::Paddle()
{
	_topLeftCornerPosition = {0, 0};
	_dimensions = {60, 10};
}

Paddle::Paddle(int x, int y)
{
	_topLeftCornerPosition = {x, y};
	_dimensions = {60, 10};
}

Paddle::Paddle(int x, int y, int heigth, int width)
{
	_topLeftCornerPosition = {x, y};
	_dimensions = {heigth, width};
}



/* Setters -------------------------------------------------------------------*/
void Paddle::setTopLeftCornerPosition(int x, int y)
{
	_topLeftCornerPosition = {x, y};
}

void Paddle::setDimensions(int heigth, int width)
{
	_dimensions = {heigth, width};
}



/* Getters -------------------------------------------------------------------*/
const Paddle::Dimensions& Paddle::getDimensions() const
{
	return _dimensions;
}

const int Paddle::getHeigth() const
{
	return _dimensions.heigth;
}

const int Paddle::getWidth() const
{
	return _dimensions.width;
}

const Paddle::Position& Paddle::getTopLeftCornerPosition() const
{
	return _topLeftCornerPosition;
}

Paddle::Position Paddle::getTopRightCornerPosition() const
{
	int x = _topLeftCornerPosition.x + _dimensions.width;
	int y = _topLeftCornerPosition.y;
	return {x, y};
}

Paddle::Position Paddle::getBottomLeftCornerPosition() const
{
	int x = _topLeftCornerPosition.x;
	int y = _topLeftCornerPosition.y + _dimensions.heigth;
	return {x, y};
}

Paddle::Position Paddle::getBottomRightCornerPosition() const
{
	int x = _topLeftCornerPosition.x + _dimensions.width;
	int y = _topLeftCornerPosition.y + _dimensions.heigth;
	return {x, y};
}



/* Game loop functions -------------------------------------------------------*/
void Paddle::render(SDL_Renderer *renderer)
{
	/* Set draw color to white */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	/* Draw paddle as white rectangle */
	Position pos = _topLeftCornerPosition;
	SDL_Rect paddle = {pos.x, pos.y, _dimensions.width, _dimensions.heigth};
	SDL_RenderFillRect(renderer, &paddle);
}