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
#include <cmath>

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
	const Speed& getSpeed() const;
	const Position& getTopLeftCornerPosition() const;
	Position getTopRightCornerPosition() const;
	Position getBottomLeftCornerPosition() const;
	Position getBottomRightCornerPosition() const;
	Position getPositionOfCenter() const;
	int getSize() const;

	/* Setters */
	void setTopLeftCornerPosition(int x, int y);
	void setTopRightCornerPosition(int x, int y);
	void setSpeed(int dx, int dy);
	void setSize(int size);

	/* Game loop functions */
	void update(Paddle& leftPaddle, Paddle& rightPaddle, PongTable& pongTable);
	void render(SDL_Renderer *renderer);
	
	/* Update functions */
	void setupServe(ServingPlayer player, PongTable table);
	void executeMovementForThisFrame(Paddle& leftPaddle, Paddle& rightPaddle, PongTable& table);
	void moveOneStep();
	

	// these two are deprecated! remove later
	void moveAndStopIfNextTo(Paddle& paddle); 
	void changeDirectionIfCollidedWith(Paddle& paddle);

	/* Overlap detection */
	bool isOverlappingPaddle(Paddle& paddle);

	bool wouldOverlapHorizontallyWith(Paddle& paddle);
	bool wouldOverlapVerticallyWith(Paddle& paddle);
	bool wouldOverlapDiagonallyWith(Paddle& paddle);
	bool wouldOverlapUpperTableEdge();
	bool wouldOverlapLowerTableEdge(int tableHeigth);

	bool isWithinHorizontalBounds(Paddle& paddle);
	bool isWithinVerticalBounds(Paddle& paddle);
	
	bool isRightOfPaddleLeftSide(Paddle& paddle);
	bool isLeftOfPaddleRightSide(Paddle& paddle);
	bool isBellowPaddleTopSide(Paddle& paddle);
	bool isAbovePaddleBottomSide(Paddle& paddle);

private:
	/* Member variables */
	const int serveBallSpeed = 10;
	int _size = 20;
	Position _topLeftCornerPosition;
	Speed _speed;
};
