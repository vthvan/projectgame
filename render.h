#ifndef _RENDER_H
#define _RENDER_H

#include "defs.h"

void renderGame(SDL_Renderer* renderer, const GameState& state, const Textures& textures, int currentLevel);
void renderMenu(SDL_Renderer* renderer,const Textures& textures );
void renderChooseLevel(SDL_Renderer* renderer,const Textures& textures );
void renderLose(SDL_Renderer* renderer, const Textures& textures);
void renderWin(SDL_Renderer* renderer, const Textures& textures);
void renderTime(SDL_Renderer* renderer,const GameState& state);
void renderGuide(SDL_Renderer* renderer,const Textures& textures );

#endif // _RENDER_H
