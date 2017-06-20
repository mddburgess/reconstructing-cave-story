#include "first_cave_bat.h"
#include "animated_sprite.h"
#include "graphics.h"


namespace {
    const units::Frame kNumFlyFrames = 3;
    const units::FPS kFlyFps = 13;

    const units::AngularVelocity kAngularVelocity = 120.0f / 1000.0f;

    const units::Game kFlightAmplitude = 5 * units::kHalfTile;
}

FirstCaveBat::FirstCaveBat(Graphics& graphics, units::Game x, units::Game y)
    : center_y_(y),
      x_(x),
      y_(y),
      facing_(RIGHT),
      flight_angle_(0.0f)
{
    initializeSprites(graphics);
}

void FirstCaveBat::update(units::MS elapsed_time, units::Game player_x) {
    flight_angle_ += kAngularVelocity * elapsed_time;
    facing_ = x_ + units::kHalfTile > player_x ? LEFT : RIGHT;

    y_ = center_y_ + kFlightAmplitude * units::Game(
            std::sin(units::degreesToRadians(flight_angle_)));

    sprites_[getSpriteState()]->update(elapsed_time);
}

void FirstCaveBat::draw(Graphics& graphics) const {
    sprites_.at(getSpriteState())->draw(graphics, x_, y_);
}

void FirstCaveBat::initializeSprites(Graphics& graphics) {
    for (int facing = FIRST_FACING; facing < LAST_FACING; ++facing) {
        initializeSprite(graphics, SpriteState(Facing(facing)));
    }
}

void FirstCaveBat::initializeSprite(Graphics& graphics, const SpriteState& sprite_state) {
    units::Tile tile_y = sprite_state.facing == RIGHT ? 3 : 2;
    sprites_[sprite_state] = std::make_shared<AnimatedSprite>(
            graphics, "content/NpcCemet.bmp",
            units::tileToPixel(2), units::tileToPixel(tile_y),
            units::tileToPixel(1), units::tileToPixel(1),
            kFlyFps, kNumFlyFrames);
}

FirstCaveBat::SpriteState FirstCaveBat::getSpriteState() const {
    return SpriteState(facing_);
}
