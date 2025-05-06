#include "render.h"
#include "sdl.h"

void renderGame(SDL_Renderer* renderer, const GameState& state, const Textures& textures, int currentLevel) {

    SDL_RenderCopy(renderer, textures.background, nullptr, nullptr);

    Uint64 currentTime = SDL_GetTicks64();
    bool showTrap = (currentTime - state.timeStart) < 3000;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile = {MAP_OFFSET_X + x * TILE_SIZE, MAP_OFFSET_Y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            switch (map[y][x]) {
                case 0:
                    SDL_RenderCopy(renderer, textures.ground, nullptr, &tile);
                    break;
                case 1:
                    SDL_RenderCopy(renderer, textures.wall, nullptr, &tile);
                    break;
                case 2:
                    SDL_RenderCopy(renderer, textures.start, nullptr, &tile);
                    break;
                case 3:
                    SDL_RenderCopy(renderer, textures.goal, nullptr, &tile);
                    break;
                case 4:
                    if (showTrap) {
                         SDL_RenderCopy(renderer, textures.trap, nullptr, &tile);
                    }
                    else  SDL_RenderCopy(renderer, textures.ground, nullptr, &tile);
                    break;
            }
        }
    }


    SDL_SetRenderDrawColor(renderer, 255, 30, 80, 255);
    SDL_RenderFillRect(renderer, &state.square);


    if (currentLevel >= 1 && currentLevel <= MAX_LEVELS && textures.lvTextures[currentLevel - 1]) {
        SDL_Rect levelRect = {WINDOW_WIDTH/2 - 134, 10, 268, 92};
        SDL_RenderCopy(renderer, textures.lvTextures[currentLevel - 1], nullptr, &levelRect);
    }

    if (textures.homeButton) {
        SDL_Rect homeRect = {10,10, 70, 70};
        SDL_RenderCopy(renderer, textures.homeButton, nullptr, &homeRect);
    }

        renderTime(renderer, state );

    SDL_RenderPresent(renderer);
}

void renderMenu(SDL_Renderer* renderer, const Textures& textures) {

    SDL_RenderCopy(renderer, textures.menu, nullptr, nullptr);


    if (textures.playButton) {
        SDL_Rect playRect = {WINDOW_WIDTH/2 - 81 +50, WINDOW_HEIGHT/2 -30, 162, 162};
        SDL_RenderCopy(renderer, textures.playButton, nullptr, &playRect);
    }

    if (textures.levelsButton) {
        SDL_Rect levelsRect = {(WINDOW_WIDTH/2 - 81 +50)-67,(WINDOW_HEIGHT/2 -30)+172, 297, 122};
        SDL_RenderCopy(renderer, textures.levelsButton, nullptr, &levelsRect);
    }

    if (textures.inforButton) {
        SDL_Rect inforRect = {20,20, 100, 100};
        SDL_RenderCopy(renderer, textures.inforButton, nullptr, &inforRect);
    }

    SDL_RenderPresent(renderer);
}

void renderChooseLevel(SDL_Renderer* renderer, const Textures& textures)
{
    SDL_RenderCopy(renderer, textures.background, nullptr, nullptr);

    for (int i = 0; i < MAX_LEVELS; i++) {
        int row = i / 3;
        int col = i % 3;
        SDL_Rect levelRect = {150 + col * (268 + 50), 150 + row * (92 + 50), 268, 92};
        if (textures.lvTextures[i]) {
            SDL_RenderCopy(renderer, textures.lvTextures[i], nullptr, &levelRect);
        }
    }

    SDL_RenderPresent(renderer);
}

void renderLose(SDL_Renderer* renderer, const Textures& textures) {

    SDL_RenderCopy(renderer, textures.lose, nullptr, nullptr);

    if (textures.homeButton) {
        SDL_Rect homeRect = {WINDOW_WIDTH/2 - 65, WINDOW_HEIGHT/2 + 80, 147, 147};
        SDL_RenderCopy(renderer, textures.homeButton, nullptr, &homeRect);
    }

    SDL_RenderPresent(renderer);
}

void renderWin(SDL_Renderer* renderer, const Textures& textures){
     SDL_RenderCopy(renderer, textures.win, nullptr, nullptr);

     if (textures.homeButton) {
        SDL_Rect homeRect = {WINDOW_WIDTH/2 -150 , WINDOW_HEIGHT/2 +70 , 147, 147};
        SDL_RenderCopy(renderer, textures.homeButton, nullptr, &homeRect);
    }

     if (textures.nextButton) {
        SDL_Rect nextRect = {WINDOW_WIDTH/2 +50 , WINDOW_HEIGHT/2 +70, 102, 147};
        SDL_RenderCopy(renderer, textures.nextButton,nullptr, &nextRect);
     }

     SDL_RenderPresent(renderer);
}

void renderTime(SDL_Renderer* renderer, const GameState& state) {
    Uint64 currentTime = SDL_GetTicks64();
    int timeElapsed = currentTime - state.timeStart;
    float timeRatio = 1.0f - (float)timeElapsed / state.timeLimit;
    if (timeRatio < 0) timeRatio = 0;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect bgRect = {940 , 50, 200, 20};
    SDL_RenderFillRect(renderer, &bgRect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect barRect = {940, 50, (int)(200 * timeRatio), 20};
    SDL_RenderFillRect(renderer, &barRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &bgRect);
}

void renderGuide(SDL_Renderer* renderer,const Textures& textures )
{
    SDL_RenderCopy(renderer, textures.background, nullptr, nullptr);

    SDL_Rect guideRect = {WINDOW_WIDTH/2 -350,WINDOW_HEIGHT/2 -350, 782, 659};
    SDL_RenderCopy(renderer, textures.guide, nullptr, &guideRect);

    if (textures.inforButton) {
        SDL_Rect inforRect = {20,20, 100, 100};
        SDL_RenderCopy(renderer, textures.inforButton, nullptr, &inforRect);
    }

    SDL_RenderPresent(renderer);
}
