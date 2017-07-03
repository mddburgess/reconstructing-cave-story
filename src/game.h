#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "damage_texts.h"
#include "particle_system.h"
#include "pickups.h"
#include "units.h"

struct FirstCaveBat;
struct Graphics;
struct GunExperienceHUD;
struct Map;
struct Player;

struct Game
{
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
    ParticleSystem front_particle_system_, entity_particle_system_;
    DamageTexts damage_texts_;
    Pickups pickups_;
};

#endif // GAME_H_
