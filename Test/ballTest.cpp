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
};

/* Unit test example */
TEST_F(BallTest, Constructor_Can_Set_Position)
{
	/* Setup */
	int expected_x = 2;
	int expected_y = 3;
	Ball ball = Ball(expected_x, expected_y);

	/* Check */
	EXPECT_EQ(ball.x, expected_x);
	EXPECT_EQ(ball.y, expected_y);
}

/* Another unit test example */
TEST_F(BallTest, Constructor_Has_Default_Position)
{
	/* Setup */
	int expected_x = 0;
	int expected_y = 0;
	Ball ball;

	/* Check */
	EXPECT_EQ(ball.x, expected_x);
	EXPECT_EQ(ball.y, expected_y);
}