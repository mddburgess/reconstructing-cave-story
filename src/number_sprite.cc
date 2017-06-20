#include "number_sprite.h"

#include <cassert>
#include "sprite.h"

namespace {
    const std::string kSpritePath = "content/TextBox.bmp";
    const units::Game kSourceY = 7 * units::kHalfTile;
    const units::Game kSourceWidth = units::kHalfTile;
    const units::Game kSourceHeight = units::kHalfTile;
}

NumberSprite::NumberSprite(Graphics& graphics, int number, int num_digits)
    : padding_(0.0f)
{
    assert(number >= 0);

    int digit_count = 0;
    do {
        const int digit = number % 10;
        reversed_digits_.push_back(std::make_shared<Sprite>(
                graphics, kSpritePath,
                units::gameToPixel(digit * units::kHalfTile),
                units::gameToPixel(kSourceY),
                units::gameToPixel(kSourceWidth),
                units::gameToPixel(kSourceHeight)));
        number /= 10;
        ++digit_count;
    } while (number != 0);

    assert(num_digits == 0 || num_digits >= digit_count);
    padding_ = num_digits == 0 ? 0.0f : units::kHalfTile * (num_digits - digit_count);
}

void NumberSprite::draw(Graphics& graphics, units::Game x, units::Game y) {
    for (size_t i = 0; i < reversed_digits_.size(); ++i) {
        const units::Game offset = units::kHalfTile * (reversed_digits_.size() - 1 - i);
        reversed_digits_[i]->draw(graphics, x + offset + padding_, y);
    }
}
