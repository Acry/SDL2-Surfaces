//BEGIN HEAD
//BEGIN DESCRIPTION

/* Set Window and a few window attributes
 * If you compile and run this you should see an
 * uninitialized Window.
 * 
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO Inititalize SDL2
 * TODO Bring Window up
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
#include <stdlib.h>
//on Linux we usually include SDL2 like this
#include <SDL2/SDL.h>
//END   INCLUDES

//BEGIN CPP DEFINITIONS
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
//typedef'ed struct from SDL_video
SDL_Window   *Window;
//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{
//silence compiler warnings about unused vars
(void)argc;
(void)argv;

//BEGIN INIT
//https://wiki.libsdl.org/SDL_Init
SDL_Init(SDL_INIT_VIDEO);
//video subsystem; automatically initializes the events subsystem
//BEGIN WINDOW
//going to hide everything until all set
Window = SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_HIDDEN);
//https://wiki.libsdl.org/SDL_WindowFlags

SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,800/2,600/2);
SDL_SetWindowTitle(Window, "SDL2 First Window");
SDL_ShowWindow(Window);
//END WINDOW

//Don't bother about the events atm. We gonna get there
SDL_Event event;

//Setting the loop condition
int running=1;
//END   INIT
//starting loop that catches the quit event if you press the closing button
//BEGIN MAIN LOOP
while(running){
	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
	}
	//END   EVENT LOOP
	//https://wiki.libsdl.org/SDL_Delay
	//Use this function to wait a specified number of milliseconds before returning.
	SDL_Delay(16);
	/* declared in SDL_timer.h
	 * The point why I call this, is to give the CPU a little break.
	 */
	//BEGIN RENDERING
	//END   RENDERING
}
//END   MAIN LOOP
//Need to clean up before we exit
SDL_DestroyWindow(Window);
//https://wiki.libsdl.org/SDL_DestroyWindow

// https://wiki.libsdl.org/SDL_Quit
SDL_Quit();
//Use this function to clean up all initialized subsystems.

//Now we have a Window and we can close it.
//That's pretty much about it. jump to the source code 2.c
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS

//END   FUNCTIONS
