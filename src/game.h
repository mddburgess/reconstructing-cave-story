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

    static int kTileSize;
    static int kScreenWidth;
    static int kScreenHeight;

    template <typename T>
    static T gameUnitsToPixels(T gameUnits);

private:
    void eventLoop();
    void update(units::MS elapsed_time_ms);
    void draw(Graphics& graphics);

    std::unique_ptr<Player> player_;
    std::unique_ptr<Map> map_;
};

template <typename T>
T Game::gameUnitsToPixels(T gameUnits) {
    return gameUnits * Game::kTileSize / 32;
}

#endif // GAME_H_
