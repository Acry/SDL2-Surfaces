//BEGIN HEAD
//BEGIN DESCRIPTION

/* 
 * If you compile and run this you should see an
 * red initialized Window with icon.
 * 
 */

/* DEFINED PROGRESS GOALS
 * 
 * TODO 
 * TODO 
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
Uint32 get_pixel32( SDL_Surface *surface, int x, int y );
void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void pixel_info(Uint32 format);
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
SDL_SetWindowSize(Window,800,600);
SDL_SetWindowTitle(Window, "SDL2 Third Window");
SDL_ShowWindow(Window);

//BEGIN ICON
SDL_Surface *icon;
icon=SDL_LoadBMP("./assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
//END 	ICON

screen = SDL_GetWindowSurface(Window);
Uint32 fmt;
fmt = SDL_GetWindowPixelFormat(Window);
pixel_info(fmt);

// Uint32 *pixels = (Uint32 *)malloc(sizeof(Uint32)* 800 * 600);
// if (SDL_MUSTLOCK(screen)){
// 	SDL_Log("Needs to be locked");
// 	SDL_LockSurface(screen);
// } else {
// 	SDL_Log("Doesn't need to be locked");
// 	pixels=screen->pixels;
// 	
// 
// }
short int xxx = 0 ;
short int yyy = 0 ;
Uint8 r,g,b,a;
uint32_t pixel;

SDL_Log("r: %d g: %d b; %d a: %d",r,g,b,a);
pixel = *( ( uint32_t * )screen->pixels + yyy * screen->w + xxx ) ;
SDL_GetRGBA(pixel, screen->format, &r, &g, &b, &a);
SDL_Log("r: %d g: %d b; %d a: %d",r,g,b,a);

Uint32 new_pixel;
r=255;
a=255;
new_pixel=SDL_MapRGBA(screen->format, r, g, b, a);
SDL_GetRGBA(new_pixel, screen->format, &r, &g, &b, &a);
SDL_Log("r: %d g: %d b; %d a: %d",r,g,b,a);

SDL_FillRect(screen, NULL, new_pixel);
// putpixel(screen, 30, 30, new_pixel);

// unsigned int *pixels = (unsigned int *)screen->pixels;
// unsigned int color = 0xffff0000;
// for (int y=0;y<screen->w;y++){
// 	for (int x=0;x<screen->h;x++){
// 		pixels[x+(y*screen->w)] = color;
// 	}
// }

// int i;
// for (i=0; i<10; i++){
// 	putpixel(screen, i, y, new_pixel);
// }



// put_pixel32( screen->pixels, 0, 0, new_pixel );
// put_pixel32( screen->pixels, 0, 1, new_pixel );
// put_pixel32( screen->pixels, 1, 0, new_pixel );
// put_pixel32( screen->pixels, 1, 1, new_pixel );

// int i;
// int j;
// for (i=0; i<10; i++){
// 	for (j=0; j<10; j++){
// 		pixels[ j * screen->w + i ] = new_pixel;	
// 	}
// 	
// 	
// 
// }



// put_pixel32( screen->pixels, 0, 0, new_pixel );
// screen->pixels[0]=new_pixel;

/* Surface is locked */
/* Direct pixel access on surface here */
// Uint8 byteincrement  = screen->format->BytesPerPixel;
// for(int position = 0; position < screen->w * screen->h* byteincrement; position += byteincrement  ){
// 	Uint8* curpixeldata = (Uint8*)screen->pixels + position;
// 	Uint32 *pixels = (Uint32 *)screen->pixels;
// 	pixels[byteincrement++]=new_pixel;
// 	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
// }
// pixels[ ( y * surface->w ) + x ] = pixel;
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
//free pixels
// free (pixels);
SDL_FreeSurface(screen);
SDL_DestroyWindow(Window);
SDL_Quit();

return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;
// 	pixel = *( ( uint32_t * )screen->pixels + y * screen->w + x ) ;
	//Get the requested pixel
	return pixels[ y * surface->w + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32 *)surface->pixels;
	
	//Set the pixel
	
	pixels[ y * surface->w + x ] = pixel;
}

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
void pixel_info(Uint32 format)
{
	SDL_Log("fmt: %s", SDL_GetPixelFormatName(format));
	SDL_Log("PIXELTYPE: %d", SDL_PIXELTYPE(format));
}
//END   FUNCTIONS
