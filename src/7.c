/* refresh gradient
 */
#include "helper.h"

void drawGradient(void);

int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();

SDL_SetWindowSize(Window,256,256);
SDL_SetWindowTitle(Window, "Refresh Gradient");
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
screen=SDL_GetWindowSurface(Window);
drawGradient();
SDL_UpdateWindowSurface(Window);

SDL_Event event;
int running=1;

while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
		if(event.type == SDL_WINDOWEVENT){
			if (event.window.event == SDL_WINDOWEVENT_RESIZED){

				// get resize surface
				screen=SDL_GetWindowSurface(Window);

				drawGradient();

				// refresh surface
				SDL_UpdateWindowSurface(Window);
			}
		}
	}

	// lower loop latency for more updates
	SDL_Delay(16); // in milliseconds

}

exit_();
return EXIT_SUCCESS;
}

void drawGradient(void){
	unsigned int *ptr = screen->pixels;

	for (int x=0; x <screen->w; x++){
		for (int y=0; y <screen->h; y++){
			// https://github.com/Acry/C-math-normalization/blob/master/main.c
			int xr = 255 * x / screen->w;
			int yr = 255 * y / screen->h;
			int row = y * (screen->pitch / screen->format->BytesPerPixel);
			// int Pixel = x * screen->format->BytesPerPixel;
			ptr[row + x] = SDL_MapRGBA(screen->format, xr, 255-yr, 255-xr, 255);
		}
	}

}
