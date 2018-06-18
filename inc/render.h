#pragma once

#include <SDL.h>

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* clip=nullptr);

void renderTexture(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip=nullptr);
