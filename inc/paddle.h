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
#include "ball.h"
#include <string>

class Ball;
class Keyboard;


/* Class declarations --------------------------------------------------------*/
class Ball;
class Paddle 
{
public:
	Paddle();
	Paddle(int x, int y) : x(x), y(y) {};

	static const int HEIGHT = 60;
	static const int WIDTH = 10;

	int x;
	int y;

	void updatePaddlePosition(int new_y);

};

