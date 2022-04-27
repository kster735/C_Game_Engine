#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"


Mix_Chunk* walk = NULL;
game_Object_t player, crate;
game_Object_t* pplayer, *pcrate;
game_Object_t background;
tile_map_t tilemap;
tile_map_t* ptilemap;


game_t Game_create() {
	game_t game;
	game.isRunning = 0;
	game.count = 1;
	game.window = NULL;
	game.renderer = NULL;
	game.camera = camera_new();
	printf("Game created successfully!\n");
	game.gMusic = NULL;
	game.volume = (int) MIX_MAX_VOLUME / 4;
	return game;
}

void Game_destroy(game_t *game) {
	game->renderer = NULL;
	free(game->renderer);
	game->window = NULL;
	free(game->window);
	printf("Game destroyed successfully!\n");
}

void  init(game_t *game, const char* title, double xpos, double ypos, int width, int height, int fullscreen) {
	fullscreen = 0;

	camera_set(game->camera, 0, 0, 1024, 768);

	if (fullscreen == 1) {
		fullscreen = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Failed initializing SDL: \n");
		game->isRunning = 0;
	}
	else {

		//Create Window
		game->window = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
		if (game->window) {
			printf("Window created!\n");
		}
		//Create Game Renderer
		game->renderer = SDL_CreateRenderer(game->window, -1, 0);
		if (game->renderer) {
			SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
			printf("Renderer is created!\n");
		}
		game->isRunning = 1;

		//Initialize Audio
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}	
	}

	//Create Tilemap
	tilemap = Tile_Map_create(game->renderer);
	ptilemap = &tilemap;

	//background = Game_Object_create("assets/background.png", game->renderer, 0, 0);
	// Load player spritesheet
	player = Game_Object_create("assets/PlayerSpriteSheetX.png", game->renderer, 512, 384);
	pplayer = &player;

	//Load environment objects
	crate = Game_Object_create("assets/crate.png", game->renderer, 640, 384);
	pcrate = &crate;

	//Load music
	game->gMusic = Mix_LoadMUS("assets/music.wav");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);
	walk = Mix_LoadWAV("assets/walk.wav");

	if (game->gMusic == NULL || walk == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}

	//Play Music
	Mix_PlayMusic(game->gMusic, -1);
	
}

void handleEvents(game_t *game) {
	enum collision{left=1, right, top, bottom}side;
	side = 0;
	SDL_Event event;
	SDL_PollEvent(&event);
	
	InputManager(event, game, &player, ptilemap, game->camera);
	
	if (checkCollision(pplayer->Collider, pcrate->Collider)) {
		if (player.xpos + player.Collider.w  > pcrate->Collider.x  && player.xpos < pcrate->Collider.x) {
			side = left;
		}
		if  (player.xpos < pcrate->Collider.x + pcrate->Collider.w && player.xpos > pcrate->Collider.x ) {
			side = right;
		}
		if (player.ypos + player.Collider.h >  pcrate->Collider.y && player.ypos < pcrate->Collider.y) {
			side = top;
		}
		if (player.ypos < pcrate->Collider.y + pcrate->Collider.h  && player.ypos > pcrate->Collider.y) {
			side = bottom;
		}
	}
	else {
		side = 0;
	}
	
	switch (side) {
	case left:
		pplayer->xpos = pcrate->Collider.x - player.Collider.w;
		break;
	case right:
		pplayer->xpos = pcrate->Collider.x + pcrate->Collider.w;
		break;
	case top:
		pplayer->ypos = pcrate->Collider.y - player.Collider.h;
		break;
	case bottom:
		pplayer->ypos = pcrate->Collider.y + pcrate->Collider.h;
		break;
	default:
		break;
	}

}

void update(game_t* game) {
	UpdateEnvironmentObjects(pcrate, tilemap);
	Animator(pplayer);

	if (pplayer->AnimationState == movef && Mix_Playing(-1) == 0) {
		Mix_PlayChannel(-1, walk, 0);
	}
}

void render(game_t* game) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	
	RenderTileMap(ptilemap, game->camera);
	RenderObject(pcrate, 128, 128, 0, 0, 0.5, 0.5, NULL);
    RenderObject(pplayer, 128, 128, pplayer->srcRect.x, 0, 0.5, 0.5, game->camera);
	
	SDL_RenderPresent(game->renderer);
}

void clean(game_t* game) {
	//Tile_Map_destroy(&tilemap);
	SDL_DestroyWindow(game->window);
	SDL_DestroyRenderer(game->renderer);
	game->window = NULL;
	game->renderer = NULL;
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	printf("Game cleaned!\n");
}

int running(game_t game) {
	return game.isRunning;
}
