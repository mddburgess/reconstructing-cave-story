#include "game.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace {
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;
    const int kBitsPerPixel = 32;
    const int kFps = 60;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);
    window_ = SDL_CreateWindow("Reconstructing Cave Story",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               kScreenWidth,
                               kScreenHeight,
                               SDL_WINDOW_SHOWN);
    eventLoop();
}

Game::~Game() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Game::eventLoop() {
    SDL_Event event;
    bool running = true;
    while (running) {
        const int start_time_ms = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    std::cout << "*" << std::endl;
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }

        update();
        draw();
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        const int delay = 1000 / kFps - elapsed_time_ms;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}

void Game::update() {

}

void Game::draw() {

}
