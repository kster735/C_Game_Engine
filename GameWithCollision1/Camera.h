#ifndef CAMERA_H
#define CAMERA_H

//Screen dimension constants
#define SCREEN_WIDTH  1024;
#define SCREEN_HEIGHT  768;

typedef struct camera {
	SDL_Rect viewport;
}camera_t;


camera_t* camera_new();

void camera_set(camera_t* camera, double xpos, double ypos, double width, double height);

#endif
