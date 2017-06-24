#include "polar_star.h"

#include <string>
#include "sprite.h"

namespace {
    const int kPolarStarIndex = 2;
    const units::Game kGunWidth = 3 * units::kHalfTile;
    const units::Game kGunHeight = 2 * units::kHalfTile;
    const std::string kSpritePath("content/Arms.bmp");

    const units::Tile kHorizontalOffset = 0;
    const units::Tile kUpOffset = 2;
    const units::Tile kDownOffset = 4;

    const units::Tile kLeftOffset = 0;
    const units::Tile kRightOffset = 1;
}

PolarStar::PolarStar(Graphics& graphics) {
    initializeSprites(graphics);
}

void PolarStar::draw(Graphics& graphics,
                     HorizontalFacing horizontal_facing,
                     VerticalFacing vertical_facing,
                     bool gun_up, units::Game x, units::Game y) {
    if (horizontal_facing == LEFT) {
        x -= units::kHalfTile;
    }
    if (vertical_facing == UP) {
        y -= units::kHalfTile / 2;
    } else if (vertical_facing == DOWN) {
        y += units::kHalfTile / 2;
    }
    if (gun_up) {
        y -= 2.0f;
    }
    sprite_map_[std::make_tuple(horizontal_facing, vertical_facing)]->draw(graphics, x, y);
}

void PolarStar::initializeSprites(Graphics& graphics) {
    ENUM_FOREACH(horizontal_facing, HORIZONTAL_FACING) {
        ENUM_FOREACH(vertical_facing, VERTICAL_FACING) {
            initializeSprite(graphics, std::make_tuple(
                    HorizontalFacing(horizontal_facing),
                    VerticalFacing(vertical_facing)));
        }
    }
};

void PolarStar::initializeSprite(Graphics& graphics, const SpriteState& sprite_state) {
    units::Tile tile_y = sprite_state.horizontal_facing() == LEFT
            ? kLeftOffset
            : kRightOffset;
    switch (sprite_state.vertical_facing()) {
        case HORIZONTAL:
            tile_y += kHorizontalOffset;
            break;
        case UP:
            tile_y += kUpOffset;
            break;
        case DOWN:
            tile_y += kDownOffset;
            break;
        case LAST_VERTICAL_FACING:
            break;
    }

    sprite_map_[sprite_state] = std::make_shared<Sprite>(
            graphics, kSpritePath,
            units::gameToPixel(kPolarStarIndex * kGunWidth),
            units::tileToPixel(tile_y),
            units::gameToPixel(kGunWidth),
            units::gameToPixel(kGunHeight));
};
