#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <SDL2/SDL.h>

/* candy bar, port from SDL1 -> SDL2
 * http://demo-effects.sourceforge.net/
 */

#define SCREEN_WIDTH          500
#define SCREEN_HEIGHT         (SCREEN_WIDTH/16*9)

SDL_Window  *Window         = NULL;
SDL_Surface *screen         = NULL;
SDL_Surface *temp_surface   = NULL;
SDL_Surface *copper_surface = NULL;

int pitch;

void createCandybar(void);
int SDL_CalculatePitch(Uint32, int);

int main( int argc, char* argv[] )
{
  (void)argc;
  (void)argv;

  Window = SDL_CreateWindow("Retro - Amiga Candybar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  screen = SDL_GetWindowSurface(Window);
  pitch  = SDL_CalculatePitch(screen->format, screen->w);
  SDL_FillRect(screen, NULL, 0);
  Uint32 format = SDL_GetWindowPixelFormat(Window);
  temp_surface = SDL_CreateRGBSurfaceWithFormat(0,SCREEN_WIDTH,128, 24, format);

  SDL_Rect crect1 = {0, 1, SCREEN_WIDTH, 127};
  SDL_Rect crect2 = {0, 0, SCREEN_WIDTH, 127};
  SDL_Rect crect3 = {0, 127, SCREEN_WIDTH, 1};
  SDL_Rect crect4 = {0, (SCREEN_HEIGHT >> 1) - 64, SCREEN_WIDTH, 1};
  SDL_Color col;

  unsigned int temp;
  int scanline;
  SDL_Event event;
  int running=1;

  createCandybar();

  while( running ){

    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running=0;
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
              running =0;
              break;
          case SDLK_s:
              SDL_SaveBMP(screen, "9_out.png");
              break;
          default:
              break;
        }
      }
    }

    /* scroll bar */
    temp = *(unsigned int*)copper_surface->pixels;
    SDL_BlitSurface(copper_surface, &crect1, copper_surface, &crect2);
    SDL_FillRect(copper_surface, &crect3, temp);

    /* shade bar */
    scanline = 0;
    for (int i = 0; i < 128; ++i){
      temp = *((unsigned int*)copper_surface->pixels + scanline);
      SDL_GetRGB(temp, screen->format, &col.r, &col.g, &col.b);
      
      if (i < 64){
          col.r &= i << 2;
          col.b &= i << 2;
          col.g &= i << 2;
      }else{
          col.r &= 0xFF - (i << 2);
          col.b &= 0xFF - (i << 2);
          col.g &= 0xFF - (i << 2);	    
      }
      temp = SDL_MapRGB(screen->format, col.r, col.g, col.b);
      SDL_FillRect(screen, &crect4, temp);
      crect4.y++;
      scanline += pitch;
    }
    crect4.y = (SCREEN_HEIGHT >> 1) - 64;
    SDL_Delay(16);
    SDL_UpdateWindowSurface(Window);
  }

  SDL_FreeSurface(copper_surface);
  SDL_DestroyWindow(Window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

void createCandybar(void){

Uint32 format = SDL_GetWindowPixelFormat(Window);
copper_surface = SDL_CreateRGBSurfaceWithFormat(0,SCREEN_WIDTH,128, 24, format);

Uint32 white = SDL_MapRGB(copper_surface->format, 0xFF, 0xFF, 0xFF);
Uint32 red = SDL_MapRGB(copper_surface->format, 0xFF, 0, 0);

SDL_Rect r = {0, 0, SCREEN_WIDTH, 16};
SDL_FillRect(copper_surface, &r, red);

r.y += 16;
SDL_FillRect(copper_surface, &r, white);

r.y += 16;
SDL_FillRect(copper_surface, &r, red);

r.y += 16;
SDL_FillRect(copper_surface, &r, white);

r.y += 16;
SDL_FillRect(copper_surface, &r, red);

r.y += 16;
SDL_FillRect(copper_surface, &r, white);

r.y += 16;
SDL_FillRect(copper_surface, &r, red);

r.y += 16;
SDL_FillRect(copper_surface, &r, white);

}

int SDL_CalculatePitch(Uint32 format, int width)
{
    int pitch;
    if (SDL_ISPIXELFORMAT_FOURCC(format) || SDL_BITSPERPIXEL(format) >= 8) {
        pitch = (width * SDL_BYTESPERPIXEL(format));
    } else {
        pitch = ((width * SDL_BITSPERPIXEL(format)) + 7) / 8;
    }
    pitch = (pitch + 3) & ~3;   /* 4-byte aligning for speed */
    return pitch;
}

