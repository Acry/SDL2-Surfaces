//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see a
 * blue circle of Pixels on the screen
 *
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO put pixels at a certain location on the screen
 * TODO implement midpoint circle function
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
#include <stdlib.h>
#include <SDL2/SDL.h>
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define BLUE   0,0,255,255
#define WHITE  255,255,255,255
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
struct circle
{
	SDL_Point center;
	float radius;
};
//END	DATASTRUCTURES

//BEGIN GLOBALS
SDL_Window   *Window;
SDL_Surface  *screen;
//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void putpixel(SDL_Surface *surface, int, int, Uint32);
void drawcircle(struct circle *circle,Uint32 pixel);
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
SDL_SetWindowSize(Window,500,500);
SDL_SetWindowTitle(Window, "SDL2 - put pixel");
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

Uint32 blue_pixel;
blue_pixel=SDL_MapRGBA(screen->format, BLUE);
//END WINDOW

//BEGIN CIRCLE
struct circle circle1;
circle1.center.x=250;
circle1.center.y=250;
circle1.radius=150.0;
drawcircle(&circle1, blue_pixel);
//END CIRCLE
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

void drawcircle(struct circle *circle, Uint32 pixel)
{
	/* https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	 * Starting from (r,0)￼, it enumerates the points in
	 * counterclockwise order for the first octant,
	 * while simultaneously mirroring
	 * the points to the other octants.
	 */
	int x = (int)circle->radius;
	int x0=circle->center.x;
	int y0=circle->center.y;
	int y = 0;
	int err = 0;
	
	while (x >= y){
		putpixel(screen,x0 + x, y0 + y, pixel);
		putpixel(screen,x0 + y, y0 + x, pixel);
		
		putpixel(screen,x0 - y, y0 + x, pixel);
		putpixel(screen,x0 - x, y0 + y, pixel);
		
		putpixel(screen,x0 - x, y0 - y, pixel);
		putpixel(screen,x0 - y, y0 - x, pixel);
		
		putpixel(screen,x0 + y, y0 - x, pixel);
		putpixel(screen,x0 + x, y0 - y, pixel);
		
		if (err <= 0){
			y += 1;
			err += 2*y + 1;
		}
		if (err > 0){
			x -= 1;
			err -= 2*x + 1;
		}
	}
	
}
//END   FUNCTIONS
