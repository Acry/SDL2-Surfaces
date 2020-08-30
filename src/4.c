/* Blit bmp image
 *
 * If you compile and run this you should see a
 * the SDL Logo on the screen
 *
 */
#include "helper.h"

int main(int argc, char *argv[])
{
(void)argc;
(void)argv;

init();

SDL_SetWindowSize(Window,200,200);
SDL_SetWindowTitle(Window, "Blit image");
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
screen=SDL_GetWindowSurface(Window);
// clear background
Uint32 color = SDL_MapRGB(screen->format, 153, 142, 174);
SDL_FillRect(screen, NULL, color);

SDL_Surface  *logo;
logo = SDL_LoadBMP("./assets/gfx/SDL_logo.bmp");

SDL_Rect logo_destRect = {0, 0, logo->w,logo->h};

/*
 *  SDL_BlitSurface
 * 
 *  From SDL_surface.h
 *  You should call SDL_BlitSurface unless you know exactly how SDL
 *  blitting works internally and how to use the other blit functions.
 *
 *  #define SDL_BlitSurface SDL_UpperBlit
 *
 *  This is the public blit function, SDL_BlitSurface, and it performs
 *  rectangle validation and clipping before passing it to SDL_LowerBlit
 *
 *  extern DECLSPEC int SDLCALL SDL_UpperBlit
 *  (SDL_Surface * src, const SDL_Rect * srcrect,
 *   SDL_Surface * dst, SDL_Rect * dstrect);
 */

SDL_BlitSurface(logo,NULL,screen,&logo_destRect);
SDL_UpdateWindowSurface(Window);

SDL_Event event;
int running=1;
while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running=0;
		}
		if(event.type == SDL_WINDOWEVENT){
			if (event.window.event == SDL_WINDOWEVENT_RESIZED){
				screen=SDL_GetWindowSurface(Window);
				SDL_FillRect(screen, NULL, color);
				SDL_BlitSurface(logo,NULL,screen,&logo_destRect);
				SDL_UpdateWindowSurface(Window);
			}
		}
	}
	SDL_Delay(16);

	
}
SDL_FreeSurface(logo);
exit_();
return EXIT_SUCCESS;

}
