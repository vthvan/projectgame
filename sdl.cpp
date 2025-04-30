#include "sdl.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


bool initSDL(SDL_Window** window, SDL_Renderer** renderer)
{
     // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    //tao cua so
    * window = SDL_CreateWindow("MAZE",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
    if (*window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    //tao renderer
    * renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;

}
Textures loadTextures(SDL_Renderer* renderer)
{
   Textures textures = {nullptr, nullptr, nullptr, nullptr, nullptr};

    SDL_Surface* bgSurface = IMG_Load("background.jpg");
    if (bgSurface) {
        textures.background = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
        if (!textures.background) {
            std::cerr << "Unable to create background texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Unable to load background.jpg! IMG_Error: " << IMG_GetError() << std::endl;
    }

    SDL_Surface* groundSurface = IMG_Load("ground.png");
    if (groundSurface) {
        textures.ground = SDL_CreateTextureFromSurface(renderer, groundSurface);
        SDL_FreeSurface(groundSurface);
        if (!textures.ground) {
            std::cerr << "Unable to create ground texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Unable to load ground.png! IMG_Error: " << IMG_GetError() << std::endl;
    }

    SDL_Surface* wallSurface = IMG_Load("wall.png");
    if (wallSurface) {
        textures.wall = SDL_CreateTextureFromSurface(renderer, wallSurface);
        SDL_FreeSurface(wallSurface);
        if (!textures.wall) {
            std::cerr << "Unable to create wall texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Unable to load wall.png! IMG_Error: " << IMG_GetError() << std::endl;
    }

    SDL_Surface* startSurface = IMG_Load("goal.png");
    if (startSurface) {
        textures.start = SDL_CreateTextureFromSurface(renderer, startSurface);
        SDL_FreeSurface(startSurface);
        if (!textures.start) {
            std::cerr << "Unable to create start texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Unable to load start.png! IMG_Error: " << IMG_GetError() << std::endl;
    }

    SDL_Surface* goalSurface = IMG_Load("door.png");
    if (goalSurface) {
        textures.goal = SDL_CreateTextureFromSurface(renderer, goalSurface);
        SDL_FreeSurface(goalSurface);
        if (!textures.goal) {
            std::cerr << "Unable to create goal texture! SDL_Error: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << "Unable to load goal.png! IMG_Error: " << IMG_GetError() << std::endl;
    }

    return textures;

}
void cleanupSDL(SDL_Window* window, SDL_Renderer* renderer, Textures textures)
{
     SDL_DestroyTexture(textures.background);
        SDL_DestroyTexture(textures.ground);
        SDL_DestroyTexture(textures.wall);
        SDL_DestroyTexture(textures.start);
        SDL_DestroyTexture(textures.goal);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
}

