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

	enum class Player
	{
		Player_1,
		Player_2,
	};

	/* Getter functions */
	const Position& getPosition() const;
	const Speed& getSpeed() const;
	int getSize() const;

	/* Setter functions */
	void setCoordinates(int x, int y);

	/* Gameplay functions */
	void setupRound(Player);
	void render(SDL_Renderer *renderer);

private:
	/* Member variables */
	int _size = 20;
	Position _position;
	Speed _speed;
};
