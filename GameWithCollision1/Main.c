#include "SDL.h"
#include "Game.h"

game_t game;
game_t *pgame = NULL;


int main(int argc, char *argv[]) {
	
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32  frameStart;
	int frameTime;

	game = Game_create();
	pgame = &game;

	init(pgame, "This game sucks!", 100, 100, 1024, 768, 0);

	while (running(game)) {

		frameStart = SDL_GetTicks();

		handleEvents(pgame);
		update(pgame);
		render(pgame);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < frameDelay) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	clean(pgame);
	Game_destroy(pgame);
	return 0;
}