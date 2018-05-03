//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see an
 * red initialized Window with icon.
 * 
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO create a red color to pass into SDL_FillRect
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
SDL_SetWindowSize(Window,800/2,600/2);
SDL_SetWindowTitle(Window, "SDL2 Third Window");
SDL_ShowWindow(Window);

//BEGIN ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
//END 	ICON
//TODO Description
Uint8 r,g,b,a;
r=255;
g=0;
b=0;
a=255;

screen = SDL_GetWindowSurface(Window);
Uint32 new_pixel;
new_pixel=SDL_MapRGBA(screen->format, r, g, b, a);

SDL_FillRect(screen, NULL, new_pixel);
SDL_UpdateWindowSurface(Window);
//END WINDOW

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
//END   FUNCTIONS
