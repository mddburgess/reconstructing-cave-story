#include "number_sprite.h"
#include "sprite.h"

NumberSprite::NumberSprite(Graphics& graphics, int number) {
    sprite_ = std::make_shared<Sprite>(
            graphics, "content/TextBox.bmp",
            units::gameToPixel(number * units::kHalfTile),
            units::gameToPixel(7 * units::kHalfTile),
            units::gameToPixel(units::kHalfTile),
            units::gameToPixel(units::kHalfTile));
}

void NumberSprite::draw(Graphics& graphics, units::Game x, units::Game y) {
    sprite_->draw(graphics, x, y);
}
