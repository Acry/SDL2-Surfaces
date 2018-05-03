//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see an RGB-
 * gradient of Pixels on the screen, but the window
 * is resizeable and updated.
 */

/* Annotations
 * Some of the init stuff went into helper.c
 * 
 * If you didn't before, you may start figuring where CPU
 * based rendering leads to and why people start using an hardware
 * based rendering infrastructure like OpenGL or Vulkan.
 * But the next example series will make this way more clear,
 * before I jump into hardware accelerated rendering.
 * 
 */

/* DEFINED PROGRESS GOALS
 * TODO making window resizeable: SDL_WINDOW_RESIZABLE
 * TODO asking resize events
 * TODO take screen size into account when...
 * TODO update screen/surface
 */

/* TODO Note to myself
 * 	Upload according C-Tutorials
 */

//END   DESCRIPTION

//BEGIN INCLUDES
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WW 256
#define WH 256
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
struct vec4{
	float r;
	float g;
	float b;
	float a;
};

struct vec2{
	float x;
	float y;
};

struct pixels{
	struct vec4 color;
	struct vec2 pos;
};
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;
struct pixels *pix_map = NULL;
//So the pixmap consists of pixel, which in turn are made of positions and colors.
//Pretty clear, right?
//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void putpixel(SDL_Surface *surface, int, int, Uint32);
void update_screen(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();
SDL_Event event;
int running=1;

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
		if(event.type == SDL_WINDOWEVENT){
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
				ww = event.window.data1;
				wh = event.window.data2;
				update_screen();
			}
		}
	}
	
	//END   EVENT LOOP
	SDL_Delay(16);
	//BEGIN RENDERING

	//END   RENDERING
	
}
//END   MAIN LOOP

free(pix_map);
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
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

void update_screen(void)
{
	screen = SDL_GetWindowSurface(Window);
	pix_map = realloc(pix_map, ww*wh * (sizeof *pix_map));

	//BEGIN GRADIENT
	int x=0;
	int y=0;
	//Set Pixel positions
	for (int i=0;i<ww*wh;i++){
		pix_map[i].pos.x=(float)x/(float)(ww-1);
		pix_map[i].pos.y=(float)y/(float)(wh-1);
		x++;
		if (x==ww){
			x=0;
			y++;
		}
	}
	//Set Pixel colors according to their position
	Uint32 color=0;
	for (int i=0;i<ww*wh;i++){
		pix_map[i].color.r=pix_map[i].pos.x;
		pix_map[i].color.g=1.0-pix_map[i].pos.y;
	}
	//map pixels on the surface
	for (int i=0;i<ww*wh;i++){
		color=SDL_MapRGBA(screen->format,(int)(pix_map[i].color.r*255), (int)(pix_map[i].color.g*255), (int)(pix_map[i].color.b*255), (int)(pix_map[i].color.a*255));
		
		putpixel(screen, roundf( pix_map[i].pos.x * ((float)ww-1.0) ), roundf( pix_map[i].pos.y * ((float)wh-1.0) ), color);
	}
	//END GRADIENT
	SDL_UpdateWindowSurface(Window);
}
//END   FUNCTIONS
