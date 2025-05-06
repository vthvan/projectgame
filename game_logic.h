#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "defs.h"

void initGameState(GameState& state);
void handleInput(GameState& state, const Uint8* keyboardState);
bool checkReachedGoal(const SDL_Rect& rect);
bool checkOutOfMap(const SDL_Rect& rect);
bool checkCollisionWithWall(const SDL_Rect& rect);
bool loadMapFromFile(const char* filename);
bool checkReachedTrap(const SDL_Rect& rect);
void checkTime(GameState& state);
#endif
