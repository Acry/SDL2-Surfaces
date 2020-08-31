#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#include "helper.h"
SDL_Window *Window = NULL;
SDL_Surface *screen = NULL;
int pitch = 0;

void init(void)
{
	#pragma region INIT
	SDL_Init(SDL_INIT_VIDEO);

	#pragma region WINDOW
	Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
	SDL_ShowWindow(Window);

	#pragma region ICON
	SDL_Surface *icon;
	icon = SDL_LoadBMP("./assets/gfx/SDL2.bmp");
	SDL_SetWindowIcon(Window, icon);
	SDL_FreeSurface(icon);
	#pragma endregion 	ICON
	#pragma endregion WINDOW
}

void exit_(void)
{
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

int SDL_CalculatePitch(Uint32 format, int width)
{
    int pitch;
    if (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_BITSPERPIXEL(format) >= 8) {
        pitch = (width * SDL_BYTESPERPIXEL(format));
    } else {
        pitch = ((width * SDL_BITSPERPIXEL(format)) + 7) / 8;
    }
    pitch = (pitch + 3) & ~3;   /* 4-byte aligning for speed */
    return pitch;
}