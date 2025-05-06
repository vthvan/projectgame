#include "game_logic.h"
#include <iostream>
#include <fstream>

using namespace std;

int map[MAP_HEIGHT][MAP_WIDTH];

void initGameState(GameState& state) {
    state.quit = false;
    state.gameWon = false;
    state.gameLost = false;
    state.square = {0, 0, SQUARE_SIZE, SQUARE_SIZE};

    char filename[20];
    snprintf(filename, sizeof(filename), "map/level%d.txt", state.currentLevel);
    if (!loadMapFromFile(filename)) {
        cerr << "Failed to load initial map!" << endl;
        state.quit = true;
        return;
    }

    bool startFound = false;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 2) {
                state.square.x = MAP_OFFSET_X + x * TILE_SIZE + (TILE_SIZE - SQUARE_SIZE) / 2;
                state.square.y = MAP_OFFSET_Y + y * TILE_SIZE + (TILE_SIZE - SQUARE_SIZE) / 2;
                startFound = true;
                break;
            }
        }
        if (startFound) break;
    }
    if (!startFound) {
        cerr << "No start position found in map!" << endl;
        state.quit = true;
    }
}

bool loadMapFromFile(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return false;
    }

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            char c;
            if (!(file >> c)) {
                cerr << "Invalid map format in " << filename << endl;
                file.close();
                return false;
            }
            if (c >= '0' && c <= '3') {
                map[y][x] = c - '0';
            } else {
                cerr << "Invalid character in " << filename <<endl;
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}

void resetGameState(GameState& state) {
    state.gameWon = false;
    state.gameLost = false;
    state.square = {0, 0, SQUARE_SIZE, SQUARE_SIZE};

    // Tìm vị trí xuất phát
    bool startFound = false;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 2) {
                state.square.x = MAP_OFFSET_X + x * TILE_SIZE + (TILE_SIZE - SQUARE_SIZE) / 2;
                state.square.y = MAP_OFFSET_Y + y * TILE_SIZE + (TILE_SIZE - SQUARE_SIZE) / 2;
                startFound = true;
                break;
            }
        }
        if (startFound) break;
    }
    if (!startFound) {
        cerr << "No start position found in map!" << endl;
        state.quit = true;
    }
}

bool checkCollisionWithWall(const SDL_Rect& rect) {

    int corners[4][2] = {
        {rect.x, rect.y},
        {rect.x + rect.w - 1, rect.y},
        {rect.x, rect.y + rect.h - 1},
        {rect.x + rect.w - 1, rect.y + rect.h - 1}
    };

    for (int i = 0; i < 4; i++) {
        int mapX = (corners[i][0] - MAP_OFFSET_X) / TILE_SIZE;
        int mapY = (corners[i][1] - MAP_OFFSET_Y) / TILE_SIZE;
        if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
            if (map[mapY][mapX] == 1) {
                return true;
            }
        }
    }
    return false;
}

bool checkOutOfMap(const SDL_Rect& rect) {
    int mapLeft = MAP_OFFSET_X;
    int mapRight = MAP_OFFSET_X + MAP_WIDTH * TILE_SIZE;
    int mapTop = MAP_OFFSET_Y;
    int mapBottom = MAP_OFFSET_Y + MAP_HEIGHT * TILE_SIZE;

    return (rect.x + rect.w <= mapLeft || rect.x >= mapRight ||
            rect.y + rect.h <= mapTop || rect.y >= mapBottom);
}

bool checkReachedGoal(const SDL_Rect& rect) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 3) {
                SDL_Rect goalRect = {MAP_OFFSET_X + x * TILE_SIZE, MAP_OFFSET_Y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                return SDL_HasIntersection(&rect, &goalRect);
            }
        }
    }
    return false;
}

void handleInput(GameState& state, const Uint8* keyboardState) {
    int newX = state.square.x;
    int newY = state.square.y;

    if (keyboardState[SDL_SCANCODE_UP]) {
        newY -= SPEED;
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        newY += SPEED;
    }
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        newX -= SPEED;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        newX += SPEED;
    }

    SDL_Rect newRect = {newX, newY, SQUARE_SIZE, SQUARE_SIZE};

    if (checkOutOfMap(newRect)) {
        state.gameLost = true;
        cout << "Game Over: You went out of the map!" << endl;
    } else if (!checkCollisionWithWall(newRect)) {
        state.square.x = newX;
        state.square.y = newY;
        if (checkReachedGoal(state.square)) {
            state.gameWon = true;
            cout << "You Win: Reached the destination!" << endl;
        }
    }
}

