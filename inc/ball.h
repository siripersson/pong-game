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

	struct Speed
	{
		int dx = 0;
		int dy = 0;
	};

	enum class ServingPlayer
	{
		One,
		Two,
	};

	/* Getters */
	const Position& getPosition() const;
	const Speed& getSpeed() const;
	int getSize() const;

	/* Setters */
	void setPosition(int x, int y);
	void setSpeed(int dx, int dy);
	void setSize(int size);

	/* Gameplay functions */
	void update();
	void render(SDL_Renderer *renderer);
	void setupServe(ServingPlayer, PongTable table);


private:
	/* Member variables */
	int _size = 20;
	Position _position;
	Speed _speed;
};
