//============================================================================
// Name        : Pong game
// Author      : Siri and Rasmus
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SDL.h>

int main(int argc, char* argv[]) {
    // Start SDL2
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a Window in the middle of the screen
    SDL_Window *window = 0;

    window = SDL_CreateWindow("Hello World!",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              640, 480,
                              SDL_WINDOW_SHOWN);

    // Delay so that we can see the window appear
    SDL_Delay(3000);

    // Cleanup and Quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
