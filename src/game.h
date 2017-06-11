#ifndef GAME_H_
#define GAME_H_

#include <memory>

struct Player;
struct Graphics;
struct Map;

struct Game {
    Game();
    ~Game();

    static int kTileSize;

private:
    void eventLoop();
    void update(int elapsed_time_ms);
    void draw(Graphics& graphics);

    std::unique_ptr<Player> player_;
    std::unique_ptr<Map> map_;
};

#endif // GAME_H_
