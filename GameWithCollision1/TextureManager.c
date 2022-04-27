#include "TextureManager.h"
#include "Camera.h"

SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	return tex;
}

void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &src, &dest);
}