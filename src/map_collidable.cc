#include "map_collidable.h"

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
        std::vector<Map::CollisionTile> tiles(map.getCollidingTiles(rectangle));
        for (Map::CollisionTile tile : tiles)
        {
            if (tile.tile_type == Map::WALL_TILE)
            {
                info = { true, tile.row, tile.col };
                break;
            }
        }
        return info;
    }
}

void MapCollidable::updateX(const CollisionRectangle& collision_rectangle,
                            Kinematics& kinematics_x,
                            const Kinematics& kinematics_y,
                            units::MS elapsed_time_ms,
                            const Map& map)
{
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
            onCollision(MapCollidable::RIGHT_SIDE, true);
        }
        else
        {
            kinematics_x.position += delta;
            onDelta(MapCollidable::RIGHT_SIDE);
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
            onCollision(MapCollidable::LEFT_SIDE, false);
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
            onCollision(MapCollidable::LEFT_SIDE, true);
        }
        else
        {
            kinematics_x.position += delta;
            onDelta(MapCollidable::LEFT_SIDE);
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
            onCollision(MapCollidable::RIGHT_SIDE, false);
        }
    }

}

void MapCollidable::updateY(const CollisionRectangle& collision_rectangle,
                            const Kinematics& kinematics_x,
                            Kinematics& kinematics_y,
                            units::MS elapsed_time_ms,
                            const Map& map)
{
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
            onCollision(MapCollidable::BOTTOM_SIDE, true);
        }
        else
        {
            kinematics_y.position += delta;
            onDelta(MapCollidable::BOTTOM_SIDE);
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
            onCollision(MapCollidable::TOP_SIDE, false);
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
            onCollision(MapCollidable::TOP_SIDE, true);
        }
        else
        {
            kinematics_y.position += delta;
            onDelta(MapCollidable::TOP_SIDE);
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
            onCollision(MapCollidable::BOTTOM_SIDE, false);
        }
    }

}
