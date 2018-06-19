/*
 *******************************************************************************
 * File   : allTests.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus @ Sylog Sverige AB
 * Brief  : Unit test runner for all tests in Pong-game project
 *******************************************************************************
 */

#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}