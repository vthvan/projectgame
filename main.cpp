#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "sdl.h"
#include "render.h"
#include "defs.h"
#include "game_logic.h"

using namespace std;


int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    Textures textures = loadTextures(renderer);
    if (!textures.background || !textures.ground || !textures.wall || !textures.start || !textures.goal) {
        cleanupSDL(window, renderer, textures);
        return 1;
    }


    GameState state;
     state.quit = false;
    state.gameWon = false;
    state.gameLost = false;
    state.currentLevel = 1;
    state.mode = menu;



    SDL_Event e;
    while (!state.quit) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                state.quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN ) {
                if (state.mode == menu)
                {
                    SDL_Rect playRect = {WINDOW_WIDTH/2 - 81 +50, WINDOW_HEIGHT/2 -50, 162, 162};
                if (x >= playRect.x && x <= playRect.x + playRect.w &&
                    y >= playRect.y && y <= playRect.y + playRect.h) {
                    state.mode = playing;
                    state.currentLevel = 1;
                    initGameState(state);
                }

                SDL_Rect levelsRect = {(WINDOW_WIDTH/2 - 81 +50)-67,(WINDOW_HEIGHT/2 -30)+172, 297, 122};
                if (x >= levelsRect.x && x <= levelsRect.x + levelsRect.w &&
                    y >= levelsRect.y && y <= levelsRect.y + levelsRect.h) {
                    state.mode = levels;
            }
                }

         else if (state.mode == levels) {
                    for (int i = 0; i < MAX_LEVELS; i++) {
                        int row = i / 3;
                        int col = i % 3;
                        SDL_Rect levelRect = {150 + col * (268 + 50), 150 + row * (92 + 50), 268, 92};
                        if (x >= levelRect.x && x <= levelRect.x + levelRect.w &&
                            y >= levelRect.y && y <= levelRect.y + levelRect.h) {
                            state.mode = playing;
                            state.currentLevel = i + 1;
                            initGameState(state);
                            break;
                        }
                    }
                }
        else if (state.mode == playing){
            SDL_Rect homeRect ={10,10, 70, 70};
            if (x >= homeRect.x && x <= homeRect.x + homeRect.w &&
                y >= homeRect.y && y <= homeRect.y + homeRect.h) {
                state.mode = menu;
                }

        }
        else if (state.mode == lose) {
                SDL_Rect homeRect = {WINDOW_WIDTH/2 - 65, WINDOW_HEIGHT/2 + 80, 147, 147};
                if (x >= homeRect.x && x <= homeRect.x + homeRect.w &&
                    y >= homeRect.y && y <= homeRect.y + homeRect.h) {
                    state.mode = menu;
            }
        }
        else if (state.mode == win) {
            SDL_Rect homeRect ={WINDOW_WIDTH/2 -150 , WINDOW_HEIGHT/2 +70 , 147, 147};
            if (x >= homeRect.x && x <= homeRect.x + homeRect.w &&
                y >= homeRect.y && y <= homeRect.y + homeRect.h) {
                state.mode = menu;
                }

            SDL_Rect nextRect ={WINDOW_WIDTH/2 +50 , WINDOW_HEIGHT/2 +70 , 102, 147};
            if (x >= nextRect.x && x <= nextRect.x + nextRect.w &&
                y >= nextRect.y && y <= nextRect.y + nextRect.h) {
                 if (state.currentLevel < MAX_LEVELS) {
                state.currentLevel++;
                char filename[20];
                snprintf(filename, sizeof(filename), "map/level%d.txt", state.currentLevel);
                if (loadMapFromFile(filename)) {
                state.mode = playing;
                resetGameState(state);
            } else {
                cerr << "Failed to load level " << state.currentLevel << endl;
                state.quit = true;
            }
        } else if (state.currentLevel == MAX_LEVELS) {
            cerr << "Congratulations! You completed all levels!" << endl;
            state.quit = true;
        }
        }
        }
    }
}

         if (state.mode == menu) {
            renderMenu(renderer, textures);
        }
        else if (state.mode == levels)
        {
            renderChooseLevel(renderer,textures);
        }
        else if (state.mode == win) {
            renderWin(renderer,textures);
        }
         else if (state.mode == playing)
        {
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        handleInput(state,keyboardState);

        renderGame(renderer,state,textures,state.currentLevel);

        if (state.gameLost){
            state.mode = lose;
        }

        if (state.gameWon ) {
                state.mode = win;

        }
        } else if (state.mode == lose) {
            renderLose(renderer,textures);
            cerr << "Game over " << endl;
          //  state.quit = true;
        }

        SDL_Delay(16);

    }
    cleanupSDL(window,renderer,textures);

    return 0;
}
