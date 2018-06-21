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
TEST_F(BallTest, Select_Player1_For_Serve)
{
	/* Run the setup to position in middle of board, and set speed towards 
	 * player 1 (assumed to be to the left) */
	ball.setupRound(Ball::Player::Player_1);

	/* Check that ball ended up in the middle */
	int expected_x = (pongTable.getWidth() + ball.getSize()) / 2;
	int expected_y = (pongTable.getHeight() + ball.getSize()) / 2;

	Ball::Position actualPosition = ball.getPosition();
	EXPECT_EQ(expected_x, actualPosition.x);
	EXPECT_EQ(expected_y, actualPosition.y);

	/* Check that the speed is in the left direction (negative dx) */
	Ball::Speed actualSpeed = ball.getSpeed();
	EXPECT_LT(actualSpeed.dx, 0);
}