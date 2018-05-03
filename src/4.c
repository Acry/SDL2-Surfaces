//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see an
 * red initialized Window with icon.
 * The Window switches it's colors between
 * red and blue every second.
 * 
 * Using defines for colors and SDL_GetTicks
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO create a blue color to pass into SDL_FillRect
 * TODO create a timer to switch colors
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
#include <stdlib.h>
#include <SDL2/SDL.h>
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define BLUE 0,0,255,255
#define RED  255,0,0,255
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
SDL_SetWindowTitle(Window, "SDL2 fourth Window");
SDL_ShowWindow(Window);

//BEGIN ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
//END 	ICON
screen = SDL_GetWindowSurface(Window);
Uint32 red_pixel;
red_pixel=SDL_MapRGBA(screen->format, RED);
Uint32 blue_pixel;
blue_pixel=SDL_MapRGBA(screen->format, BLUE);
//END WINDOW

SDL_Event event;
Uint32 loop_start = 0;
Uint32 loop_end   = 0;
Uint32 loop_time  = 0;
Uint32 track_time = 0;
int running=1;
//END   INIT

//BEGIN MAIN LOOP
while(running){
	loop_start=SDL_GetTicks();
	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
	}
	//END   EVENT LOOP
	SDL_Delay(16);
	//BEGIN RENDERING
	if (track_time<=1000)
		SDL_FillRect(screen, NULL, red_pixel);
	else
		SDL_FillRect(screen, NULL, blue_pixel);

	SDL_UpdateWindowSurface(Window);
	//END   RENDERING
	loop_end=SDL_GetTicks();
	loop_time=loop_end-loop_start;
	track_time+=loop_time;
	if (track_time>2000)
		track_time=0;
	
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
