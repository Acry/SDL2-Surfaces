#pragma GCC diagnostic ignored "-Wunknown-pragmas"

/* refresh window surface
 */
#include "helper.h"

int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();

SDL_SetWindowSize(Window,200,200);
SDL_SetWindowTitle(Window, "Refresh Surface");
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
screen=SDL_GetWindowSurface(Window);
Uint32 color = SDL_MapRGB(screen->format, 113, 113, 113);
SDL_FillRect(screen, NULL, color);
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

				// fill surface
				SDL_FillRect(screen, NULL, color);


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

