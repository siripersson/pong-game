/*
 *******************************************************************************
 * File   : main.cpp
 * Date   : 18 Jun 2018
 * Author : Rasmus Källqvist & Siri Persson @ Sylog Sverige AB
 * Brief  : Main program for Pong game, creates a game-runner object and 
 *          starts the game.
 *******************************************************************************
 */

#include "pong.h"

int main(int argc, char* argv[])
{
    Pong pong(argc, argv);
    pong.execute();
    return 0;
}