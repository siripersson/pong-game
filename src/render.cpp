#include "render.h"
#include <SDL.h>

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rectangle, SDL_Rect* clip){
	SDL_RenderCopy(renderer, texture, clip, &rectangle);
}

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;

	renderTexture(texture, renderer, rectangle, clip);
}

