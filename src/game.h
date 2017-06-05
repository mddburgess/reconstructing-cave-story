#ifndef GAME_H_
#define GAME_H_

#include <memory>

struct Sprite;
struct Graphics;

struct Game {
    Game();
    ~Game();

private:
    void eventLoop();
    void update();
    void draw(Graphics& graphics);

    std::unique_ptr<Sprite> sprite_;
};

#endif // GAME_H_
