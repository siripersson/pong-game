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
#include "paddle.h"

/* Class declarations --------------------------------------------------------*/
class Paddle;
class Ball 
{
public:
	Ball() {};
	Ball(int x, int y) : x(x), y(y) {};
	~Ball() {};

	static const int LENGTH = 10;

	int x;
	int y;
};
