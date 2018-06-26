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
#include "pongTable.h"
#include <string>
#include<iostream>

/* Class declarations --------------------------------------------------------*/
class Paddle 
{
public:
	Paddle();
	Paddle(int x, int y);
	~Paddle() {};

	static const int HEIGHT = 60;
	static const int WIDTH = 10;

	struct Position
	{
				int x = 0;
				int y = 0;
	};

	int _speed = 0;

	/* Getters */
	const Position& getPosition() const;
	const int getSpeed() const;

	/* Setters */
	void setPosition(int x, int y);
	void setSpeed(int dy);

	/* Gameplay functions */
	void update(int dy);
	void render(SDL_Renderer *renderer);
	bool isOutsideLowerBorder();
	bool isOutsideUpperBorder();

private:
	Position _position;
	PongTable pongTable;

};

