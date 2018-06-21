#include "gtest/gtest.h"
#include "keyboard.h"

class KeyBoardTest : public ::testing::Test
{
public:
	Keyboard keyboard;
};

/* Unit test example */
TEST_F(KeyboardTest, Two_Simultaneous_Key_Presses)
{
	/* Setup */
	bool expected_keypress1 = 1;
	bool expected_keypress2 = 1;


	bool actual_keypress1 = keyboard.handleKeyboardEvent()

	/* Check */
	EXPECT_EQ(actual_keypress1, expected_keypress1);
	EXPECT_EQ(actual_keypress2, expected_keypress2);
}
