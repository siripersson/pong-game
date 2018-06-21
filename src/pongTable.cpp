/*
 *******************************************************************************
 * File   : pongTable.cpp
 * Date   : 20 Jun 2018
 * Author : Rasmus @ Sylog Sverige AB
 * Brief  :
 *******************************************************************************
 */

#include "pongTable.h"

/* Function definitions ------------------------------------------------------*/
PongTable::PongTable()
{
	_width = 640;
	_height = 480;
}

PongTable::PongTable(int width, int height)
{
	_width = width;
	_height = height;
}

int PongTable::getWidth() const
{
	return _width;
}


int PongTable::getHeight() const
{
	return _height;
}