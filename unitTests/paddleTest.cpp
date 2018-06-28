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
};

/* Unit test example */
TEST_F(PaddleTest, verify_Position_After_Moving_Paddle_Outside_Upper_Border)
{
	/* Arrange */
	int expectedPosition = 0;
	int speedUpward = -3;

	/* Act */
	paddle.setPosition(40, 2);
	paddle.update(speedUpward);
	int actualPosition = paddle.getPosition().y;

	/* Assert */
	EXPECT_EQ(actualPosition, expectedPosition);
}

TEST_F(PaddleTest, verify_Position_After_Moving_Paddle_Outside_Lower_Border)
{
	/* Arrange */
	int expectedPosition = pongTable.getHeight() - Paddle::HEIGHT;
	int speedDownward = 3;

	/* Act */
	paddle.setPosition(40, pongTable.getHeight() - 2);
	paddle.update(speedDownward);
	int actualPosition = paddle.getPosition().y;

	/* Assert */
	EXPECT_EQ(actualPosition, expectedPosition);
}




