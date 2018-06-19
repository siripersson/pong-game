/*
 *******************************************************************************
 * File   : ball.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Source file for the pong ball class
 *******************************************************************************
 */

#include "ball.h"
#include "pong.h"
#include "paddle.h"

const int Ball::LENGTH = 10;

Ball::Ball(int x, int y){
	_x = x;
	_y = y;

}

