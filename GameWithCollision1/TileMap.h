#ifndef TILEMAP_H
#define TILEMAP_H
#include "Game.h"
#include "Camera.h"

#define MAPH 24
#define MAPW 32

typedef struct TileMap {
	double xpos;
	double ypos;
	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Renderer* renderer;

	int map[MAPH][MAPW];

} tile_map_t;

//tile_map_t* Tile_Map_new(void);

tile_map_t Tile_Map_create(SDL_Renderer* renderer);

void Tile_Map_destroy(tile_map_t* tilemap);

void LoadTileMap(int arr[MAPH][MAPW],tile_map_t* tilemap);

void RenderTileMap(tile_map_t* tilemap, camera_t* camera);

#endif
