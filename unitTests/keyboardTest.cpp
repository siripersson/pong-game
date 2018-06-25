#include "gtest/gtest.h"
#include "keyboard.h"

class KeyboardTest : public ::testing::Test
{
public:
	Keyboard keyboard;

	void generateSDLUpKeyPress (){
		SDL_Event event;
		event.type = SDL_KEYDOWN;
		event.key.keysym.sym = SDLK_UP;
		keyboard.handleKeyboardEvent(event);

	}
};

/* Unit test example */
TEST_F(KeyboardTest, Keystate_Is_Set_To_Pressed_If_Key_Is_Pressed)
{
	/* Arrange */
	std::string expectedKeystate = "PRESSED";

	/* Act */
	generateSDLUpKeyPress();

	std::string actualKeystate = keyboard.keyStates["SDLK_UP"];

	/* Assert */
	EXPECT_EQ(actualKeystate, expectedKeystate);
}

TEST_F(KeyboardTest, Function_IsPressed_Returns_True_If_Key_Is_Pressed)
{
	bool expectedIsPressed = true;
	generateSDLUpKeyPress();
	bool actualIsPressed = keyboard.isPressed("SDLK_UP");

	/* Assert */
	EXPECT_EQ(actualIsPressed, expectedIsPressed);
}

