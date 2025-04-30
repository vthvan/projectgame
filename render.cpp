#include "render.h"

void renderGame(SDL_Renderer* renderer, const GameState& state, const Textures& textures) {
    // Vẽ hình ảnh nền
    SDL_RenderCopy(renderer, textures.background, nullptr, nullptr);

    // Vẽ map
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect tile = {MAP_OFFSET_X + x * TILE_SIZE, MAP_OFFSET_Y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            switch (map[y][x]) {
                case 0: // Đất
                    SDL_RenderCopy(renderer, textures.ground, nullptr, &tile);
                    break;
                case 1: // Tường
                    SDL_RenderCopy(renderer, textures.wall, nullptr, &tile);
                    break;
                case 2: // Xuất phát
                    SDL_RenderCopy(renderer, textures.start, nullptr, &tile);
                    break;
                case 3: // Đích
                    SDL_RenderCopy(renderer, textures.goal, nullptr, &tile);
                    break;
            }
        }
    }

    // Vẽ hình vuông
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &state.square);

    // Cập nhật màn hình
    SDL_RenderPresent(renderer);
}
