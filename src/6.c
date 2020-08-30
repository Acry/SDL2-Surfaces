
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#pragma region HEAD
/* Gradient
 * If you compile and run this you should see an RGB-
 * gradient of Pixels on the screen
 *
 */

#include "helper.h"

void drawGradient(void);

int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();

SDL_SetWindowSize(Window,256,256);
SDL_SetWindowTitle(Window, "fixed gradient");
SDL_SetWindowResizable(Window, SDL_FALSE);
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

screen = SDL_GetWindowSurface(Window);
pitch = SDL_CalculatePitch(screen->format, screen->w);

drawGradient();
SDL_UpdateWindowSurface(Window);
SDL_Event event;

int running = 1;

while(running){

	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running = 0;
		}
		if(event.type == SDL_WINDOWEVENT){
			if (event.window.event == SDL_WINDOWEVENT_RESIZED){
				SDL_Log("Resize Event");
				SDL_Log("x %d",event.window.data1);
				SDL_Log("y %d",event.window.data2);
				screen = SDL_GetWindowSurface(Window);
				pitch = SDL_CalculatePitch(screen->format, screen->w);
				SDL_Log("pitch: %d", pitch);
				int bpp = screen->format->BytesPerPixel;
				SDL_Log("bpp: %d", bpp);
				int formatPitch = screen->pitch;
				SDL_Log("formatPitch: %d", formatPitch);
			}
		}
	}
	

	SDL_Delay(16);
}

exit_();
return EXIT_SUCCESS;
}



void drawGradient(void){
	unsigned int *ptr = (unsigned int*)screen->pixels;

	for (int x=0; x <screen->w; x++){
		for (int y=0; y <screen->h; y++){
			ptr[y * pitch + x] = SDL_MapRGBA(screen->format, x, 255-y, 255-x, 255);
		}
	}
}






