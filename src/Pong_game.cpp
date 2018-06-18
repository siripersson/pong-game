//============================================================================
// Name        : Pong game
// Author      : Siri and Rasmus
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
	 SDL_Window *window = NULL;
	 SDL_Renderer *renderer;

    // Start SDL2
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a Window in the middle of the screen
    window = SDL_CreateWindow("Pong game",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Set render color to
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    // Clear window
    SDL_RenderClear( renderer );

    // #############################################################################################################
    // Ball
    // #############################################################################################################

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect ball;
    ball.w = 10;
    ball.h = 10;
    ball.x = SCREEN_WIDTH/2 - ball.w/2;
    ball.y = SCREEN_HEIGHT/2;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    // Render rect
    SDL_RenderFillRect( renderer, &ball );


    // ##############################################################################################################
    // Paddle 1
    // ##############################################################################################################

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
       SDL_Rect paddle;
       paddle.w = 10;
       paddle.h = 70;
       paddle.x = SCREEN_WIDTH - (40 + paddle.w);
       paddle.y = SCREEN_HEIGHT/2 - paddle.h/2;

       // Set render color to blue ( rect will be rendered in this color )
       SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

       // Render rect
       SDL_RenderFillRect( renderer, &paddle );


       // ##############################################################################################################
       // Paddle 2
       // ##############################################################################################################

       // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
       SDL_Rect paddle2;
       paddle2.w = 10;
       paddle2.h = 70;
       paddle2.x = paddle2.w*2;
       paddle2.y = SCREEN_HEIGHT/2 - paddle2.h/2;


       // Set render color to blue ( rect will be rendered in this color )
       SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

       // Render rect
      SDL_RenderFillRect( renderer, &paddle2 );

       // Render the rect to the screen
       SDL_RenderPresent(renderer);



    // Delay so that we can see the window appear
    SDL_Delay(3000);

    // Cleanup and Quit
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
