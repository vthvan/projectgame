#include "sdl.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;


bool initSDL(SDL_Window** window, SDL_Renderer** renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cerr << "SDL_image could not initialize! IMG_Error: " << IMG_GetError() << endl;
        SDL_Quit();
        return false;
    }

    * window = SDL_CreateWindow("MAZE",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
    if (*window == nullptr) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    * renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;

}
Textures loadTextures(SDL_Renderer* renderer)
{
   Textures textures = {nullptr, nullptr, nullptr, nullptr, nullptr};

    SDL_Surface* bgSurface = IMG_Load("pic/background.jpg");
    if (bgSurface) {
        textures.background = SDL_CreateTextureFromSurface(renderer, bgSurface);
        SDL_FreeSurface(bgSurface);
        if (!textures.background) {
            cerr << "Unable to create background texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load background.jpg! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* menuSurface = IMG_Load("pic/menu.png");
    if (menuSurface) {
        textures.menu = SDL_CreateTextureFromSurface(renderer, menuSurface);
        SDL_FreeSurface(menuSurface);
        if (!textures.menu) {
            cerr << "Unable to create menu texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load menu.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* groundSurface = IMG_Load("pic/ground.png");
    if (groundSurface) {
        textures.ground = SDL_CreateTextureFromSurface(renderer, groundSurface);
        SDL_FreeSurface(groundSurface);
        if (!textures.ground) {
            cerr << "Unable to create ground texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load ground.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* wallSurface = IMG_Load("pic/wall.png");
    if (wallSurface) {
        textures.wall = SDL_CreateTextureFromSurface(renderer, wallSurface);
        SDL_FreeSurface(wallSurface);
        if (!textures.wall) {
            cerr << "Unable to create wall texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load wall.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* startSurface = IMG_Load("pic/start.png");
    if (startSurface) {
        textures.start = SDL_CreateTextureFromSurface(renderer, startSurface);
        SDL_FreeSurface(startSurface);
        if (!textures.start) {
            cerr << "Unable to create start texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load start.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* goalSurface = IMG_Load("pic/door.png");
    if (goalSurface) {
        textures.goal = SDL_CreateTextureFromSurface(renderer, goalSurface);
        SDL_FreeSurface(goalSurface);
        if (!textures.goal) {
            cerr << "Unable to create door texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load door.png! IMG_Error: " << IMG_GetError() << endl;
    }

    for (int i = 0; i < MAX_LEVELS; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "pic/lv%d.png", i + 1);
        SDL_Surface* levelSurface = IMG_Load(filename);
        if (levelSurface) {
            textures.lvTextures[i] = SDL_CreateTextureFromSurface(renderer, levelSurface);
            SDL_FreeSurface(levelSurface);
            if (!textures.lvTextures[i]) {
                cerr << "Unable to create texture for " << filename << "! SDL_Error: " << SDL_GetError() << endl;
            }
        } else {
            cerr << "Unable to load " << filename << "! IMG_Error: " << IMG_GetError() << endl;
        }
    }
    SDL_Surface* playSurface = IMG_Load("pic/playbutton.png");
    if (playSurface) {
        textures.playButton = SDL_CreateTextureFromSurface(renderer, playSurface);
        SDL_FreeSurface(playSurface);
        if (!textures.playButton) {
            cerr << "Unable to create play button texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load playbutton.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* levelsSurface = IMG_Load("pic/levelsbutton.png");
    if (levelsSurface) {
        textures.levelsButton = SDL_CreateTextureFromSurface(renderer, levelsSurface);
        SDL_FreeSurface(levelsSurface);
        if (!textures.levelsButton) {
            cerr << "Unable to create levels button texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load levelsbutton.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* loseSurface = IMG_Load("pic/lose.png");
    if (loseSurface) {
        textures.lose = SDL_CreateTextureFromSurface(renderer, loseSurface);
        SDL_FreeSurface(loseSurface);
        if (!textures.lose) {
            cerr << "Unable to create lose texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load lose.png! IMG_Error: " << IMG_GetError() << endl;
    }

     SDL_Surface* homeSurface = IMG_Load("pic/homebutton.png");
    if (homeSurface) {
        textures.homeButton = SDL_CreateTextureFromSurface(renderer, homeSurface);
        SDL_FreeSurface(homeSurface);
        if (!textures.homeButton) {
            cerr << "Unable to create home button texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load homebutton.png! IMG_Error: " << IMG_GetError() << endl;
    }

     SDL_Surface* winSurface = IMG_Load("pic/win.png");
    if (winSurface) {
        textures.win = SDL_CreateTextureFromSurface(renderer, winSurface);
        SDL_FreeSurface(winSurface);
        if (!textures.win) {
            cerr << "Unable to create win texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load win.png! IMG_Error: " << IMG_GetError() << endl;
    }

    SDL_Surface* nextSurface = IMG_Load("pic/nextbutton.png");
    if (nextSurface) {
        textures.nextButton = SDL_CreateTextureFromSurface(renderer, nextSurface);
        SDL_FreeSurface(nextSurface);
        if (!textures.nextButton) {
            cerr << "Unable to create next texture! SDL_Error: " << SDL_GetError() << endl;
        }
    } else {
        cerr << "Unable to load nextbutton.png! IMG_Error: " << IMG_GetError() << endl;
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
        SDL_DestroyTexture(textures.lose);
        for (int i = 0; i < MAX_LEVELS; i++) {
        SDL_DestroyTexture(textures.lvTextures[i]);
    }
        SDL_DestroyTexture(textures.playButton);
        SDL_DestroyTexture(textures.levelsButton);
        SDL_DestroyTexture(textures.homeButton);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
}

