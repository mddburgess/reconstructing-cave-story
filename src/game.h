#ifndef GAME_H_
#define GAME_H_

#include <memory>

struct AnimatedSprite;
struct Graphics;

struct Game {
    Game();
    ~Game();

    static int kTileSize;

private:
    void eventLoop();
    void update(int elapsed_time_ms);
    void draw(Graphics& graphics);

    std::unique_ptr<AnimatedSprite> sprite_;
};

#endif // GAME_H_
