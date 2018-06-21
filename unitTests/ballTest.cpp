/*
 *******************************************************************************
 * File   : ballTest.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus @ Sylog Sverige AB
 * Brief  : Unit tests for Ball class
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gtest/gtest.h"
#include "ball.h"

class BallTest : public ::testing::Test 
{
public:
	Ball ball;
	PongTable pongTable;
};


/* Constructor ---------------------------------------------------------------*/
TEST_F(BallTest, Default_Constructor_Sets_Default_Size)
{	
	const int expected_default_size = 20;
	
	Ball ball;

	EXPECT_EQ(expected_default_size, ball.getSize());
}

TEST_F(BallTest, Coordinate_Constructor_Sets_Default_Size)
{	
	const int expected_default_size = 20;
	
	Ball ball(1, 2);

	EXPECT_EQ(expected_default_size, ball.getSize());
}


/* Round setup ---------------------------------------------------------------*/
TEST_F(BallTest, Served_Ball_Starts_In_Middle_Of_Pong_Table)
{
	/* Arrange */
	const int ballSize = 10;
	const int tableSideLength = 100;

	PongTable pongTable(tableSideLength, tableSideLength);
	ball.setSize(ballSize);
	ball.setupServe(Ball::ServingPlayer::One, pongTable);

	/* The middle of the table is found at half the side lengths. To get the 
	 * ball centered in the middle, and not a little off of the right, we nudge 
	 * the upper left corner from the center by half the ball's size. */
	int expected_x = (tableSideLength / 2) - (ballSize / 2);
	int expected_y = (tableSideLength / 2) - (ballSize / 2);

	/* Act */
	Ball::Position actualPosition = ball.getPosition();
	
	/* Assert */
	EXPECT_EQ(expected_x, actualPosition.x);
	EXPECT_EQ(expected_y, actualPosition.y);
}

TEST_F(BallTest, When_Player_One_Serves_Ball_Moves_Left)
{
	ball.setupServe(Ball::ServingPlayer::One, pongTable);

	/* If dx is negative, the ball is moving towards the left*/
	EXPECT_LT(ball.getSpeed().dx, 0);
}

TEST_F(BallTest, When_Player_Two_Serves_Ball_Moves_Right)
{
	ball.setupServe(Ball::ServingPlayer::Two, pongTable);

	/* If dx is negative, the ball is moving towards the left*/
	EXPECT_GT(ball.getSpeed().dx, 0);
}


/* Ongoing round -------------------------------------------------------------*/
TEST_F(BallTest, Horizontal_Speed_Of_One_Moves_Ball_One_Pixel_During_Update)
{
	/* Arrange */
	const int initialPos = 10;
	const int dx = -1;
	
	ball.setPosition(initialPos, initialPos);
	ball.setSpeed(dx, 0);

	/* Act */
	ball.update();

	/* Assert */
	EXPECT_EQ(initialPos + dx, ball.getPosition().x);
}

TEST_F(BallTest, Vertical_Speed_Of_One_Moves_Ball_One_Pixel_During_Update)
{
	/* Arrange */
	const int initialPos = 10;
	const int dy = 1;

	ball.setPosition(initialPos, initialPos);
	ball.setSpeed(0, dy);

	/* Act */
	ball.update();

	/* Assert */
	EXPECT_EQ(initialPos + dy, ball.getPosition().y);
}