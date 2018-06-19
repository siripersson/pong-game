/*
 *******************************************************************************
 * File   : pong.h
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Header file for the pong game-runner class
 *******************************************************************************
 */

#pragma once

/* Includes ------------------------------------------------------------------*/
#include "ball.h"
#include "paddle.h"
#include "render.h"
#include <SDL.h>

/* Class declarations --------------------------------------------------------*/
class Ball;
class Paddle;
class Pong 
{
private:
   /* SDL entities */
   SDL_Window *window;
   SDL_Renderer *renderer;

   /* Timing */

   
   /* Game actors */
   Ball* ball;
   Paddle* left_paddle;
   Paddle* right_paddle;

public:
   static const int SCREEN_WIDTH = 640;
   static const int SCREEN_HEIGHT = 480;

   Pong(int argc, char *argv[]);
   ~Pong();

   /* Game running functions */
   void execute();
   void input();
   void update();
   void render();
};
