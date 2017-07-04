#include "map_collidable.h"

#include "accelerators.h"
#include "collision_rectangle.h"
#include "kinematics.h"
#include "map.h"

namespace
{
    boost::optional<units::Game> testMapCollision(const Map& map,
                                                  const Rectangle& rectangle,
                                                  sides::SideType direction)
    {
        std::vector<CollisionTile> tiles(map.getCollidingTiles(rectangle));
        for (auto tile : tiles)
        {
            const auto side = sides::opposite_side(direction);
            const auto position = sides::vertical(side)
                    ? rectangle.center_x()
                    : rectangle.center_y();

            const auto maybe_position = tile.testCollision(side, position);
            if (maybe_position)
            {
                return maybe_position;
            }
        }
        return boost::none;
    }
}

void MapCollidable::updateX(const CollisionRectangle& collision_rectangle,
                            const Accelerator& accelerator,
                            Kinematics& kinematics_x,
                            const Kinematics& kinematics_y,
                            units::MS elapsed_time_ms,
                            const Map& map)
{
    update(collision_rectangle,
           accelerator,
           kinematics_x,
           kinematics_y,
           elapsed_time_ms,
           map,
           kinematics_x,
           X_AXIS);
}

void MapCollidable::updateY(const CollisionRectangle& collision_rectangle,
                            const Accelerator& accelerator,
                            const Kinematics& kinematics_x,
                            Kinematics& kinematics_y,
                            units::MS elapsed_time_ms,
                            const Map& map)
{
    update(collision_rectangle,
           accelerator,
           kinematics_x,
           kinematics_y,
           elapsed_time_ms,
           map,
           kinematics_y,
           Y_AXIS);
}

void MapCollidable::update(const CollisionRectangle& collision_rectangle,
                           const Accelerator& accelerator,
                           const Kinematics& kinematics_x,
                           const Kinematics& kinematics_y,
                           units::MS elapsed_time_ms,
                           const Map& map,
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
        auto maybe_position = testMapCollision(
                map,
                collision_rectangle.collision(
                        direction,
                        kinematics_x.position,
                        kinematics_y.position,
                        delta),
                direction);

        // React to collision
        if (maybe_position)
        {
            kinematics.position = *maybe_position -
                    collision_rectangle.boundingBox().side(direction);
            onCollision(direction, true);
        } else
        {
            kinematics.position += delta;
            onDelta(direction);
        }
    }

    // Check collision in other direction
    const auto opposite_direction = sides::opposite_side(direction);

    auto maybe_position = testMapCollision(
            map,
            collision_rectangle.collision(
                    opposite_direction,
                    kinematics_x.position,
                    kinematics_y.position,
                    0),
            opposite_direction);

    if (maybe_position)
    {
        kinematics.position = *maybe_position -
                collision_rectangle.boundingBox().side(opposite_direction);
        onCollision(opposite_direction, false);
    }
}
