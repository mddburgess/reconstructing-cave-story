#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "damage_texts.h"
#include "head_bump_particle.h"
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
    void update(units::MS elapsed_time_ms);
    void draw(Graphics& graphics);

    std::shared_ptr<Player> player_;
    std::shared_ptr<FirstCaveBat> bat_;
    std::unique_ptr<Map> map_;
    std::unique_ptr<HeadBumpParticle> particle_;
    DamageTexts damage_texts_;

};

#endif // GAME_H_
