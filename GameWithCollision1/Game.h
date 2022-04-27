#ifndef Game_h
#define Game_h
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "GameObject.h"
#include "TileMap.h"
#include "Camera.h"

struct Game {
	int isRunning;
	int count;
	int volume;
	SDL_Window* window;
	camera_t* camera;
	SDL_Renderer* renderer;
	Mix_Music* gMusic;
};

typedef struct Game game_t;
game_t Game_create();
void Game_destroy(game_t *game);
void init(game_t *game, const char* title, double xpos, double ypos, int width, int height, int fullscreen);
void handleEvents(game_t *game);
void update(game_t* game);
void render(game_t* game);
void clean(game_t* game);
int running(game_t game);

#endif