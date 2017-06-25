#include "polar_star.h"

#include <string>
#include "map.h"
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

    // Projectile velocity
    const units::Velocity kProjectileSpeed = 0.6f;
    const units::Game kProjectileMaxOffset = 7 * units::kHalfTile;

    const units::Game kProjectileWidth = 4.0f;
}

PolarStar::PolarStar(Graphics& graphics) {
    initializeSprites(graphics);
}

void PolarStar::updateProjectiles(units::MS elapsed_time, const Map& map) {
    if (projectile_a_) {
        if (!projectile_a_->update(elapsed_time, map)) {
            projectile_a_.reset();
        }
    }
    if (projectile_b_) {
        if (!projectile_b_->update(elapsed_time, map)) {
            projectile_b_.reset();
        }
    }
}

void PolarStar::draw(Graphics& graphics,
                     HorizontalFacing horizontal_facing,
                     VerticalFacing vertical_facing,
                     bool gun_up,
                     units::Game player_x,
                     units::Game player_y) {

    units::Game x = gun_x(horizontal_facing, player_x);
    units::Game y = gun_y(vertical_facing, gun_up, player_y);
    sprite_map_[std::make_tuple(horizontal_facing, vertical_facing)]->draw(graphics, x, y);
    if (projectile_a_) {
        projectile_a_->draw(graphics);
    }
    if (projectile_b_) {
        projectile_b_->draw(graphics);
    }
}

units::Game PolarStar::gun_y(VerticalFacing vertical_facing,
                             bool gun_up,
                             units::Game player_y) const {

    units::Game gun_y = player_y;
    if (vertical_facing == UP) {
        gun_y -= units::kHalfTile / 2;
    } else if (vertical_facing == DOWN) {
        gun_y += units::kHalfTile / 2;
    }
    if (gun_up) {
        gun_y -= 2.0f;
    }
    return gun_y;
}

void PolarStar::startFire(units::Game player_x,
                          units::Game player_y,
                          HorizontalFacing horizontal_facing,
                          VerticalFacing vertical_facing,
                          bool gun_up) {

    if (projectile_a_ && projectile_b_) {
        return;
    }

    units::Game bullet_x = gun_x(horizontal_facing, player_x) - units::kHalfTile;
    units::Game bullet_y = gun_y(vertical_facing, gun_up, player_y) + - units::kHalfTile;
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
    if (!projectile_a_) {
        projectile_a_ = std::make_shared<Projectile>(
                vertical_facing == HORIZONTAL ? horizontal_projectile_
                                              : vertical_projectile_,
                horizontal_facing,
                vertical_facing,
                bullet_x,
                bullet_y
        );
    } else if (!projectile_b_) {
        projectile_b_ = std::make_shared<Projectile>(
                vertical_facing == HORIZONTAL ? horizontal_projectile_
                                              : vertical_projectile_,
                horizontal_facing,
                vertical_facing,
                bullet_x,
                bullet_y
        );
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
}

std::vector<std::shared_ptr<::Projectile>> PolarStar::getProjectiles() {
    std::vector<std::shared_ptr<::Projectile>> projectiles;
    if (projectile_a_) projectiles.push_back(projectile_a_);
    if (projectile_b_) projectiles.push_back(projectile_b_);
    return projectiles;
}

PolarStar::Projectile::Projectile(std::shared_ptr <Sprite> sprite,
                                  HorizontalFacing horizontal_direction,
                                  VerticalFacing vertical_direction,
                                  units::Game x, units::Game y)
: sprite_(sprite),
  horizontal_direction_(horizontal_direction),
  vertical_direction_(vertical_direction),
  x_(x),
  y_(y),
  offset_(0),
  alive_(true)
{
}

bool PolarStar::Projectile::update(units::MS elapsed_time, const Map& map) {
    offset_ += kProjectileSpeed * elapsed_time;
    std::vector<Map::CollisionTile> colliding_tiles(
            map.getCollidingTiles(collisionRectangle()));
    for (Map::CollisionTile tile : colliding_tiles) {
        if (tile.tile_type == Map::WALL_TILE) {
            return false;
        }
    }
    return alive_ && offset_ < kProjectileMaxOffset;
}

void PolarStar::Projectile::draw(Graphics& graphics) {
    sprite_->draw(graphics, getX(), getY());
}

Rectangle PolarStar::Projectile::collisionRectangle() const {
    const units::Game width = vertical_direction_ == HORIZONTAL
        ? units::tileToGame(1)
        : kProjectileWidth;
    const units::Game height = vertical_direction_ != HORIZONTAL
        ? units::tileToGame(1)
        : kProjectileWidth;
    return Rectangle(getX() + units::kHalfTile - width / 2,
                     getY() + units::kHalfTile - height / 2,
                     width,
                     height);
}

units::Game PolarStar::Projectile::getX() const {
    if (vertical_direction_ == HORIZONTAL) {
        return x_ + (horizontal_direction_ == LEFT ? -offset_ : offset_);
    } else {
        return x_;
    }
}

units::Game PolarStar::Projectile::getY() const {
    units::Game y = y_;
    switch (vertical_direction_) {
        case UP:
            y -= offset_;
            break;
        case DOWN:
            y += offset_;
            break;
        default:
            break;
    }
    return y;
}
