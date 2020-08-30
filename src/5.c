#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#pragma region HEAD

/* 
 * If you compile and run this you should see an
 * black initialized Window with icon and custom pointer.
 * 
 * SDL_BlitScaled
 */

/* DEFINED PROGRESS GOALS
 * 
 * Custom pointer
 * 
 */

#include "helper.h"


#pragma endregion 	HEAD

#pragma region MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

init();

SDL_SetWindowSize(Window,200,200);
SDL_SetWindowTitle(Window, "custom pointer");
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

#pragma region Cursor

SDL_Cursor  *cursor       = NULL;

SDL_Surface *cur_surf     = NULL;
SDL_Surface *temp_surface = NULL;

// load bitmap
temp_surface = SDL_LoadBMP("assets/gfx/pointer.bmp");

// create a new smaller surface with the same format (alpha)
cur_surf = SDL_CreateRGBSurfaceWithFormat(0, 28, 28, 24, temp_surface->format->format);

// scale the bitmap down
SDL_BlitScaled(temp_surface, NULL, cur_surf, NULL);

// https://wiki.libsdl.org/SDL_CreateColorCursor
cursor = SDL_CreateColorCursor(cur_surf, 0, 0);
SDL_SetCursor(cursor);

SDL_FreeSurface(cur_surf);
SDL_FreeSurface(temp_surface);

#pragma endregion CUSTOM CURSOR

screen = SDL_GetWindowSurface(Window);
Uint32 color;
color = SDL_MapRGB(screen->format, 113, 113, 113);
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
				screen=SDL_GetWindowSurface(Window);
				SDL_FillRect(screen, NULL, color);
				SDL_UpdateWindowSurface(Window);
			}
		}
	}
	SDL_Delay(16);
}

// free cursor
SDL_FreeCursor(cursor);

exit_();

return EXIT_SUCCESS;

}
#pragma endregion   MAIN FUNCTION
