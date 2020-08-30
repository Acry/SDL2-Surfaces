#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma region HEAD
#pragma region DESCRIPTION

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
 * include a timer
 * make it pausable
 * TODO profile the function
 * since I use clock_gettime anyways I use it for Loop
 *      Timing.
 */


#pragma endregion   DESCRIPTION

#pragma region INCLUDES
#include "helper.h"
#include <time.h>
#pragma endregion   INCLUDES

#pragma region CPP DEFINITIONS
#define WW 256
#define WH 256
#pragma endregion   CPP DEFINITIONS

#pragma region DATASTRUCTURES
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
#pragma endregion DATASTRUCTURES

#pragma region GLOBALS
int ww=WW;
int wh=WH;
struct pixels *pix_map = NULL;

float fTime=0;
SDL_bool paused	 = SDL_FALSE;
#pragma endregion   GLOBALS

#pragma region FUNCTION PROTOTYPES
void update_screen(void);
struct timespec diff(struct timespec start, struct timespec end);
#pragma endregion FUNCTION PROTOTYPES

#pragma endregion 	HEAD

#pragma region MAIN FUNCTION
int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();
SDL_SetWindowSize(Window,256,256);
SDL_SetWindowTitle(Window, "Animated Gradient");
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);

screen = SDL_GetWindowSurface(Window);
SDL_FillRect(screen, NULL, 0);
update_screen();
SDL_UpdateWindowSurface(Window);

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
// update_screen();
#pragma region MAIN LOOP
while(running){
	clock_gettime(CLOCK_REALTIME, &start_loop);
	loop_start=SDL_GetTicks();
	#pragma region EVENT LOOP
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
	
	#pragma endregion   EVENT LOOP

	#pragma region RENDERING
	if (!paused){
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
		update_screen();
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
		temp=diff(start,stop);
		SDL_Log("FT: %.2f ms", (float)temp.tv_nsec/1000000 );
	}
	#pragma endregion   RENDERING
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
		// SDL_Log("Oh no, we don't even get 30 FPS!");

	clock_gettime(CLOCK_REALTIME, &stop_loop);
	temp=diff(start_loop,stop_loop);
// 	SDL_Log("LT af wait: %ld", temp.tv_nsec );
}
#pragma endregion   MAIN LOOP

free(pix_map);
exit_();
return EXIT_SUCCESS;

}
#pragma endregion   MAIN FUNCTION

#pragma region FUNCTIONS
void update_screen(void)
{
	screen = SDL_GetWindowSurface(Window);
	pix_map = realloc(pix_map, ww*wh * (sizeof *pix_map));

	#pragma region GRADIENT
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
	Uint32 color;
	for (int i=0;i<ww*wh;i++){
		color=SDL_MapRGBA(screen->format,(int)(pix_map[i].color.r*255), (int)(pix_map[i].color.g*255), (int)(pix_map[i].color.b*255), (int)(pix_map[i].color.a*255));
		unsigned int *ptr = screen->pixels;
		int x = roundf( pix_map[i].pos.x * ((float)ww-1.0) );
		int y = roundf( pix_map[i].pos.y * ((float)wh-1.0) );
		int row = y * (screen->pitch / screen->format->BytesPerPixel);
		ptr[row + x] = color;
	}
	#pragma endregion GRADIENT
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
#pragma endregion   FUNCTIONS
