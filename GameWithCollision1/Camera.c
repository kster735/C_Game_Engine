#include "SDL.h"
#include "Camera.h"

camera_t* camera_new() {
	camera_t* camera = (camera_t*)malloc(sizeof(camera_t));
	return camera;
}

void camera_set(camera_t* camera, double xpos, double ypos, double  width, double height) {
	camera->viewport.x = xpos;
	camera->viewport.y = ypos;
	camera->viewport.w = width;
	camera->viewport.h = height;
};



