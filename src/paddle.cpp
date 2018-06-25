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
	_position = {0, 0};
	_dimensions = {60, 10};
}

Paddle::Paddle(int x, int y)
{
	_position = {x, y};
	_dimensions = {60, 10};
}

Paddle::Paddle(int x, int y, int heigth, int width)
{
	_position = {x, y};
	_dimensions = {heigth, width};
}

/* Setters -------------------------------------------------------------------*/
void Paddle::setUpperLeftCornerPosition(int x, int y)
{
	_position = {x, y};
}

void Paddle::setDimensions(int heigth, int width)
{
	_dimensions = {heigth, width};
}

/* Getters -------------------------------------------------------------------*/
const Paddle::Position& Paddle::getPosition() const
{
	return _position;
}

const Paddle::Dimensions& Paddle::getDimensions() const
{
	return _dimensions;
}

Paddle::Position Paddle::getBottomRightCornerPosition() const
{
	int x = _position.x + _dimensions.width;
	int y = _position.y + _dimensions.heigth;
	return {x, y};
}