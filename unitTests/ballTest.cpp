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
	void setupPaddleAsSquareForCollisionTests();

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


/* Getters -------------------------------------------------------------------*/
TEST_F(BallTest, Can_Get_Position_Of_Ball_Center)
{
	/* Arrange*/
	const int size = 10;
	const int pos_x = 20;
	const int pos_y = 30;

	ball.setSize(size);
	ball.setTopLeftCornerPosition(pos_x, pos_y);

	/* Act */
	Ball::Position centerPosition = ball.getPositionOfCenter();

	/* Assert */
	const int expected_x = pos_x + size/2;
	const int expected_y = pos_y + size/2;
	EXPECT_EQ(expected_x, centerPosition.x);
	EXPECT_EQ(expected_y, centerPosition.y);
}

TEST_F(BallTest, Can_Get_Position_Of_Right_Corner)
{
	/* Arrange */
	const int size = 10;
	const int pos_x = 20;
	const int pos_y = 30;

	ball.setSize(size);
	ball.setTopLeftCornerPosition(pos_x, pos_y);

	/* Act */
	Ball::Position cornerPosition = ball.getBottomRightCornerPosition();

	/* Assert */
	const int expected_x = pos_x + size;
	const int expected_y = pos_y + size;
	EXPECT_EQ(expected_x, cornerPosition.x);
	EXPECT_EQ(expected_y, cornerPosition.y);

}


/* Round setup ---------------------------------------------------------------*/
TEST_F(BallTest, Served_Ball_Starts_In_Middle_Of_Pong_Table)
{
	/* Arrange */
	const int ballSize = 10;
	const int tableSideLength = 100;
	PongTable pongTable(tableSideLength, tableSideLength);
	ball.setSize(ballSize);

	/* Act */
	ball.setupServe(Ball::ServingPlayer::One, pongTable);
	
	/* Assert */
	/* The middle of the table is found at half the side lengths. To get the 
	 * ball centered in the middle, and not a little off of the right, we nudge 
	 * the upper left corner from the center by half the ball's size. */
	int expected_x = (tableSideLength / 2);
	int expected_y = (tableSideLength / 2);

	Ball::Position actualCenterPosition = ball.getPositionOfCenter();
	EXPECT_EQ(expected_x, actualCenterPosition.x);
	EXPECT_EQ(expected_y, actualCenterPosition.y);
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
	
	ball.setTopLeftCornerPosition(initialPos, initialPos);
	ball.setSpeed(dx, 0);

	/* Act */
	ball.update();

	/* Assert */
	EXPECT_EQ(initialPos + dx, ball.getTopLeftCornerPosition().x);
}

TEST_F(BallTest, Vertical_Speed_Of_One_Moves_Ball_One_Pixel_During_Update)
{
	/* Arrange */
	const int initialPos = 10;
	const int dy = 1;

	ball.setTopLeftCornerPosition(initialPos, initialPos);
	ball.setSpeed(0, dy);

	/* Act */
	ball.update();

	/* Assert */
	EXPECT_EQ(initialPos + dy, ball.getTopLeftCornerPosition().y);
}


/* Detect overlap tests ------------------------------------------------------*/
/* We first test that we can detect that the ball is overlapping with a paddle, 
 * so that we later can test mechanisms for avoiding overlaps.*/

/* Helper function, make sure paddle is consistent throughout all tests */
void BallTest::setupPaddleAsSquareForCollisionTests()
{
	int paddle_x = 2;
	int paddle_y = 2;
	int paddleHeigth = 4;
	int paddleWidth = 4;

	paddle.setTopLeftCornerPosition(paddle_x, paddle_y);
	paddle.setDimensions(paddleHeigth, paddleWidth);
}

/* If we imagine two lines extending vertically from the left and right side of  
 * the paddle, we check that the ball can detect that it is within those lines.
 * Note: Horizontal movement is bounded by vertical lines! */
TEST_F(BallTest, Detects_Is_Within_Paddle_Horizontal_Bounds)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = paddle.getTopLeftCornerPosition().x + ballSize/2;
	const int ball_y = 0; // don't care about vertical position 
	ball.setTopLeftCornerPosition(ball_x, ball_y);

	/* Act */
	bool actual_answer = ball.isWithinHorizontalBounds(paddle);

	/* Assert */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_Is_Outside_Of_Paddle_Horizontal_Bounds)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = -10; // negative guarantees we're out of bounds
	const int ball_y = 0; // don't care about vertical position 
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isWithinHorizontalBounds(paddle);

	/* Assert */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}


/* If we imagine two lines extending horizontally from the top and bottom side
 * of the paddle, we check that the ball can detect that it is within those 
 * lines. Note: Vertical movement is bounded by horizontal lines! */
TEST_F(BallTest, Detects_Is_Within_Paddle_Vertical_Bounds)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = 0; // don't care about horizontal position
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isWithinVerticalBounds(paddle);

	/* Assert */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}