#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "units.h"

struct Player;
struct Graphics;
struct Map;

struct Game {
    Game();
    ~Game();

    static units::Tile kScreenWidth;
    static units::Tile kScreenHeight;

private:
    void eventLoop();
    void update(units::MS elapsed_time_ms);
    void draw(Graphics& graphics);

    std::unique_ptr<Player> player_;
    std::unique_ptr<Map> map_;
};

#endif // GAME_H_
