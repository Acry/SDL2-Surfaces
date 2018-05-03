//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see an RGB-
 * gradient of Pixels on the screen
 *
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO implement nested for loop changing RGB Values
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
#include <stdlib.h>
#include <SDL2/SDL.h>
//END   INCLUDES

//BEGIN CPP DEFINITIONS
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
SDL_Window   *Window;
SDL_Surface  *screen;
//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void putpixel(SDL_Surface *surface, int, int, Uint32);
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
SDL_SetWindowSize(Window,256,256);
SDL_SetWindowTitle(Window, "linear gradient");
SDL_ShowWindow(Window);

//BEGIN ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
//END 	ICON

screen = SDL_GetWindowSurface(Window);
//END WINDOW

//BEGIN GRADIENT
Uint32 color=0;
for (int i=0; i <screen->w; i++){
	for (int j=0; j <screen->h; j++){
		color=SDL_MapRGBA(screen->format, i, 255-j, 255-i, 255);
		putpixel(screen,i,j,color);
	}
	
}
//END GRADIENT
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

SDL_FreeSurface(screen);
SDL_DestroyWindow(Window);
SDL_Quit();

return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	/* Code from 
	 * http://sdl.beuc.net/sdl.wiki/Pixel_Access
	 */
	
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	
	switch(bpp) {
		case 1:
			*p = pixel;
			break;
			
		case 2:
			*(Uint16 *)p = pixel;
			break;
			
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
			} else {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
			}
			break;
			
		case 4:
			*(Uint32 *)p = pixel;
			break;
	}
}
//END   FUNCTIONS
