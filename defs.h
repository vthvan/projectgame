#ifndef DEFS_H
#define DEFS_H

#include <SDL.h>
#include <SDL_image.h>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int TILE_SIZE = 40;
const int MAP_WIDTH = 15;
const int MAP_HEIGHT = 15;
const int SQUARE_SIZE = 20;
const int SPEED = 5   ;
const int MAP_OFFSET_X = (WINDOW_WIDTH - MAP_WIDTH * TILE_SIZE) / 2;
const int MAP_OFFSET_Y = (WINDOW_HEIGHT - MAP_HEIGHT * TILE_SIZE) / 2 +10;
const int MAX_LEVELS = 10;
const int timeLimits[MAX_LEVELS] = {20000, 7000, 8000, 6000, 13000, 12000, 5000, 7000, 5000, 15000};


extern int map[MAP_HEIGHT][MAP_WIDTH];

enum gameMode{
    menu,
    guide,
    playing,
    levels,
    lose,
    win
} ;

struct GameState {
    SDL_Rect square;
    bool quit;
    bool gameWon;
    bool gameLost;
    int currentLevel;
    gameMode mode;
    Uint64 timeStart;
    int timeLimit;
};


struct Textures {
    SDL_Texture* background;
    SDL_Texture* menu;
    SDL_Texture* ground;
    SDL_Texture* wall;
    SDL_Texture* start;
    SDL_Texture* goal;
    SDL_Texture* lvTextures[MAX_LEVELS];
    SDL_Texture* playButton;
    SDL_Texture* levelsButton;
    SDL_Texture* lose;
    SDL_Texture* win;
    SDL_Texture* homeButton;
    SDL_Texture* nextButton;
    SDL_Texture* trap;
    SDL_Texture* inforButton;
    SDL_Texture* guide;

};

#endif
