#ifndef _SDL__H
#define _SDL__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

bool initSDL(SDL_Window** window, SDL_Renderer** renderer);
Textures loadTextures(SDL_Renderer* renderer);
void cleanupSDL(SDL_Window* window, SDL_Renderer* renderer, Textures textures);

#endif
