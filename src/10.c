#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region HEAD
#pragma region DESCRIPTION

/* DESCRIPTION
 * flip surface
 * If you compile and run this you should see a
 * SDL Logo horizontal and vertical flipped the screen
 * like using SDL_RenderCopyEx with flags SDL_FLIP_VERTICAL|SDL_FLIP_HORIZONTAL
 * https://github.com/Acry/SDL2-Renderer/blob/master/src/1a.c
 * 
 * Need that also for loading OpenGL Textures.
 * https://github.com/Acry/SDL2-OpenGL
 * 
 */

/* DEFINED PROGRESS GOALS
 * Implement vertical and horizontal flip functions for surfaces
 *
 */
#pragma endregion   DESCRIPTION

#pragma region INCLUDES
#include <stdlib.h>
#include <SDL2/SDL.h>
#pragma endregion   INCLUDES

#pragma region CPP DEFINITIONS
#define WHITE  255,255,255,255
#pragma endregion   CPP DEFINITIONS

#pragma region DATASTRUCTURES
#pragma endregion DATASTRUCTURES

#pragma region GLOBALS
SDL_Window   *Window;
SDL_Surface  *screen;
SDL_Surface  *logo;
#pragma region VISIBLES
#pragma endregion 	VISIBLES

#pragma endregion   GLOBALS

#pragma region FUNCTION PROTOTYPES
SDL_Surface * flip_vertical	(SDL_Surface *);
SDL_Surface * flip_horizontal	(SDL_Surface *);
#pragma endregion FUNCTION PROTOTYPES

#pragma endregion 	HEAD

#pragma region MAIN FUNCTION
int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

#pragma region INIT
SDL_Init(SDL_INIT_VIDEO);

#pragma region WINDOW
Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
SDL_SetWindowSize(Window,179,99);
SDL_SetWindowTitle(Window, "Flip Surface");
SDL_ShowWindow(Window);

#pragma region ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");

SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
#pragma endregion 	ICON

screen = SDL_GetWindowSurface(Window);
Uint32 white_pixel;
white_pixel=SDL_MapRGBA(screen->format, WHITE);
SDL_FillRect(screen, NULL, white_pixel);
#pragma endregion WINDOW

#pragma region LOGO
logo=SDL_LoadBMP("./assets/gfx/SDL_logo.bmp");
logo=flip_vertical(logo);
logo=flip_horizontal(logo);
SDL_BlitSurface(logo,NULL,screen,NULL);
#pragma endregion 	LOGO
SDL_UpdateWindowSurface(Window);
SDL_Event event;

int running=1;
#pragma endregion   INIT

#pragma region MAIN LOOP
while(running){

	#pragma region EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
	}
	#pragma endregion   EVENT LOOP
	SDL_Delay(16);
	#pragma region RENDERING
	#pragma endregion   RENDERING
	
}
#pragma endregion   MAIN LOOP
SDL_FreeSurface		(logo);
SDL_FreeSurface		(screen);
SDL_DestroyWindow	(Window);
SDL_Quit();

return EXIT_SUCCESS;

}
#pragma endregion   MAIN FUNCTION

#pragma region FUNCTIONS
SDL_Surface * flip_horizontal(SDL_Surface *sfc)
{

	SDL_Surface *result= SDL_CreateRGBSurfaceWithFormat(0,sfc->w,sfc->h, sfc->format->BytesPerPixel, sfc->format->format);
	size_t pitch 	= sfc->pitch;
	int pxlength 	= pitch*sfc->h;

	void *pixels 	= sfc->pixels + pxlength;	// last pixel
	void *rpixels 	= result->pixels;		// first pixel	
	
	for(int line 	= 0; line < sfc->h; ++line){
		memcpy(rpixels,pixels,pitch);		// copy the line
		pixels -= pitch;			// count down
		rpixels += pitch;			// count up
	}
	return result;
	
}

SDL_Surface * flip_vertical(SDL_Surface *sfc)
{

	SDL_Surface *result= SDL_CreateRGBSurfaceWithFormat(0,sfc->w,sfc->h, sfc->format->BytesPerPixel, sfc->format->format);
	
	int pitch 	= sfc->pitch;
	void *pixels 	= sfc->pixels;
	void *rpixels 	= result->pixels+pitch;
	
 	size_t lenght = sfc->format->BytesPerPixel;
	
	for(int line = 0; line < sfc->h; ++line){
		for (int col = 0; col < sfc->w; col++){
			memcpy(rpixels,pixels,lenght);
			pixels+=lenght;
			rpixels-=lenght;
		}
		rpixels+=2*pitch;
	}
	return result;
	
}
#pragma endregion   FUNCTIONS
