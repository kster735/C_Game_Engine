#include "Game.h"
#include "InputManager.h"
#include "Camera.h"


const double SSPEED = 4;
const double FSPEED = 8;

//The dimensions of the level
const int LEVEL_WIDTH = 2048;
const int LEVEL_HEIGHT = 1536;

void InputManager(SDL_Event event, game_t* game, game_Object_t* player, camera_t* camera) {
	double SPEED;
	int moves = 0;

	if (event.type == SDL_QUIT) {
		game->isRunning = 0;
	}
	else {
			const Uint8* state = SDL_GetKeyboardState(NULL);
			

			if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) {
				SPEED = FSPEED;
			}
			else {
				SPEED = SSPEED;
			}
			/*
			//Compensate for diagonal speed
			//Not working properly due to camera modifications
			double temp = SPEED;
			if ((state[SDL_SCANCODE_D] && state[SDL_SCANCODE_S]) ||
				(state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W]) ||
				(state[SDL_SCANCODE_A] && state[SDL_SCANCODE_S]) ||
				(state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W])) {	
				SPEED = ( temp / sqrt(2));
			}else{
				SPEED = temp;
			}
			*/




			if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
				moves = 1;
				player->xpos += SPEED;
				
			}
			if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
				moves = 1;
				player->xpos -= SPEED;
				
			}
			if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
				moves = 1;
				player->ypos -= SPEED;
			}
			if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
				moves = 1;
				player->ypos += SPEED;
			}
			


			if (state[SDL_SCANCODE_KP_PLUS]) {
				if ((game->volume > 0) && (game->volume < MIX_MAX_VOLUME)) {
					game->volume = game->volume + 1;
					printf("Game volume: %d", game->volume);
					Mix_VolumeMusic(game->volume);
				}
			}
			if (state[SDL_SCANCODE_KP_MINUS]) {
				if ((game->volume > 1) ) {
					game->volume = game->volume - 1;
					printf("Game volume: %d", game->volume);
					Mix_VolumeMusic(game->volume);
				}
				else {
					game->volume = 1;
					printf("Game volume: %d", game->volume);
					Mix_VolumeMusic(game->volume);
				}
			}
			
			player->Collider.x = player->xpos;
			player->Collider.y = player->ypos;

			
			game->camera->viewport.x = (player->xpos + 32) - 1024 / 2;
			game->camera->viewport.y = (player->ypos + 32) - 768 / 2;

			//Keep the camera in bounds
			if (game->camera->viewport.x < 0)
			{
				game->camera->viewport.x = 0;
			}
			if (game->camera->viewport.y < 0)
			{
				game->camera->viewport.y = 0;
			}
			if (game->camera->viewport.x > LEVEL_WIDTH - game->camera->viewport.w)
			{
				game->camera->viewport.x = LEVEL_WIDTH - game->camera->viewport.w;
			}
			if (game->camera->viewport.y > LEVEL_HEIGHT - game->camera->viewport.h)
			{
				game->camera->viewport.y = LEVEL_HEIGHT - game->camera->viewport.h;
			}



			//Keep player in bounds
			if (player->xpos < 0)
			{
				player->xpos = 0;
			}
			if (player->ypos < 0)
			{
				player->ypos = 0;
			}
			if (player->xpos > LEVEL_WIDTH - 64)
			{
				player->xpos = LEVEL_WIDTH - 64;
			}
			if (player->ypos > LEVEL_HEIGHT - 64)
			{
				player->ypos = LEVEL_HEIGHT - 64;
			}


			if (moves) {
				player->AnimationState = movef;
			}
			else {
				player->AnimationState = idle;
			}


	}
}
