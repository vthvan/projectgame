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
    initGameState(state);

    // Vòng lặp chính
    SDL_Event e;
    while (!state.quit) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                state.quit = true;
            }
        }

        // Lấy trạng thái bàn phím
        const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
        handleInput(state,keyboardState);

        renderGame(renderer,state,textures);

        // Chuyển level nếu thắng
        if (state.gameWon && state.currentLevel < MAX_LEVELS) {
            state.currentLevel++;
            char filename[20];
            snprintf(filename, sizeof(filename), "level%d.txt", state.currentLevel);
            if (loadMapFromFile(filename)) {
                resetGameState(state);
            } else {
                cerr << "Failed to load level " << state.currentLevel << endl;
                state.quit = true;
            }
        } else if (state.gameWon && state.currentLevel == MAX_LEVELS) {
            cout << "Congratulations! You completed all levels!" << endl;
            state.quit = true;
        }

        // Reset nếu thua
        if (state.gameLost) {
            resetGameState(state);
        }


        // Delay để kiểm soát FPS
        SDL_Delay(16); // ~60 FPS

    }

    cleanupSDL(window,renderer,textures);

    return 0;
}
