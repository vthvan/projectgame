#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 800;
const int TILE_SIZE = 40;
const int MAP_WIDTH = 15; // 600/40
const int MAP_HEIGHT = 15;
const int SQUARE_SIZE = 25;
const int SPEED = 5   ;

// Căn giữa map 600x600 trong cửa sổ 800x600
const int MAP_OFFSET_X = (WINDOW_WIDTH - MAP_WIDTH * TILE_SIZE) / 2; // 100
const int MAP_OFFSET_Y = (WINDOW_HEIGHT - MAP_HEIGHT * TILE_SIZE) / 2; // 0

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main(int argc, char* argv[]) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow("MAZE",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Tạo renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Tải hình ảnh nền
    SDL_Surface* bgSurface = IMG_Load("background.jpg");
    if (bgSurface == nullptr) {
        std::cerr << "Unable to load image! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    if (bgTexture == nullptr) {
        std::cerr << "Unable to create texture! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Tải hình ảnh cho các ô
    SDL_Surface* groundSurface = IMG_Load("ground.png");
    SDL_Surface* wallSurface = IMG_Load("wall.png");
    SDL_Surface* startSurface = IMG_Load("goal.png");
    SDL_Surface* goalSurface = IMG_Load("goal.png");
    if (!groundSurface || !wallSurface || !startSurface || !goalSurface) {
        std::cerr << "Unable to load tile images! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Texture* groundTexture = SDL_CreateTextureFromSurface(renderer, groundSurface);
    SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(renderer, wallSurface);
    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    SDL_Texture* goalTexture = SDL_CreateTextureFromSurface(renderer, goalSurface);
    SDL_FreeSurface(groundSurface);
    SDL_FreeSurface(wallSurface);
    SDL_FreeSurface(startSurface);
    SDL_FreeSurface(goalSurface);
    if (!groundTexture || !wallTexture || !startTexture || !goalTexture) {
        std::cerr << "Unable to create tile textures! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyTexture(groundTexture);
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(goalTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

       // Tìm vị trí xuất phát
    SDL_Rect square = {0, 0, SQUARE_SIZE, SQUARE_SIZE};
    bool startFound = false;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (map[y][x] == 2) {
                square.x = MAP_OFFSET_X + x * TILE_SIZE + (TILE_SIZE - SQUARE_SIZE) / 2;
                square.y = MAP_OFFSET_Y + y * TILE_SIZE + (TILE_SIZE - SQUARE_SIZE) / 2;
                startFound = true;
                break;
            }
        }
        if (startFound) break;
    }
    if (!startFound) {
        std::cerr << "No start position found in map!" << std::endl;
        SDL_DestroyTexture(bgTexture);
        SDL_DestroyTexture(groundTexture);
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyTexture(startTexture);
        SDL_DestroyTexture(goalTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    bool gameWon = false;
    bool gameLost = false;
    SDL_Event e;



    // Vòng lặp chính
    while (!quit && !gameWon && !gameLost) {
        // Xử lý sự kiện
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Lấy trạng thái bàn phím
        const Uint8* state = SDL_GetKeyboardState(nullptr);

        // Tính toán vị trí mới của hình vuông
        int newX = square.x;
        int newY = square.y;

        if (state[SDL_SCANCODE_UP]) {
            newY -= SPEED;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            newY += SPEED;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            newX -= SPEED;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            newX += SPEED;
        }

        // Kiểm tra va chạm và điều kiện trò chơi
        int mapX = (newX - MAP_OFFSET_X) / TILE_SIZE;
        int mapY = (newY - MAP_OFFSET_Y) / TILE_SIZE;
        bool canMove = true;

        // Kiểm tra ra khỏi map
        if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
            gameLost = true;
            std::cout << "Game Over: You went out of the map!" << std::endl;
        }
        // Kiểm tra va chạm với tường
        else if (map[mapY][mapX] == 1) {
            canMove = false;
        }
        // Kiểm tra chạm đích
        else if (map[mapY][mapX] == 3) {
            gameWon = true;
            std::cout << "You Win: Reached the destination!" << std::endl;
        }

        // Cập nhật vị trí nếu có thể di chuyển
        if (canMove) {
            square.x = newX;
            square.y = newY;
        }




        // Vẽ hình ảnh nền
        SDL_RenderCopy(renderer, bgTexture, nullptr, nullptr);

        // Vẽ map
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                SDL_Rect tile = {MAP_OFFSET_X + x * TILE_SIZE, MAP_OFFSET_Y + y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                switch (map[y][x]) {
                    case 0: // Đất
                        SDL_RenderCopy(renderer, groundTexture, nullptr, &tile);
                        break;
                    case 1: // Tường
                        SDL_RenderCopy(renderer, wallTexture, nullptr, &tile);
                        break;
                    case 2: // Xuất phát
                        SDL_RenderCopy(renderer, startTexture, nullptr, &tile);
                        break;
                    case 3: // Đích
                        SDL_RenderCopy(renderer, goalTexture, nullptr, &tile);
                        break;
                }
            }
        }

        // Vẽ hình vuông
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &square);

        // Cập nhật màn hình
        SDL_RenderPresent(renderer);

        // Delay để kiểm soát FPS
        SDL_Delay(16); // ~60 FPS

    }


    // Giải phóng tài nguyên
     SDL_DestroyTexture(bgTexture);
    SDL_DestroyTexture(groundTexture);
    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(startTexture);
    SDL_DestroyTexture(goalTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
