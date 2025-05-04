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

    // Khởi tạo SDL
    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    Textures textures = loadTextures(renderer);
    if (!textures.background || !textures.ground || !textures.wall || !textures.start || !textures.goal) {
        cleanupSDL(window, renderer, textures);
        return 1;
    }

    // Khởi tạo trạng thái game
    GameState state;
     state.quit = false;
    state.gameWon = false;
    state.gameLost = false;
    state.currentLevel = 1;
    state.mode = menu;

    // Vòng lặp chính
    SDL_Event e;
    while (!state.quit) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                state.quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN ) {
                // Kiểm tra click nút Play
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (state.mode == menu)
                {
                    SDL_Rect playRect = {WINDOW_WIDTH/2 - 81 +50, WINDOW_HEIGHT/2 -50, 162, 162};
                if (x >= playRect.x && x <= playRect.x + playRect.w &&
                    y >= playRect.y && y <= playRect.y + playRect.h) {
                    state.mode = playing;
                    initGameState(state); // Khởi tạo game khi nhấn Play
                }

                SDL_Rect levelsRect = {(WINDOW_WIDTH/2 - 81 +50)-67,(WINDOW_HEIGHT/2 -30)+172, 297, 122};
                if (x >= levelsRect.x && x <= levelsRect.x + levelsRect.w &&
                    y >= levelsRect.y && y <= levelsRect.y + levelsRect.h) {
                    state.mode = levels;
            }
                }

         else if (state.mode == levels) {
                    // Kiểm tra click nút level
                    for (int i = 0; i < MAX_LEVELS; i++) {
                        int row = i / 3;
                        int col = i % 3;
                        SDL_Rect levelRect = {150 + col * (268 + 50), 200 + row * (92 + 50), 268, 92};
                        if (x >= levelRect.x && x <= levelRect.x + levelRect.w &&
                            y >= levelRect.y && y <= levelRect.y + levelRect.h) {
                            state.mode = playing;
                            state.currentLevel = i + 1; // Chọn level tương ứng
                            initGameState(state);
                            break;
                        }
                    }
                }
            }
        }

         if (state.mode == menu) {
            // Vẽ menu
            renderMenu(renderer, textures);
        }else if (state.mode == levels)
        {
            renderChooseLevel(renderer,textures);
        }
         else if (state.mode == playing)
        {
            // Lấy trạng thái bàn phím
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        handleInput(state,keyboardState);

        renderGame(renderer,state,textures,state.currentLevel);

        // Chuyển level nếu thắng
        if (state.gameWon && state.currentLevel < MAX_LEVELS) {
            state.currentLevel++;
            char filename[20];
            snprintf(filename, sizeof(filename), "map/level%d.txt", state.currentLevel);
            if (loadMapFromFile(filename)) {
                resetGameState(state);
            } else {
                cerr << "Failed to load level " << state.currentLevel << endl;
                state.quit = true;
            }
        } else if (state.gameWon && state.currentLevel == MAX_LEVELS) {
            cerr << "Congratulations! You completed all levels!" << endl;
            state.quit = true;
        }

        // Reset nếu thua
        if (state.gameLost) {
            cerr << "Game over " << endl;
            state.quit = true;
        }


        }

        // Delay để kiểm soát FPS
        SDL_Delay(16); // ~60 FPS


    }

    cleanupSDL(window,renderer,textures);

    return 0;
}
