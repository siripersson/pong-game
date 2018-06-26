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
	Paddle paddle2;
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
TEST_F(BallTest, Can_Get_Position_Of_Top_Right_Corner)
{
	/* Arrange */
	const int size = 10;
	const int pos_x = 20;
	const int pos_y = 30;

	ball.setSize(size);
	ball.setTopLeftCornerPosition(pos_x, pos_y);

	/* Act */
	Ball::Position cornerPosition = ball.getTopRightCornerPosition();

	/* Assert */
	const int expected_x = pos_x + size;
	const int expected_y = pos_y;
	EXPECT_EQ(expected_x, cornerPosition.x);
	EXPECT_EQ(expected_y, cornerPosition.y);
}

TEST_F(BallTest, Can_Get_Position_Of_Bottom_Left_Corner)
{
	/* Arrange */
	const int size = 10;
	const int pos_x = 20;
	const int pos_y = 30;

	ball.setSize(size);
	ball.setTopLeftCornerPosition(pos_x, pos_y);

	/* Act */
	Ball::Position cornerPosition = ball.getBottomLeftCornerPosition();

	/* Assert */
	const int expected_x = pos_x;
	const int expected_y = pos_y + size;
	EXPECT_EQ(expected_x, cornerPosition.x);
	EXPECT_EQ(expected_y, cornerPosition.y);
}

TEST_F(BallTest, Can_Get_Position_Of_Bottom_Right_Corner)
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



/* Setters -------------------------------------------------------------------*/
TEST_F(BallTest, Can_Set_Position_Of_Top_Right_Corner)
{
	/* Arrange */
	Ball ball(0, 0);
	const int size = 10;
	const int pos_x = 20;
	const int pos_y = 30;
	ball.setSize(size);

	/* Act */
	ball.setTopRightCornerPosition(pos_x, pos_y);

	/* Assert */
	Ball::Position cornerPosition = ball.getTopRightCornerPosition();
	const int expected_x = ball.getTopLeftCornerPosition().x + size;
	const int expected_y = ball.getTopLeftCornerPosition().y;
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
	const int initialPos = 100;
	const int dx = -1;
	
	ball.setTopLeftCornerPosition(initialPos, initialPos);
	ball.setSpeed(dx, 0);

	/* Act */
	ball.update(paddle, paddle, pongTable);

	/* Assert */
	EXPECT_EQ(initialPos + dx, ball.getTopLeftCornerPosition().x);
}

TEST_F(BallTest, Vertical_Speed_Of_One_Moves_Ball_One_Pixel_During_Update)
{
	/* Arrange */
	const int initialPos = 100;
	const int dy = 1;

	ball.setTopLeftCornerPosition(initialPos, initialPos);
	ball.setSpeed(0, dy);

	/* Act */
	ball.update(paddle, paddle, pongTable);

	/* Assert */
	EXPECT_EQ(initialPos + dy, ball.getTopLeftCornerPosition().y);
}



/* Detect overlap tests ------------------------------------------------------*/
/* We first test that we can detect that the ball is overlapping with a paddle, 
 * so that we later can test mechanisms for avoiding overlaps.*/

/* Helper function, make sure paddle is consistent throughout all tests. We
 * set the paddle to a square with side lengths 4, to make it somewhat easier 
 * to calculate coordinates for a ball of size 2 at various positions around 
 * the padel. */
void BallTest::setupPaddleAsSquareForCollisionTests()
{
	int paddle_x = 2;
	int paddle_y = 2;
	int paddleHeigth = 4;
	int paddleWidth = 4;

	paddle.setTopLeftCornerPosition(paddle_x, paddle_y);
	paddle.setDimensions(paddleHeigth, paddleWidth);

	// move paddle 2 out of the way
	int paddle2_x = 1002;
	int paddle2_y = 1002;

	paddle2.setTopLeftCornerPosition(paddle2_x, paddle2_y);
	paddle2.setDimensions(paddleHeigth, paddleWidth);	
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

TEST_F(BallTest, Detects_Is_Outside_Of_Paddle_Vertical_Bounds)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = 0; // don't care about horizontal position
	const int ball_y = -10; // negative guarantees we're out of bounds
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isWithinVerticalBounds(paddle);

	/* Assert */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_No_Overlap_When_Placed_In_Negative_Coordinates)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = -10; // negative guarantees we're out of bounds
	const int ball_y = -10;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isOverlappingPaddle(paddle);

	/* Assert */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_No_Overlap_When_Adjacent_To_The_Left)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	// place ball adjacent to the middle of the paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - ballSize;
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actualOverlapping = ball.isOverlappingPaddle(paddle);

	/* Assert */
	bool expectedOverlapping = false;
	EXPECT_EQ(expectedOverlapping, actualOverlapping);	
}

TEST_F(BallTest, Detects_Is_Overlapping_Right_Side_Of_Paddle)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = paddle.getTopRightCornerPosition().x - ballSize/2;
	const int ball_y = paddle.getTopRightCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isOverlappingPaddle(paddle);

	/* Assert */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_Is_Overlapping_Top_Side_Of_Paddle)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = paddle.getTopLeftCornerPosition().x + ballSize/2;
	const int ball_y = paddle.getTopLeftCornerPosition().y - ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isOverlappingPaddle(paddle);

	/* Assert */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_Is_Overlapping_Left_Side_Of_Paddle)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = paddle.getTopLeftCornerPosition().x - ballSize/2;
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isOverlappingPaddle(paddle);

	/* Assert */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_Is_Overlapping_Bottom_Side_Of_Paddle)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	const int ball_x = paddle.getBottomLeftCornerPosition().x + ballSize/2;
	const int ball_y = paddle.getBottomLeftCornerPosition().y - ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	ball.setSize(ballSize);

	/* Act */
	bool actual_answer = ball.isOverlappingPaddle(paddle);

	/* Assert */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}



/* Horizontal collision detection --------------------------------------------*/
TEST_F(BallTest, Detects_Collision_When_Adjacent_And_Horizontal_Speed_Is_One)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to the middle of the paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - ballSize;
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// horizontal speed is 1 unit to the right 
	const int speed = 1;
	const int ball_dx = speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapHorizontallyWith(paddle);

	/* Asset */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, Detects_Collision_When_Adjacent_And_Horizontal_Speed_Is_Ten)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to the middle of the paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - ballSize;
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// horizontal speed is 10 units to the right 
	const int speed = 10;
	const int ball_dx = speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapHorizontallyWith(paddle);

	/* Asset */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, No_Collision_When_Path_Is_Clear_And_Horizontal_Speed_Is_One)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to the middle of the paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - ballSize;
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// horizontal speed is 1 unit to the left
	const int speed = 1;
	const int ball_dx = -speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapHorizontallyWith(paddle);

	/* Asset */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, No_Collision_When_Path_Is_Clear_And_Horizontal_Speed_Is_Ten)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to the middle of the paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - ballSize;
	const int ball_y = paddle.getTopLeftCornerPosition().y + ballSize/2;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// horizontal speed is 1 unit to the left
	const int speed = 10;
	const int ball_dx = -speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapHorizontallyWith(paddle);

	/* Asset */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}



/* Vertical collision detection ----------------------------------------------*/
TEST_F(BallTest, Detects_Collision_Vertically_To_The_Right)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to the middle of the paddle's bottom side 
	const int ball_x = paddle.getBottomLeftCornerPosition().x + ballSize/2;
	const int ball_y = paddle.getBottomLeftCornerPosition().y - 1;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves upward
	const int speed = 10;
	const int ball_dx = 0;
	const int ball_dy = -speed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapVerticallyWith(paddle);

	/* Asset */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, No_Collision_When_Path_Is_Clear_To_The_Left)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to the middle of the paddle's bottom side 
	const int ball_x = paddle.getBottomLeftCornerPosition().x + ballSize/2;
	const int ball_y = paddle.getBottomLeftCornerPosition().y - 1;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves downward
	const int speed = 10;
	const int ball_dx = 0;
	const int ball_dy = speed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapVerticallyWith(paddle);

	/* Asset */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}



/* Diagonal collision detection ----------------------------------------------*/
TEST_F(BallTest, Detects_Collision_Diagonally_Up_To_The_Right)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to lower left corner of paddle 
	const int ball_x = paddle.getBottomLeftCornerPosition().x;
	const int ball_y = paddle.getBottomLeftCornerPosition().y;
	ball.setTopRightCornerPosition(ball_x, ball_y);
	// ball moves diagonally to the right
	const int speed = 10;
	const int ball_dx = speed;
	const int ball_dy = -speed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapDiagonallyWith(paddle);

	/* Asset */
	bool expected_answer = true;
	EXPECT_EQ(expected_answer, actual_answer);
}

TEST_F(BallTest, No_Collision_When_Path_Is_Clear_Diagonally_To_The_Right)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball adjacent to lower left corner of paddle 
	const int ball_x = paddle.getBottomLeftCornerPosition().x;
	const int ball_y = paddle.getBottomLeftCornerPosition().y;
	ball.setTopRightCornerPosition(ball_x, ball_y);
	// ball moves diagonally to the left
	const int speed = 10;
	const int ball_dx = -speed;
	const int ball_dy = speed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	bool actual_answer = ball.wouldOverlapDiagonallyWith(paddle);

	/* Asset */
	bool expected_answer = false;
	EXPECT_EQ(expected_answer, actual_answer);
}


/* Collision aware movement --------------------------------------------------*/
TEST_F(BallTest, Move_To_The_Right_Stops_When_Adjacent_To_Paddle_Left_Side)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball's right side with a one step gap to paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - 1;
	const int ball_y = paddle.getTopLeftCornerPosition().y;
	ball.setTopRightCornerPosition(ball_x, ball_y);
	// ball moves to the right
	const int speed = 10;
	const int ball_dx = speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_x = ball.getTopRightCornerPosition().x;
	const int actual_y = ball.getTopRightCornerPosition().y;
	const int expected_x = paddle.getTopLeftCornerPosition().x;
	const int expected_y = paddle.getTopLeftCornerPosition().y;
	EXPECT_EQ(expected_x, actual_x);
	EXPECT_EQ(expected_y, actual_y);
}

TEST_F(BallTest, Move_To_The_Left_Stops_When_Adjacent_To_Paddle_Right_Side)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball's left side with a one step gap to paddle's right side
	const int ball_x = paddle.getTopRightCornerPosition().x + 1;
	const int ball_y = paddle.getTopRightCornerPosition().y;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves to the left
	const int speed = 10;
	const int ball_dx = -speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_x = ball.getTopLeftCornerPosition().x;
	const int actual_y = ball.getTopLeftCornerPosition().y;
	const int expected_x = paddle.getTopRightCornerPosition().x;
	const int expected_y = paddle.getTopRightCornerPosition().y;
	EXPECT_EQ(expected_x, actual_x);
	EXPECT_EQ(expected_y, actual_y);
}

TEST_F(BallTest, Move_Upwards_Stops_When_Adjacent_To_Paddle_Bottom)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball underneath padel's bottom left corner 
	const int ball_x = paddle.getBottomLeftCornerPosition().x;
	const int ball_y = paddle.getBottomLeftCornerPosition().y + 1;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves to the right
	const int speed = 10;
	const int ball_dx = 0;
	const int ball_dy = -speed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_x = ball.getTopLeftCornerPosition().x;
	const int actual_y = ball.getTopLeftCornerPosition().y;
	const int expected_x = paddle.getBottomLeftCornerPosition().x;
	const int expected_y = paddle.getBottomLeftCornerPosition().y;
	EXPECT_EQ(expected_x, actual_x);
	EXPECT_EQ(expected_y, actual_y);
}

TEST_F(BallTest, Moves_Diagonally_Up_Until_Adjacent_To_Corner)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball on step away from paddle's bottom left corner
	const int ball_x = paddle.getBottomLeftCornerPosition().x - 1;
	const int ball_y = paddle.getBottomLeftCornerPosition().y + 1;
	ball.setTopRightCornerPosition(ball_x, ball_y);
	// ball moves diagonally up to the right
	const int speed = 10;
	const int ball_dx = speed;
	const int ball_dy = -speed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_x = ball.getTopRightCornerPosition().x;
	const int actual_y = ball.getTopRightCornerPosition().y;
	const int expected_x = paddle.getBottomLeftCornerPosition().x;
	const int expected_y = paddle.getBottomLeftCornerPosition().y;
	EXPECT_EQ(expected_x, actual_x);
	EXPECT_EQ(expected_y, actual_y);
}

TEST_F(BallTest, Moves_Full_Speed_If_No_Paddle_To_The_Right)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball on the right side of the paddle 
	const int ball_x = paddle.getTopRightCornerPosition().x + 1;
	const int ball_y = paddle.getTopRightCornerPosition().y;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves to the right
	const int speed = 10;
	const int ball_dx = speed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_x = ball.getTopLeftCornerPosition().x;
	const int actual_y = ball.getTopLeftCornerPosition().y;
	const int expected_x = paddle.getTopRightCornerPosition().x + 1 + speed;
	const int expected_y = paddle.getTopRightCornerPosition().y;
	EXPECT_EQ(expected_x, actual_x);
	EXPECT_EQ(expected_y, actual_y);
}

TEST_F(BallTest, Horizontal_Collision_Causes_Horizontal_Speed_To_Change_Sign)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball's right side with a one step gap to paddle's left side
	const int ball_x = paddle.getTopLeftCornerPosition().x - 1;
	const int ball_y = paddle.getTopLeftCornerPosition().y;
	ball.setTopRightCornerPosition(ball_x, ball_y);
	// ball moves to the right
	const int initialSpeed = 10;
	const int ball_dx = initialSpeed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_speed = ball.getSpeed().dx;
	const int expected_speed = -initialSpeed;
	EXPECT_EQ(expected_speed, actual_speed);
}

TEST_F(BallTest, Vertical_Collision_Causes_Vertical_Speed_To_Change_Sign)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball's top side with a one step gap to paddle's bottom side
	const int ball_x = paddle.getBottomLeftCornerPosition().x;
	const int ball_y = paddle.getBottomLeftCornerPosition().y + 1;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves up
	const int initialSpeed = -10;
	const int ball_dx = 0;
	const int ball_dy = initialSpeed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_speed = ball.getSpeed().dy;
	const int expected_speed = -(initialSpeed);
	EXPECT_EQ(expected_speed, actual_speed);
}

TEST_F(BallTest, No_Horizontal_Collision_Causes_Horizontal_Speed_To_Remain_Same)
{
	/* Arrange */
	setupPaddleAsSquareForCollisionTests();
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball's left side to the right of the paddle
	const int ball_x = paddle.getTopRightCornerPosition().x + 1;
	const int ball_y = paddle.getTopRightCornerPosition().y;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves to the right
	const int initialSpeed = 10;
	const int ball_dx = initialSpeed;
	const int ball_dy = 0;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_speed = ball.getSpeed().dx;
	const int expected_speed = +initialSpeed;
	EXPECT_EQ(expected_speed, actual_speed);
}

TEST_F(BallTest, No_Vertical_Collision_Causes_Vertical_Speed_To_Remain_Same)
{
	/* Arrange */
	const int paddle_x = 50;
	const int paddle_y = 50;
	paddle.setTopLeftCornerPosition(paddle_x, paddle_y);
	const int ballSize = 2;
	ball.setSize(ballSize);
	// place ball's top side to the bottom of the paddle
	const int ball_x = paddle.getBottomRightCornerPosition().x;
	const int ball_y = paddle.getBottomRightCornerPosition().y + 1;
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves to the right
	const int initialSpeed = -10;
	const int ball_dx = 0;
	const int ball_dy = initialSpeed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);

	/* Assert */
	const int actual_speed = ball.getSpeed().dy;
	const int expected_speed = +initialSpeed;
	EXPECT_EQ(expected_speed, actual_speed);
}

TEST_F(BallTest, Collision_With_Upper_Pong_Table_Edge_Inverts_Vertical_Speed)
{
	/* Arrange */
	// move paddles out of the way
	paddle.setTopLeftCornerPosition(-100, -100);
	paddle2.setTopLeftCornerPosition(-100, -100);
	const int table_width = 100;
	const int table_heigth = 100;
	PongTable pongTable(table_width, table_heigth);
	// place ball one step away from table upper boundry
	const int ball_x = 0;
	const int ball_y = 1; 
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves upwards
	const int initialSpeed = -10;
	const int ball_dx = 0;
	const int ball_dy = initialSpeed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);	

	/* Assert */
	const int actual_speed = ball.getSpeed().dy;
	const int expected_speed = -initialSpeed;
	EXPECT_EQ(expected_speed, actual_speed);	
}

TEST_F(BallTest, Collision_With_Lower_Pong_Table_Edge_Inverts_Vertical_Speed)
{
	/* Arrange */
	// move paddles out of the way
	paddle.setTopLeftCornerPosition(-100, -100);
	paddle2.setTopLeftCornerPosition(-100, -100);
	const int table_width = 100;
	const int table_heigth = 100;
	PongTable pongTable(table_width, table_heigth);
	// place ball one step away from table upper boundry
	const int ball_x = 0;
	const int ball_y = table_heigth - 5; 
	ball.setTopLeftCornerPosition(ball_x, ball_y);
	// ball moves upwards
	const int initialSpeed = 10;
	const int ball_dx = 0;
	const int ball_dy = initialSpeed;
	ball.setSpeed(ball_dx, ball_dy);

	/* Act */
	ball.executeMovementForThisFrame(paddle, paddle2, pongTable);	

	/* Assert */
	const int actual_speed = ball.getSpeed().dy;
	const int expected_speed = -initialSpeed;
	EXPECT_EQ(expected_speed, actual_speed);	
}