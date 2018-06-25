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
	void setupPaddleForCollisionTests();

	Ball ball;
	Paddle paddle;
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

	/* The middle of the table is found at half the side lengths. To get the 
	 * ball centered in the middle, and not a little off of the right, we nudge 
	 * the upper left corner from the center by half the ball's size. */
	int expected_x = (tableSideLength / 2) - (ballSize / 2);
	int expected_y = (tableSideLength / 2) - (ballSize / 2);

	/* Act */
	ball.setupServe(Ball::ServingPlayer::One, pongTable);
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


/* Ball movement -------------------------------------------------------------*/
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


/* Collision detection -------------------------------------------------------*/
/* Helper function, make sure paddle is consistent throughout all tests */
void BallTest::setupPaddleForCollisionTests()
{
	int paddle_x = 2;
	int paddle_y = 2;
	int paddle_heigth = 4;
	int paddle_width = 4;

	paddle.setPosition(paddle_x, paddle_y);
	paddle.setDimensions(paddle_heigth, paddle_width);
}

/* We first test that we can detect that the ball is overlapping with a paddle, 
 * so that we later can test mechanisms for avoiding overlaps.*/
TEST_F(BallTest, Detects_Overlap_With_Lower_Right_Corner_Of_Paddle)
{
	/* Arrange */
	setupPaddleForCollisionTests();

	int ball_size = 2;
	int ball_x  = paddle.getRightCornerPosition().x - (ball_size / 2);
	int ball_y  = paddle.getRightCornerPosition().y - (ball_size / 2);
	Ball ball(ball_x, ball_y, ball_size);

	/* Act */
	bool actual_overlap = ball.isOverlappingPaddle(paddle);

	/* Assert */
	EXPECT_EQ(true, actual_overlap);
}

TEST_F(BallTest, Detects_No_Overlap_With_Lower_Right_Corner_Of_Paddle)
{
	/* Arrange */
	setupPaddleForCollisionTests();

	int ball_size = 2;
	int ball_x  = paddle.getRightCornerPosition().x;
	int ball_y  = paddle.getRightCornerPosition().y;
	Ball ball(ball_x, ball_y, ball_size);

	/* Act */
	bool actual_overlap = ball.isOverlappingPaddle(paddle);

	/* Assert */
	EXPECT_EQ(false, actual_overlap);
}