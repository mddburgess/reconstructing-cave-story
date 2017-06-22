#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include <memory>
#include <vector>
#include "units.h"

struct Graphics;
struct Sprite;

struct NumberSprite {
    static NumberSprite HUDNumber(Graphics& graphics, int number, int num_digits) {
        return NumberSprite(graphics, number, num_digits, WHITE, NONE);
    }

    static NumberSprite DamageNumber(Graphics& graphics, int number) {
        return NumberSprite(graphics, number, 0, RED, MINUS);
    }

    static NumberSprite ExperienceNumber(Graphics& graphics, int number) {
        return NumberSprite(graphics, number, 0, WHITE, PLUS);
    }

    void draw(Graphics& graphics, units::Game x, units::Game y);

    units::Game width() const { return units::kHalfTile * reversed_sprites_.size(); }
    units::Game height() const { return units::kHalfTile; }

private:
    enum ColourType {
        RED,
        WHITE
    };
    enum OperatorType {
        PLUS,
        MINUS,
        NONE
    };
    NumberSprite(Graphics& graphics, int number, int num_digits,
                 ColourType colour, OperatorType op);

    units::Game padding_;
    std::vector<std::shared_ptr<Sprite>> reversed_sprites_;
};

#endif // NUMBER_SPRITE_H_