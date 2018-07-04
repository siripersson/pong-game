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
#include "pongTable.h"
#include "render.h"
#include "paddle.h"
#include <string>
#include <iostream>
#include <math.h>
#include <random>

class Paddle;

/* Class declarations --------------------------------------------------------*/
class Ball 
{
public:
	/* Constructors and destructors */
	Ball() {};
	Ball(int x, int y);
	~Ball() {};

	struct Position
	{
		int x = 0;
		int y = 0;
	};

	struct Movement
	{
		int dx = 0;
		int dy = 0;
	};

	int _speed = 0;
	float _angle;

	enum class ServingPlayer
	{
		One,
		Two,
	};

	/* Getters */
	const Position& getPosition() const;
	const Movement& getMovement() const;
	const int getSpeed() const;
	int getSize() const;

	/* Setters */
	void setPosition(int x, int y);
	void setMovement(int dx, int dy);
	void setSpeed(int speed);
	void setSize(int size);

	/* Gameplay functions */
	void updatePosition();
	void render(SDL_Renderer *renderer);
	void setupServe(ServingPlayer, PongTable table);

	bool wallCollision();
	void reverseBallYdirection ();

	bool collidesWith(Paddle paddle);
	void bouncesOff(Paddle paddle);

private:
	/* Member variables */
	const int serveBallSpeed = 10;
	int _size = 20;
	Position _position;
	Movement _movement;
	PongTable pongTable;
};
