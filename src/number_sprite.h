#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include <memory>
#include "units.h"

struct Graphics;
struct Sprite;

struct NumberSprite {
    NumberSprite(Graphics& graphics, int number);

    void draw(Graphics& graphics, units::Game x, units::Game y);

private:
    std::shared_ptr<Sprite> sprite_;
};

#endif // NUMBER_SPRITE_H_
