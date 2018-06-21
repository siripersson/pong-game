/*
 *******************************************************************************
 * File   : pongTable.h
 * Date   : 20 Jun 2018
 * Author : Rasmus @ Sylog Sverige AB
 * Brief  :
 *******************************************************************************
 */

#pragma once

/* Includes ------------------------------------------------------------------*/
// none

/* Class declarations --------------------------------------------------------*/
class PongTable
{
public:
	PongTable();
	PongTable(int width, int height);

	int getWidth() const;
	int getHeight() const;
private:
	int _width;
	int _height;
};