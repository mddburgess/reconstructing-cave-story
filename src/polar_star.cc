#include "polar_star.h"

#include <string>
#include "sprite.h"

namespace {
    const int kPolarStarIndex = 2;
    const units::Game kGunWidth = 3 * units::kHalfTile;
    const units::Game kGunHeight = 2 * units::kHalfTile;
    const std::string kSpritePath("Arms");

    const units::Tile kHorizontalOffset = 0;
    const units::Tile kUpOffset = 2;
    const units::Tile kDownOffset = 4;

    const units::Tile kLeftOffset = 0;
    const units::Tile kRightOffset = 1;
    
    // Nozzle offsets
    const units::Game kNozzleHorizontalY = 23;
    const units::Game kNozzleHorizontalLeftX = 10;
    const units::Game kNozzleHorizontalRightX = 38;

    const units::Game kNozzleUpY = 4;
    const units::Game kNozzleUpLeftX = 27;
    const units::Game kNozzleUpRightX = 21;

    const units::Game kNozzleDownY = 28;
    const units::Game kNozzleDownLeftX = 29;
    const units::Game kNozzleDownRightX = 19;

    // Projectile sprite
    const units::Tile kProjectileSourceY = 2;
    const units::Tile kHorizontalProjectileSourceX = 8;
    const units::Tile kVerticalProjectileSourceX = 9;
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

    units::Game bullet_x = x - units::kHalfTile;
    units::Game bullet_y = y + - units::kHalfTile;
    switch (vertical_facing) {
        case HORIZONTAL:
            bullet_y += kNozzleHorizontalY;
            bullet_x += horizontal_facing == LEFT
                ? kNozzleHorizontalLeftX
                : kNozzleHorizontalRightX;
            break;
        case UP:
            bullet_y += kNozzleUpY;
            bullet_x += horizontal_facing == LEFT
                ? kNozzleDownLeftX
                : kNozzleDownRightX;
            break;
        case DOWN:
            bullet_y += kNozzleDownY;
            bullet_x += horizontal_facing == LEFT
                ? kNozzleUpLeftX
                : kNozzleUpRightX;
            break;
        default:
            break;
    }
    if (vertical_facing == HORIZONTAL) {
        horizontal_projectile_->draw(graphics, bullet_x, bullet_y);
    } else {
        vertical_projectile_->draw(graphics, bullet_x, bullet_y);
    }
}

void PolarStar::initializeSprites(Graphics& graphics) {
    ENUM_FOREACH(horizontal_facing, HORIZONTAL_FACING) {
        ENUM_FOREACH(vertical_facing, VERTICAL_FACING) {
            initializeSprite(graphics, std::make_tuple(
                    HorizontalFacing(horizontal_facing),
                    VerticalFacing(vertical_facing)));
        }
    }
    horizontal_projectile_ = std::make_shared<Sprite>(
            graphics, "Bullet",
            units::tileToPixel(kHorizontalProjectileSourceX),
            units::tileToPixel(kProjectileSourceY),
            units::tileToPixel(1), units::tileToPixel(1));
    vertical_projectile_ = std::make_shared<Sprite>(
            graphics, "Bullet",
            units::tileToPixel(kVerticalProjectileSourceX),
            units::tileToPixel(kProjectileSourceY),
            units::tileToPixel(1), units::tileToPixel(1));
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
