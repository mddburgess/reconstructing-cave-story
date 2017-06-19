#include "first_cave_bat.h"
#include "animated_sprite.h"
#include "graphics.h"

namespace {
    const units::Frame kNumFlyFrames = 3;
    const units::FPS kFlyFps = 13;

    const units::AngularVelocity kAngularVelocity = 120.0f / 1000.0f;
}

FirstCaveBat::FirstCaveBat(Graphics& graphics, units::Game x, units::Game y)
    : x_(x),
      y_(y),
      flight_angle_(0.0f)
{
    sprite_ = std::make_shared<AnimatedSprite>(
            graphics, "content/NpcCemet.bmp",
            units::tileToPixel(2), units::tileToPixel(2),
            units::tileToPixel(1), units::tileToPixel(1),
            kFlyFps, kNumFlyFrames);
}

void FirstCaveBat::update(units::MS elapsed_time) {
    flight_angle_ += kAngularVelocity * elapsed_time;
    sprite_->update(elapsed_time);
}

void FirstCaveBat::draw(Graphics& graphics) const {
    const units::Game y = y_ + units::tileToGame(5) / 2.0f * std::sin(units::degreesToRadians(flight_angle_));
    sprite_->draw(graphics, x_, y);
}
