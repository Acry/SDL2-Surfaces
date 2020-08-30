#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#pragma region HEAD

/* 
 * I moved the init code in helper functions to clean up.
 * 
 * If you compile and run this you should see an
 * black initialized Window with icon.
 * 
 */

/* DEFINED PROGRESS GOALS
 * 
 * Set Icon
 * 
 */
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Window *Window = NULL;
SDL_Surface *screen = NULL;

// function prototype
void init(void);

#pragma endregion 	HEAD

#pragma region MAIN
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

init();

#pragma region ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
#pragma endregion 	ICON




SDL_Event event;

int running=1;

while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
	}
	SDL_Delay(16);
}
SDL_DestroyWindow(Window);
SDL_Quit();

return EXIT_SUCCESS;

}
#pragma endregion   MAIN

void init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	Window = SDL_CreateWindow("Set Icon",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 200, 200, 0);
	screen = SDL_GetWindowSurface(Window);
	Uint32 color = SDL_MapRGB(screen->format, 113, 113, 113);
	SDL_FillRect(screen, NULL, color);
	SDL_UpdateWindowSurface(Window);
}