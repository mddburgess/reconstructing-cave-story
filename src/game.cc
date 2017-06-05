#include "game.h"
#include <SDL2/SDL.h>
#include "graphics.h"
#include "animated_sprite.h"
#include "input.h"

namespace {
    const int kFps = 60;
}

// static
int Game::kTileSize = 32;

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
    Input input;
    SDL_Event event;

    sprite_ = std::make_unique<AnimatedSprite>("content/MyChar.bmp",
                                               graphics.getRenderer(),
                                               0, 0, kTileSize, kTileSize,
                                               15, 3);

    bool running = true;
    int last_update_time = SDL_GetTicks();
    while (running) {
        const int start_time_ms = SDL_GetTicks();
        input.beginNewFrame();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    input.keyDownEvent(event);
                    break;
                case SDL_KEYUP:
                    input.keyUpEvent(event);
                    break;
                default:
                    break;
            }
        }

        if (input.wasKeyPressed(SDLK_ESCAPE)) {
            running = false;
        }

        const int current_time_ms = SDL_GetTicks();
        update(current_time_ms - last_update_time);
        last_update_time = current_time_ms;

        draw(graphics);
        const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        const int delay = 1000 / kFps - elapsed_time_ms;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}

void Game::update(int elapsed_time_ms) {
    sprite_->update(elapsed_time_ms);
}

void Game::draw(Graphics& graphics) {
    graphics.clear();
    sprite_->draw(graphics, 320, 240);
    graphics.flip();
}
