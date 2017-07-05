#include "map_collidable.h"

#include "accelerators.h"
#include "collision_rectangle.h"
#include "kinematics.h"
#include "map.h"

namespace
{
    struct CollisionInfo
    {
        units::Game position;
        tiles::TileType tile_type;
    };

    boost::optional<CollisionInfo>
    testMapCollision(const Map& map,
                     const Rectangle& rectangle,
                     sides::SideType direction,
                     const boost::optional<tiles::TileType>& maybe_ground_tile)
    {
        std::vector<CollisionTile> tiles(map.getCollidingTiles(rectangle, direction));
        for (auto tile : tiles)
        {
            const auto side = sides::opposite_side(direction);
            const auto perpendicular_position = sides::vertical(side)
                    ? rectangle.center_x()
                    : rectangle.center_y();
            const auto leading_position = rectangle.side(direction);
            const auto should_test_slopes = sides::vertical(side);

            const auto test_info = tile.testCollision(
                    side,
                    perpendicular_position,
                    leading_position,
                    should_test_slopes);

            if (test_info.is_colliding)
            {
                const CollisionInfo info = { test_info.position,
                                             tile.tile_type() };
                return info;
            }
            else if (maybe_ground_tile && direction == sides::BOTTOM_SIDE)
            {
                const auto tall_slope = tiles::TileType()
                        .set(tiles::SLOPE).set(tiles::TALL_SLOPE);

                if ((maybe_ground_tile->test(tiles::SLOPE) &&
                        tile.tile_type()[tiles::SLOPE]) ||
                        ((maybe_ground_tile->test(tiles::WALL) &&
                            (tall_slope & tile.tile_type()) == tall_slope)))
                {
                    const CollisionInfo info = { test_info.position,
                                                 tile.tile_type() };
                    return info;
                }
            }
        }
        return boost::none;
    }
}

void
MapCollidable::updateX(const CollisionRectangle& collision_rectangle,
                       const Accelerator& accelerator, Kinematics& kinematics_x,
                       const Kinematics& kinematics_y, units::MS elapsed_time_ms,
                       const Map& map)
{
    update(collision_rectangle,
           accelerator,
           kinematics_x,
           kinematics_y,
           elapsed_time_ms,
           map,
           boost::none,
           kinematics_x,
           X_AXIS);
}

void
MapCollidable::updateY(const CollisionRectangle& collision_rectangle,
                       const Accelerator& accelerator,
                       const Kinematics& kinematics_x,
                       Kinematics& kinematics_y,
                       units::MS elapsed_time_ms,
                       const Map& map,
                       const boost::optional<tiles::TileType>& maybe_ground_tile)
{
    update(collision_rectangle,
           accelerator,
           kinematics_x,
           kinematics_y,
           elapsed_time_ms,
           map,
           maybe_ground_tile,
           kinematics_y,
           Y_AXIS);
}

void
MapCollidable::update(const CollisionRectangle& collision_rectangle,
                      const Accelerator& accelerator,
                      const Kinematics& kinematics_x,
                      const Kinematics& kinematics_y,
                      units::MS elapsed_time_ms,
                      const Map& map,
                      const boost::optional<tiles::TileType>& maybe_ground_tile,
                      Kinematics& kinematics,
                      MapCollidable::AxisType axis)
{
    accelerator.updateVelocity(kinematics, elapsed_time_ms);

    const units::Game delta = kinematics.velocity * elapsed_time_ms;

    // Check collision in the direction of delta
    const auto direction = axis == X_AXIS
            ? (delta > 0.0f ? sides::RIGHT_SIDE : sides::LEFT_SIDE)
            : (delta > 0.0f ? sides::BOTTOM_SIDE : sides::TOP_SIDE);

    {
        auto maybe_info = testMapCollision(
                map,
                collision_rectangle.collision(
                        direction,
                        kinematics_x.position,
                        kinematics_y.position,
                        delta),
                direction,
                maybe_ground_tile);

        // React to collision
        if (maybe_info)
        {
            kinematics.position = maybe_info->position -
                    collision_rectangle.boundingBox().side(direction);
            onCollision(direction, true, maybe_info->tile_type);
        }
        else
        {
            kinematics.position += delta;
            onDelta(direction);
        }
    }

    // Check collision in other direction
    const auto opposite_direction = sides::opposite_side(direction);

    auto maybe_info = testMapCollision(
            map,
            collision_rectangle.collision(
                    opposite_direction,
                    kinematics_x.position,
                    kinematics_y.position,
                    0),
            opposite_direction,
            boost::none);

    if (maybe_info)
    {
        kinematics.position = maybe_info->position -
                collision_rectangle.boundingBox().side(opposite_direction);
        onCollision(opposite_direction, false, maybe_info->tile_type);
    }
}
