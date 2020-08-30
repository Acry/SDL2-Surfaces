#ifndef _HELPER_H_
#define _HELPER_H_

#include <stdlib.h>
#include <SDL2/SDL.h>

extern SDL_Window *Window;
extern SDL_Surface *screen;
extern int pitch;

void init(void);
void exit_(void);
int SDL_CalculatePitch(Uint32, int);
#endif
