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
	struct Dimensions
	{
		int heigth;	
		int width;
	};

	struct Position
	{
		int x;
		int y;
	};

	/* Constructors */
	Paddle();
	Paddle(int x, int y);
	Paddle(int x, int y, int heigth, int width);

	/* Setters */
	void setTopLeftCornerPosition(int x, int y);
	void setDimensions(int heigth, int width);

	/* Getters */
	const Dimensions& getDimensions() const;
	const Position& getTopLeftCornerPosition() const;
	Position getBottomLeftCornerPosition() const;
	Position getTopRightCornerPosition() const;
	Position getBottomRightCornerPosition() const;

private:
	Position _topLeftCornerPosition;
	Dimensions _dimensions;
};

