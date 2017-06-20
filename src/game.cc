#include "game.h"
#include <SDL2/SDL.h>
#include "graphics.h"
#include "player.h"
#include "input.h"
#include "map.h"
#include "first_cave_bat.h"

namespace {
    const units::FPS kFps = 60;
    const units::MS kMaxFrameTime = 5 * 1000 / 60;
}

// static
units::Tile Game::kScreenWidth = 20;
units::Tile Game::kScreenHeight = 15;

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    eventLoop();
}

Game::~Game() {
    SDL_Quit();
}

void Game::eventLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;

    player_ = std::make_unique<Player>(graphics,
                                       units::tileToGame(kScreenWidth / 2),
                                       units::tileToGame(kScreenHeight / 2));
    bat_ = std::make_unique<FirstCaveBat>(graphics,
                                          units::tileToGame(7),
                                          units::tileToGame(kScreenHeight / 2 + 1));
    map_.reset(Map::createTestMap(graphics));

    bool running = true;
    units::MS last_update_time = SDL_GetTicks();
    while (running) {
        const units::MS start_time_ms = SDL_GetTicks();
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

        // Player horizontal movement
        if (input.isKeyHeld(SDLK_LEFT) == input.isKeyHeld(SDLK_RIGHT)) {
            player_->stopMoving();
        } else if (input.isKeyHeld(SDLK_LEFT)) {
            player_->startMovingLeft();
        } else if (input.isKeyHeld(SDLK_RIGHT)) {
            player_->startMovingRight();
        }

        if (input.isKeyHeld(SDLK_UP) == input.isKeyHeld(SDLK_DOWN)) {
            player_->lookHorizontal();
        } else if (input.isKeyHeld(SDLK_UP)) {
            player_->lookUp();
        } else if (input.isKeyHeld(SDLK_DOWN)) {
            player_->lookDown();
        }

        // Player jump
        if (input.wasKeyPressed(SDLK_z)) {
            player_->startJump();
        } else if (input.wasKeyReleased(SDLK_z)) {
            player_->stopJump();
        }

        const units::MS current_time_ms = SDL_GetTicks();
        const units::MS elapsed_time = current_time_ms - last_update_time;
        update(std::min(elapsed_time, kMaxFrameTime));
        last_update_time = current_time_ms;

        draw(graphics);
        const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        const int delay = 1000 / kFps - elapsed_time_ms;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}

void Game::update(units::MS elapsed_time_ms) {
    player_->update(elapsed_time_ms, *map_);
    bat_->update(elapsed_time_ms, player_->center_x());

    if (bat_->damageRectangle().collidesWith(player_->damageRectangle())) {
        printf("Do damage to Quote!\n");
    }
}

void Game::draw(Graphics& graphics) {
    graphics.clear();
    map_->drawBackground(graphics);
    bat_->draw(graphics);
    player_->draw(graphics);
    map_->draw(graphics);
    graphics.flip();
}
