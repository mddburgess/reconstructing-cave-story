#include "game.h"
#include <SDL2/SDL.h>
#include "graphics.h"
#include "sprite.h"

namespace {
    const int kFps = 60;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_ShowCursor(SDL_DISABLE);
    eventLoop();
}

Game::~Game() {
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;
    SDL_Event event;

    sprite_ = std::make_unique<Sprite>("content/MyChar.bmp",
                                       graphics.getRenderer(),
                                       0, 0, 32, 32);

    bool running = true;
    while (running) {
        const int start_time_ms = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }

        update();
        draw(graphics);
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        const int delay = 1000 / kFps - elapsed_time_ms;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}

void Game::update() {

}

void Game::draw(Graphics& graphics) {
    graphics.clear();
    sprite_->draw(graphics, 320, 240);
    graphics.flip();
}
