#include "TextureManager.h"
#include "GameObject.h"

const int DELAY = 10;

game_Object_t Game_Object_create(const char* texturesheet, SDL_Renderer* renderer, double x, double y) {
	game_Object_t gameObject;
	gameObject.renderer = renderer;
	gameObject.objTexture = LoadTexture(texturesheet, renderer);
	gameObject.xpos = x;
	gameObject.initialxpos = x;
	gameObject.ypos = y;
	gameObject.initialypos = y;
	gameObject.Collider.x = x ; 
	gameObject.Collider.y = y ;
	gameObject.animationCount = 0;
	gameObject.delay = DELAY;
	gameObject.frames = 0;
	gameObject.collides = 0;
	return gameObject;
}

void Game_Object_destroy(game_Object_t* gameObject) {

}

void UpdateEnvironmentObjects(game_Object_t *gameObject, tile_map_t tilemap) {
	gameObject->xpos = gameObject->initialxpos + tilemap.xpos;
	gameObject->ypos = gameObject->initialypos + tilemap.ypos;
}

void RenderObject(game_Object_t *gameObject, int width, int height, double x, double y, double scaleW, double scaleH, camera_t* camera) {
	gameObject->srcRect.w = width;
	gameObject->srcRect.h = height;
	gameObject->srcRect.x = x;
	gameObject->srcRect.y = y;
	gameObject->AnimationState = idle;
	gameObject->Collider.w = width / 2;
	gameObject->Collider.h = height/ 2;
	if (camera != NULL) {
		gameObject->destRect.x = gameObject->xpos - camera->viewport.x;
		gameObject->destRect.y = gameObject->ypos - camera->viewport.y;
	}
	else {
		gameObject->destRect.x = gameObject->xpos;
		gameObject->destRect.y = gameObject->ypos;
	}
	
	gameObject->destRect.w = (int)(gameObject->srcRect.w * scaleW);
	gameObject->destRect.h = (int)(gameObject->srcRect.h * scaleH);
	SDL_RenderCopy(gameObject->renderer, gameObject->objTexture, &gameObject->srcRect, &gameObject->destRect);
}

int checkCollision(SDL_Rect a, SDL_Rect b) {
	//Code from https://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
	//The sides of the rectangles
	double leftA, leftB;
	double rightA, rightB;
	double topA, topB;
	double bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return 0;
	}

	if (topA >= bottomB)
	{
		return 0;
	}

	if (rightA <= leftB)
	{
		return 0;
	}

	if (leftA >= rightB)
	{
		return 0;
	}

	//If none of the sides from A are outside B
	return 1;
}


void applyCollision(game_Object_t* gameObject, SDL_Rect collider) {
	
}




void Animator(game_Object_t* gameObject) {
	if (gameObject->AnimationState == idle) {
		gameObject->frames = 2;
		gameObject->delay = 20;
		gameObject->srcRect.x = 1024 + 128 * ((int)gameObject->animationCount / gameObject->delay);

		gameObject->animationCount += 1;

		gameObject->srcRect.y = 0;

		if (gameObject->animationCount > gameObject->delay * (gameObject->frames - 1)) {
			gameObject->animationCount = 0;
		}
	}
	else if (gameObject->AnimationState == movef) {
		gameObject->frames = 8;
		gameObject->delay = 6;
		
		gameObject->srcRect.x = 128 * ((int) gameObject->animationCount / gameObject->delay);

		gameObject->animationCount += 1;

		gameObject->srcRect.y = 0;

		if (gameObject->animationCount > gameObject->delay  * (gameObject->frames - 1)) {
			gameObject->animationCount = 0;
		}
	}
}
