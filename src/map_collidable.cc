#include "map_collidable.h"

#include "accelerators.h"
#include "collision_rectangle.h"
#include "kinematics.h"
#include "map.h"

namespace
{
    struct CollisionInfo
    {
        bool collided;
        units::Tile row, col;
    };

    CollisionInfo getWallCollisionInfo(const Map& map, const Rectangle& rectangle)
    {
        CollisionInfo info = { false, 0, 0 };
        std::vector<CollisionTile> tiles(map.getCollidingTiles(rectangle));
        for (auto tile : tiles)
        {
            if (tile.tile_type == tiles::WALL_TILE)
            {
                info = { true, tile.row, tile.col };
                break;
            }
        }
        return info;
    }
}

void MapCollidable::updateX(const CollisionRectangle& collision_rectangle,
                            const Accelerator& accelerator,
                            Kinematics& kinematics_x,
                            const Kinematics& kinematics_y,
                            units::MS elapsed_time_ms,
                            const Map& map)
{
    accelerator.updateVelocity(kinematics_x, elapsed_time_ms);

    // Calculate delta
    const units::Game delta = kinematics_x.velocity * elapsed_time_ms;
    if (delta > 0.0f)
    {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map,
                collision_rectangle.rightCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        delta));

        // React to collision
        if (info.collided)
        {
            kinematics_x.position = units::tileToGame(info.col)
                                     - collision_rectangle.boundingBox().right();
            onCollision(sides::RIGHT_SIDE, true);
        }
        else
        {
            kinematics_x.position += delta;
            onDelta(sides::RIGHT_SIDE);
        }

        // Check collision in other direction
        info = getWallCollisionInfo(map,
                collision_rectangle.leftCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        0));

        if (info.collided)
        {
            kinematics_x.position = units::tileToGame(info.col + 1)
                                     - collision_rectangle.boundingBox().left();
            onCollision(sides::LEFT_SIDE, false);
        }
    }
    else
    {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map,
                collision_rectangle.leftCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        delta));

        // React to collision
        if (info.collided)
        {
            kinematics_x.position = units::tileToGame(info.col + 1)
                                     - collision_rectangle.boundingBox().left();
            onCollision(sides::LEFT_SIDE, true);
        }
        else
        {
            kinematics_x.position += delta;
            onDelta(sides::LEFT_SIDE);
        }

        // Check collision in other direction
        info = getWallCollisionInfo(map,
                collision_rectangle.rightCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        0));

        if (info.collided)
        {
            kinematics_x.position = units::tileToGame(info.col)
                                     - collision_rectangle.boundingBox().right();
            onCollision(sides::RIGHT_SIDE, false);
        }
    }

}

void MapCollidable::updateY(const CollisionRectangle& collision_rectangle,
                            const Accelerator& accelerator,
                            const Kinematics& kinematics_x,
                            Kinematics& kinematics_y,
                            units::MS elapsed_time_ms,
                            const Map& map)
{
    accelerator.updateVelocity(kinematics_y, elapsed_time_ms);

    // Calculate delta
    const units::Game delta = static_cast<units::Game>(round(kinematics_y.velocity * elapsed_time_ms));
    if (delta > 0.0f)
    {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map,
                collision_rectangle.bottomCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        delta));

        // React to collision
        if (info.collided)
        {
            kinematics_y.position = units::tileToGame(info.row)
                                     - collision_rectangle.boundingBox().bottom();
            onCollision(sides::BOTTOM_SIDE, true);
        }
        else
        {
            kinematics_y.position += delta;
            onDelta(sides::BOTTOM_SIDE);
        }

        // Check collision in other direction
        info = getWallCollisionInfo(map,
                collision_rectangle.topCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        0));

        if (info.collided)
        {
            kinematics_y.position = units::tileToGame(info.row + 1)
                                     - collision_rectangle.boundingBox().top();
            onCollision(sides::TOP_SIDE, false);
        }
    }
    else
    {
        // Check collision in the direction of delta
        CollisionInfo info = getWallCollisionInfo(map,
                collision_rectangle.topCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        delta));

        // React to collision
        if (info.collided)
        {
            kinematics_y.position = units::tileToGame(info.row + 1)
                                     - collision_rectangle.boundingBox().top();
            onCollision(sides::TOP_SIDE, true);
        }
        else
        {
            kinematics_y.position += delta;
            onDelta(sides::TOP_SIDE);
        }

        // Check collision in other direction
        info = getWallCollisionInfo(map,
                collision_rectangle.bottomCollision(
                        kinematics_x.position,
                        kinematics_y.position,
                        0));

        if (info.collided)
        {
            kinematics_y.position = units::tileToGame(info.row) - collision_rectangle.boundingBox().bottom();
            onCollision(sides::BOTTOM_SIDE, false);
        }
    }

}
