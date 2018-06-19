/*
 *******************************************************************************
 * File   : ball.h
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Header for the pong ball class
 *******************************************************************************
 */

#pragma once

class Paddle;

class Ball {
public:
	Ball(int x, int y);
	~Ball() {} 

	static const int LENGTH;

	int _x;
	int _y;
};
