//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see a
 * the SDL Logo on the screen
 *
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO Load/free and blit logo
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
SDL_SetWindowTitle(Window, "Blit");
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
/*
 *  From SDL_surface.h
 *  You should call SDL_BlitSurface() unless you know exactly how SDL
 *  blitting works internally and how to use the other blit functions.
 *
 *  #define SDL_BlitSurface SDL_UpperBlit
 *
 *  This is the public blit function, SDL_BlitSurface(), and it performs
 *  rectangle validation and clipping before passing it to SDL_LowerBlit()
 *
 *  extern DECLSPEC int SDLCALL SDL_UpperBlit
 *  (SDL_Surface * src, const SDL_Rect * srcrect,
 *   SDL_Surface * dst, SDL_Rect * dstrect);
 */
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
//END   FUNCTIONS
