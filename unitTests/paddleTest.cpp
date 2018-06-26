/*
 *******************************************************************************
 * File   : paddleTest.cpp
 * Date   : 25 Jun 2018
 * Author : Siri Persson @ Sylog Sverige AB
 * Brief  : Header file for the pong game-runner class
 *******************************************************************************
 */
#include "gtest/gtest.h"
#include "paddle.h"
#

class PaddleTest : public ::testing::Test
{
public:
	Paddle paddle;
	PongTable pongTable;

	void initilizePaddleOutsideUpperBorder(){
		paddle.setPosition(40, 0);
	}

	void initilizePaddleOutsideLowerBorder(){
		paddle.setPosition(40, pongTable.getHeight());
	}
};

/* Unit test example */
TEST_F(PaddleTest, Check_If_Paddle_Outside_Upper_Border)
{
	/* Arrange */
	bool expectedIsOutsideUpperBorder = true;

	/* Act */
	initilizePaddleOutsideUpperBorder();
	bool actualIsOutsideUpperBorder = paddle.isOutsideUpperBorder();

	/* Assert */
	EXPECT_EQ(actualIsOutsideUpperBorder, expectedIsOutsideUpperBorder);
}

TEST_F(PaddleTest, Check_If_Paddle_Outside_Lower_Border)
{
	/* Arrange */
	bool expectedIsOutsideLowerBorder = true;

	/* Act */
	initilizePaddleOutsideLowerBorder();
	bool actualIsOutsideLowerBorder = paddle.isOutsideLowerBorder();

	/* Assert */
	EXPECT_EQ(actualIsOutsideLowerBorder, expectedIsOutsideLowerBorder);
}




