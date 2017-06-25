#include "game.h"

#include <cstdlib>
#include <ctime>
#include <SDL2/SDL.h>
#include "first_cave_bat.h"
#include "graphics.h"
#include "input.h"
#include "map.h"
#include "player.h"

namespace {
    const units::FPS kFps = 60;
    const units::MS kMaxFrameTime = 5 * 1000 / 60;
}

// static
units::Tile Game::kScreenWidth = 20;
units::Tile Game::kScreenHeight = 15;

Game::Game() {
    srand(static_cast<unsigned int>(time(NULL)));
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

    player_ = std::make_shared<Player>(graphics,
                                       units::tileToGame(kScreenWidth / 2),
                                       units::tileToGame(kScreenHeight / 2));
    damage_texts_.addDamageable(player_);

    bat_ = std::make_shared<FirstCaveBat>(graphics,
                                          units::tileToGame(7),
                                          units::tileToGame(kScreenHeight / 2 + 1));
    damage_texts_.addDamageable(bat_);

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

        // Player fire
        if (input.wasKeyPressed(SDLK_x)) {
            ParticleTools particle_tools = { particle_system_, graphics };
            player_->startFire(particle_tools);
        } else if (input.wasKeyReleased(SDLK_x)) {
            player_->stopFire();
        }

        // Player jump
        if (input.wasKeyPressed(SDLK_z)) {
            player_->startJump();
        } else if (input.wasKeyReleased(SDLK_z)) {
            player_->stopJump();
        }

        const units::MS current_time_ms = SDL_GetTicks();
        const units::MS elapsed_time = current_time_ms - last_update_time;
        update(std::min(elapsed_time, kMaxFrameTime), graphics);
        last_update_time = current_time_ms;

        draw(graphics);
        const units::MS elapsed_time_ms = SDL_GetTicks() - start_time_ms;
        const int delay = 1000 / kFps - elapsed_time_ms;
        if (delay > 0) {
            SDL_Delay(delay);
        }
    }
}

void Game::update(units::MS elapsed_time_ms,
                  Graphics& graphics)
{
    Timer::updateAll(elapsed_time_ms);
    damage_texts_.update(elapsed_time_ms);
    particle_system_.update(elapsed_time_ms);
    ParticleTools particle_tools = { particle_system_, graphics };
    player_->update(elapsed_time_ms, *map_, particle_tools);
    if (bat_) {
        if (!bat_->update(elapsed_time_ms, player_->center_x())) {
            bat_.reset();
        };
    }
    std::vector<std::shared_ptr<Projectile>> projectiles(player_->getProjectiles());
    for (std::shared_ptr<Projectile> projectile : projectiles) {
        if (bat_ && bat_->collisionRectangle().collidesWith(projectile->collisionRectangle())) {
            bat_->takeDamage(projectile->contactDamage());
            projectile->collideWithEnemy();
        }
    }
    if (bat_ && bat_->damageRectangle().collidesWith(player_->damageRectangle())) {
        player_->takeDamage(bat_->contactDamage());
    }
}

void Game::draw(Graphics& graphics) {
    graphics.clear();
    map_->drawBackground(graphics);
    if (bat_) {
        bat_->draw(graphics);
    }
    player_->draw(graphics);
    map_->draw(graphics);
    particle_system_.draw(graphics);
    damage_texts_.draw(graphics);
    player_->drawHUD(graphics);
    graphics.flip();
}
