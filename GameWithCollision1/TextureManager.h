#include "Game.h"
#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER
SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer);
#endif