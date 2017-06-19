#include "first_cave_bat.h"
#include "animated_sprite.h"
#include "graphics.h"

namespace {
    const units::Frame kNumFlyFrames = 3;
    const units::FPS kFlyFps = 10;
}

FirstCaveBat::FirstCaveBat(Graphics& graphics, units::Game x, units::Game y)
    : x_(x),
      y_(y)
{
    sprite_ = std::make_shared<AnimatedSprite>(
            graphics, "content/NpcCemet.bmp",
            units::tileToPixel(2), units::tileToPixel(2),
            units::tileToPixel(1), units::tileToPixel(1),
            kFlyFps, kNumFlyFrames);
}

void FirstCaveBat::update(units::MS elapsed_time) {
    sprite_->update(elapsed_time);
}

void FirstCaveBat::draw(Graphics& graphics) const {
    sprite_->draw(graphics, x_, y_);
}
