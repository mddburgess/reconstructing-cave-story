#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "damage_texts.h"
#include "particle_system.h"
#include "units.h"

struct Player;
struct Graphics;
struct Map;
struct FirstCaveBat;

struct Game {
    Game();
    ~Game();

    static units::Tile kScreenWidth;
    static units::Tile kScreenHeight;

private:
    void eventLoop();
    void update(units::MS elapsed_time_ms, Graphics& graphics);
    void draw(Graphics& graphics);

    std::shared_ptr<Player> player_;
    std::shared_ptr<FirstCaveBat> bat_;
    std::unique_ptr<Map> map_;
    ParticleSystem particle_system_;
    DamageTexts damage_texts_;

};

#endif // GAME_H_
