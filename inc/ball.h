/*
 *******************************************************************************
 * File   : ball.h
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Header for the pong ball class
 *******************************************************************************
 */

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "pong.h"
#include <SDL.h>

/* Class definitions ---------------------------------------------------------*/
class Ball 
{
public:
	Ball(){};
	Ball(int x, int y) : x(x), y(y) {};
	~Ball() {} 

	/* Dimension */
	static const int LENGTH = 10;

	/* Position */
	int x;
	int y;
};
