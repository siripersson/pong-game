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

/* Constructor tests ---------------------------------------------------------*/
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

/* Round Setup tests ---------------------------------------------------------*/
TEST_F(BallTest, Player_1_Served_Ball_Starts_In_Middle)
{
	const int ballSize = 10;
	const int tableSideLength = 100;
	PongTable pongTable(tableSideLength, tableSideLength);
	ball.setSize(ballSize);
	ball.setupRound(Ball::ServingPlayer::One, pongTable);

	/* The middle of the table is found at half the side lengths. To get the 
	 * ball centered in the middle, and not a little off of the right, we nudge 
	 * the upper left corner from the center by half the ball's size. */
	int expected_x = (tableSideLength / 2) - (ballSize / 2);
	int expected_y = (tableSideLength / 2) - (ballSize / 2);

	Ball::Position actualPosition = ball.getPosition();
	EXPECT_EQ(expected_x, actualPosition.x);
	EXPECT_EQ(expected_y, actualPosition.y);
}

// TODO ball moves to the left test