#include "helper.h"
SDL_Window *Window = NULL;
SDL_Surface *screen = NULL;
void init(void)
{
	//BEGIN INIT
	SDL_Init(SDL_INIT_VIDEO);

	//BEGIN WINDOW
	Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	SDL_SetWindowPosition(Window, 0, 0);
	SDL_SetWindowSize(Window, 256, 256);
	SDL_SetWindowTitle(Window, "linear gradient");
	SDL_ShowWindow(Window);

	//BEGIN ICON
	SDL_Surface *icon;
	icon = SDL_LoadBMP("./assets/gfx/SDL2.bmp");
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);
	//END 	ICON
	//END WINDOW
}

void exit_(void)
{
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
