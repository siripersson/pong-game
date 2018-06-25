/*
 *******************************************************************************
 * File   : paddle.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Source file for the paddle actor-class
 *******************************************************************************
 */

#include "paddle.h"
#include "keyboard.h"

const int Paddle::HEIGHT;
const int Paddle::WIDTH;

void Paddle::updatePaddlePosition(int new_y)
{
    y += new_y;
}

