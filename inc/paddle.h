/*
 *******************************************************************************
 * File   : paddle.h
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Header file for the paddle actor-class
 *******************************************************************************
 */

#pragma once

/* Includes ------------------------------------------------------------------*/
// none

/* Class declarations --------------------------------------------------------*/
class Paddle 
{
public:
	struct Position
	{
		int x;
		int y;
	};

	struct Dimensions
	{
		int heigth;	
		int width;
	};

	/* Constructors */
	Paddle();
	Paddle(int x, int y);
	Paddle(int x, int y, int heigth, int width);

	/* Setters */
	void setTopLeftCornerPosition(int x, int y);
	void setDimensions(int heigth, int width);

	/* Getters */
	const Position& getTopLeftCornerPosition() const;
	const Dimensions& getDimensions() const;
	Position getBottomRightCornerPosition() const;

private:
	Position _topLeftCornerPosition;
	Dimensions _dimensions;
};

