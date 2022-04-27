#ifndef GAME_OBJECT
#define GAME_OBJECT
#include "TileMap.h"
typedef enum state { idle, movef, moveb, mover, movel, movefr, movefl, movebr, movebl, spawn, die, special } state_t;


typedef struct GameObject {
	double xpos;
	double ypos;
	double initialxpos;
	double initialypos;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
	state_t AnimationState;
	SDL_Rect Collider;
	int animationCount;
	int frames;
	int delay;
	int collides;
} game_Object_t;

game_Object_t Game_Object_create(const char* texturesheet, SDL_Renderer* renderer, double x, double y);

void Game_Object_destroy(game_Object_t* gameObject);

void UpdateEnvironmentObjects(game_Object_t *gameObject, tile_map_t tilemap);

void RenderObject(game_Object_t* gameObject, int width, int height, double x, double y, double scaleW, double scaleH, camera_t* camera);

int checkCollision(SDL_Rect a, SDL_Rect b);

void applyCollision(game_Object_t* gameObject, SDL_Rect collider);

void Animator(game_Object_t* gameObject);

#endif
