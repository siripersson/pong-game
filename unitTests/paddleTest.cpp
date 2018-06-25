/*
 *******************************************************************************
 * File   : paddleTest.cpp
 * Date   : 25 Jun 2018
 * Author : Rasmus @ Sylog Sverige AB
 * Brief  : Unit tests for Paddle class
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gtest/gtest.h"
#include "paddle.h"

class PaddleTest : public ::testing::Test 
{
public:
	void setupPaddleForGetCornerTest();

	Paddle paddle;
};


/* Corner Getters ------------------------------------------------------------*/
/* Helper Function */
void PaddleTest::setupPaddleForGetCornerTest()
{
	int x_pos = 10;
	int y_pos = 20;

	paddle.setTopLeftCornerPosition(x_pos, y_pos);
}

/* Top Left Corner */
TEST_F(PaddleTest, Can_Get_Top_Left_Corner_Position)
{
	/* Arrange */
	setupPaddleForGetCornerTest();
	const int expected_x = 10;
	const int expected_y = 20;
	
	/* Act */
	Paddle::Position actual_position = paddle.getTopLeftCornerPosition();

	/* Assert */
	EXPECT_EQ(expected_x, actual_position.x);
	EXPECT_EQ(expected_y, actual_position.y);

}

/* Top Right Corner */
TEST_F(PaddleTest, Can_Get_Top_Right_Corner_Position)
{
	/* Arrange */
	setupPaddleForGetCornerTest();
	Paddle::Position paddlePosition = paddle.getTopLeftCornerPosition();
	const int expected_x = paddlePosition.x + paddle.getDimensions().width;
	const int expected_y = paddlePosition.y;

	/* Act */
	Paddle::Position actual_position = paddle.getTopRightCornerPosition();

	/* Assert */
	EXPECT_EQ(expected_x, actual_position.x);
	EXPECT_EQ(expected_y, actual_position.y);
}

/* Bottom Left Corner */
TEST_F(PaddleTest, Can_Get_Bottom_Left_Corner_Position)
{
	/* Arrange */
	setupPaddleForGetCornerTest();
	Paddle::Position paddlePosition = paddle.getTopLeftCornerPosition();
	const int expected_x = paddlePosition.x;
	const int expected_y = paddlePosition.y + paddle.getDimensions().heigth;

	/* Act */
	Paddle::Position actual_position = paddle.getBottomLeftCornerPosition();	

	/* Assert */
	EXPECT_EQ(expected_x, actual_position.x);
	EXPECT_EQ(expected_y, actual_position.y);
}

/* Bottom Right Corner */
TEST_F(PaddleTest, Can_Get_Bottom_Right_Corner_Position)
{
	/* Arrange */
	setupPaddleForGetCornerTest();
	Paddle::Position paddlePosition = paddle.getTopLeftCornerPosition();
	const int expected_x = paddlePosition.x + paddle.getDimensions().width;
	const int expected_y = paddlePosition.y + paddle.getDimensions().heigth;

	/* Act */
	Paddle::Position actual_position = paddle.getBottomRightCornerPosition();

	/* Assert */
	EXPECT_EQ(expected_x, actual_position.x);
	EXPECT_EQ(expected_y, actual_position.y);
}