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

/* Class declarations --------------------------------------------------------*/
class Ball 
{
public:
	/* Structs and enums */
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

	/* Constructors and destructors */
	Ball() {};
	Ball(int x, int y);
	Ball(int x, int y, int size);
	~Ball() {};

	/* Getters */
	const Position& getTopLeftCornerPosition() const;
	const Speed& getSpeed() const;
	int getSize() const;
	Position getPositionOfBallCenter() const;

	/* Setters */
	void setTopLeftCornerPosition(int x, int y);
	void setSpeed(int dx, int dy);
	void setSize(int size);

	/* Gameloop functions */
	void update();
	void render(SDL_Renderer *renderer);
	
	/* Movement */
	void setupServe(ServingPlayer, PongTable table);

	/* Collision detection */
	bool isOverlappingPaddle(Paddle&);

private:
	/* Member variables */
	const int serveBallSpeed = 10;
	int _size = 20;
	Position _topLeftCornerPosition;
	Speed _speed;
};
