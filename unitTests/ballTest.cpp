/*
 *******************************************************************************
 * File   : ballTest.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus & Siri Persson @ Sylog Sverige AB
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
	EXPECT_LT(ball.getMovement().dx, 0);
}

TEST_F(BallTest, When_Player_Two_Serves_Ball_Moves_Right)
{
	ball.setupServe(Ball::ServingPlayer::Two, pongTable);

	/* If dx is negative, the ball is moving towards the left*/
	EXPECT_GT(ball.getMovement().dx, 0);
}


/* Ongoing round -------------------------------------------------------------*/
TEST_F(BallTest, Horizontal_Speed_Of_One_Moves_Ball_One_Pixel_During_Update)
{
	/* Arrange */
	const int initialPos = 10;
	const int dx = -1;
	
	ball.setPosition(initialPos, initialPos);
	ball.setMovement(dx, 0);

	/* Act */
	ball.updatePosition();

	/* Assert */
	EXPECT_EQ(initialPos + dx, ball.getPosition().x);
}

TEST_F(BallTest, Vertical_Speed_Of_One_Moves_Ball_One_Pixel_During_Update)
{
	/* Arrange */
	const int initialPos = 10;
	const int dy = 1;

	ball.setPosition(initialPos, initialPos);
	ball.setMovement(0, dy);

	/* Act */
	ball.updatePosition();

	/* Assert */
	EXPECT_EQ(initialPos + dy, ball.getPosition().y);
}

TEST_F(BallTest, Wall_Collision_Returns_True_If_Ball_Reaches_Lower_Border)
{
	/* Arrange */
	bool expectedValue= true;

	/* Act */
	ball.setPosition(40, pongTable.getHeight()- ball.getSize() -2);
	ball.setMovement(0, 2);

	bool actualValue = ball.wallCollision();

	/* Assert */
	EXPECT_EQ(actualValue, expectedValue);
}

TEST_F(BallTest, Wall_Collision_Returns_True_If_Ball_Reaches_Upper_Border)
{
	/* Arrange */
	bool expectedValue= true;

	/* Act */
	ball.setPosition(40, 1);
	ball.setMovement(0, -2);

	bool actualValue = ball.wallCollision();

	/* Assert */
	EXPECT_EQ(actualValue, expectedValue);
}

TEST_F(BallTest, Wall_Collision_Returns_False_If_Ball_Not_At_Border)
{
	/* Arrange */
	bool expectedValue= false;

	/* Act */
	ball.setPosition(40, 40);
	ball.setSpeed(2);

	bool actualValue = ball.wallCollision();

	/* Assert */
	EXPECT_EQ(actualValue, expectedValue);
}

TEST_F(BallTest, Collides_With_Paddle_Returns_True_If_Ball_Hits_Paddle)
{
	/* Arrange */
	bool expectedValue= true;

	/* Act */
	ball.setPosition(40, 40);
	ball.setSpeed(2);

	// Placera paddle på en speciell position
	paddle.setPosition(40,40);

	bool actualValue = ball.collidesWith(paddle);

	/* Assert */
	EXPECT_EQ(actualValue, expectedValue);
}

TEST_F(BallTest, Collides_With_Paddle_Returns_False_If_Ball_Does_Not_Hit_Paddle)
{
	/* Arrange */
	bool expectedValue= false;

	/* Act */
	ball.setPosition(40, 40);
	ball.setSpeed(2);
	paddle.setPosition(200,200);

	bool actualValue = ball.collidesWith(paddle);

	/* Assert */
	EXPECT_EQ(actualValue, expectedValue);
}







