#include "TextureManager.h"
#include "TileMap.h"
#include "Camera.h"


int levelOne[MAPH][MAPW] = {
	{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,0,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,0,2,2,2,2,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,2,2,2,2,1,1,1,1,1,1,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


/*tile_map_t* Tile_Map_new(void) {
	return (tile_map_t*)malloc(sizeof(tile_map_t));
}*/

tile_map_t Tile_Map_create(SDL_Renderer* renderer) {
	tile_map_t tilemap;
	tilemap.renderer = renderer;
	
	tilemap.dirt = LoadTexture("assets/dirt.png", renderer);
	tilemap.grass = LoadTexture("assets/grass.png", renderer);
	tilemap.water = LoadTexture("assets/water.png", renderer);

	LoadTileMap(levelOne, &tilemap);

	tilemap.xpos = tilemap.ypos = 0;
	tilemap.src.x = tilemap.src.y =  0;
	tilemap.src.h = tilemap.dest.h = 64;
	tilemap.src.w = tilemap.dest.w = 64;

	tilemap.dest.x = tilemap.dest.y = 0;

	printf("About to return tilemap\n");
	printf("%d\n", tilemap.map[3][3]);
	return tilemap;
}

void Tile_Map_destroy(tile_map_t* tilemap) {
	free(tilemap->dirt);
	free(tilemap->grass);
	free(tilemap->water);
}

void LoadTileMap(int arr[MAPH][MAPW], tile_map_t* tilemap) {
	int i, j;
	for (i = 0; i < MAPH; i++) {
		for (j = 0; j < MAPW; j++) {
			tilemap->map[i][j] = arr[i][j];
		}
	}
}

void RenderTileMap(tile_map_t* tilemap, camera_t* camera) {
	typedef enum{grass, dirt, water} Ground;
	tilemap->xpos = -camera->viewport.x;
	tilemap->ypos = -camera->viewport.y;

	Ground ground;
	int i, j;
	for (i = 0; i < MAPH; i++) {
		for (j = 0; j < MAPW; j++) {
			 ground = tilemap->map[i][j];

			 tilemap->dest.x = j * 64 + tilemap->xpos;
			 tilemap->dest.y = i * 64 + tilemap->ypos;

			 switch (ground) {
			 case grass:
				 Draw(tilemap->grass, tilemap->src, tilemap->dest, tilemap->renderer);
				 break;
			 case dirt:
				 Draw(tilemap->dirt, tilemap->src, tilemap->dest, tilemap->renderer);
				 break;
			 case water:
				 Draw(tilemap->water, tilemap->src, tilemap->dest, tilemap->renderer);
				 break;
			 default:
				 break;
			 }
		}
	}

	
}