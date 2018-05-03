//BEGIN HEAD
//BEGIN DESCRIPTION

/* DESCRIPTION
 * If you compile and run this you should see an RGB-
 * gradient of Pixels on the screen, but the window
 * is resizeable and updated + colors are changed over time
 */

/* Annotations
 * Now the functions are timed and we gonna see that functions
 * are pretty expensive, that's why I introduce you to the
 * SDL_Renderer in set 2.
 * 
 * If you maximize the window, the program should be pretty slow,
 * it depends on your machine, but still - it should slow down 
 * significantly.
 */

/* DEFINED PROGRESS GOALS
 * TODO include a timer
 * TODO make it pausable
 * TODO profile the function
 * TODO since I use clock_gettime anyways I use it for Loop
 *      Timing.
 */


//END   DESCRIPTION

//BEGIN INCLUDES
#include "helper.h"
#include <time.h>
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

float fTime=0;
SDL_bool paused	 = SDL_FALSE;

//BEGIN VISIBLES
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void putpixel(SDL_Surface *surface, int, int, Uint32);
void update_screen(void);
struct timespec diff(struct timespec start, struct timespec end);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();
Uint32 loop_start = 0;
Uint32 loop_end   = 0;
Uint32 loop_time  = 0;

struct timespec start, stop, start_loop, stop_loop, temp, wait;
wait.tv_sec = 0;
//30 FPS 	MS   * μs   * ns
wait.tv_nsec = 33333333L;
//33,000,000 Nanoseconds
SDL_Event event;
int running=1;

//BEGIN MAIN LOOP
while(running){
	clock_gettime(CLOCK_REALTIME, &start_loop);
	loop_start=SDL_GetTicks();
	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
		if(event.type == SDL_WINDOWEVENT){
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
				ww = event.window.data1;
				wh = event.window.data2;

			}
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				paused=paused^1; //XOR - flip var
			}
			if(event.button.button == SDL_BUTTON_LEFT){
				paused=paused^1; //XOR - flip var
			}
		}
	}
	
	//END   EVENT LOOP

	//BEGIN RENDERING
	if (!paused){
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		update_screen();
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
		temp=diff(start,stop);
		SDL_Log("FT: %.2f ms", (float)temp.tv_nsec/1000000 );
	}
	//END   RENDERING
	loop_end=SDL_GetTicks();
	loop_time=loop_end-loop_start;
	fTime+=(float)loop_time/1000;
	clock_gettime(CLOCK_REALTIME, &stop_loop);
	temp=diff(start_loop,stop_loop);
// 	SDL_Log("LT before : %ld", temp.tv_nsec );
	temp=diff(temp,wait);
// 	SDL_Log("wait time : %ld", temp.tv_nsec );
// 	SDL_Log("wait limit: %ld", wait.tv_nsec );
	if (temp.tv_nsec<wait.tv_nsec)
		while (nanosleep(&temp, &temp)); //TODO handle interrupts
	else
		SDL_Log("Oh no, we don't even get 30 FPS!");

	clock_gettime(CLOCK_REALTIME, &stop_loop);
	temp=diff(start_loop,stop_loop);
// 	SDL_Log("LT af wait: %ld", temp.tv_nsec );
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
	//Set Pixel positions and colors like on https://www.shadertoy.com/new
	//vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
	for (int i=0;i<ww*wh;i++){
		pix_map[i].pos.x=(float)x/(float)(ww-1);
		pix_map[i].pos.y=(float)y/(float)(wh-1);
		pix_map[i].color.r=0.5 + 0.5*cos(fTime+pix_map[i].pos.x+(1.0-pix_map[i].pos.y));
		pix_map[i].color.g=0.5 + 0.5*cos(fTime+pix_map[i].pos.x+(1.0-pix_map[i].pos.y)+2);
		pix_map[i].color.b=0.5 + 0.5*cos(fTime+pix_map[i].pos.x+(1.0-pix_map[i].pos.y)+4);
		pix_map[i].color.a=1.0;
		x++;
		if (x==ww){
			x=0;
			y++;
		}
	}


	//map pixels on the surface
	Uint32 color=0;
	for (int i=0;i<ww*wh;i++){
		color=SDL_MapRGBA(screen->format,(int)(pix_map[i].color.r*255), (int)(pix_map[i].color.g*255), (int)(pix_map[i].color.b*255), (int)(pix_map[i].color.a*255));
		putpixel(screen, roundf( pix_map[i].pos.x * ((float)ww-1.0) ), roundf( pix_map[i].pos.y * ((float)wh-1.0) ), color);
	}
	//END GRADIENT
	SDL_UpdateWindowSurface(Window);
}

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}
//END   FUNCTIONS
