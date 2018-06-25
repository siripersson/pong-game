/*
 *******************************************************************************
 * File   : pong.h
 * Date   : 18 Jun 2018
 * Author : Siri Persson @ Sylog Sverige AB
 * Brief  : Header file for the pong game-runner class
 *******************************************************************************
 */
#pragma once

#include <SDL.h>
#include<string>
#include <map>

class Paddle;

class Keyboard
{
private:
	Paddle* leftPaddle;
	Paddle* rightPaddle;
public:
	Keyboard(){};
	~Keyboard() {}

	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;

	std::map<std::string, std::string> keyStates;

	void handleKeyboardEvent(SDL_Event event);
	bool isPressed(std::string keycode);
	bool checkIfPressedQuit(SDL_Event event);

};


