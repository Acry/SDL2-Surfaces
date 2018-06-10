//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
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
//END   DESCRIPTION

//BEGIN INCLUDES
#include <stdlib.h>
#include <SDL2/SDL.h>
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WHITE  255,255,255,255
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
SDL_Window   *Window;
SDL_Surface  *screen;
SDL_Surface  *logo;
//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
SDL_Surface * flip_vertical	(SDL_Surface *);
SDL_Surface * flip_horizontal	(SDL_Surface *);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

//BEGIN INIT
SDL_Init(SDL_INIT_VIDEO);

//BEGIN WINDOW
Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,179,99);
SDL_SetWindowTitle(Window, "5b.c - flip");
SDL_ShowWindow(Window);

//BEGIN ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");

SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
//END 	ICON

screen = SDL_GetWindowSurface(Window);
Uint32 white_pixel;
white_pixel=SDL_MapRGBA(screen->format, WHITE);
SDL_FillRect(screen, NULL, white_pixel);
//END WINDOW

//BEGIN LOGO
logo=SDL_LoadBMP("./assets/gfx/SDL_logo.bmp");
logo=flip_vertical(logo);
logo=flip_horizontal(logo);
SDL_BlitSurface(logo,NULL,screen,NULL);
//END 	LOGO
SDL_UpdateWindowSurface(Window);
SDL_Event event;

int running=1;
//END   INIT

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
	}
	//END   EVENT LOOP
	SDL_Delay(16);
	//BEGIN RENDERING
	//END   RENDERING
	
}
//END   MAIN LOOP
SDL_FreeSurface(logo);
SDL_FreeSurface(screen);
SDL_DestroyWindow(Window);
SDL_Quit();

return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
SDL_Surface * flip_horizontal(SDL_Surface *sfc)
{
	// What is pitch and stride?
	// Stride means bytes in a row of pixels including any padding.
	// Pitch should be a synonym.
	
	// Pitch, absolute value, the number of bytes per bitmap line;
	// it can be either positive or negative depending on the bitmap's vertical orientation
	
	// To find a specific pixel in the padded image, you go like this:
	// Pixel = (y   * pitch) + x;
	// Pixel = (line*pitch ) +col

	// 	SDL_PixelFormat *format;    Read-only
	// 	int w, h;                   Read-only
	// 	int pitch;                  Read-only, the length of a row of pixels in bytes
	// 	void *pixels;               Read-write
	
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
//END   FUNCTIONS
