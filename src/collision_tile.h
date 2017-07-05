#ifndef COLLISION_TILE_H_
#define COLLISION_TILE_H_

#include <boost/optional.hpp>
#include "side_type.h"
#include "tile_type.h"
#include "units.h"

struct CollisionTile
{
    CollisionTile(units::Tile row,
                  units::Tile col,
                  tiles::TileType tile_type) :
            row_(row),
            col_(col),
            tile_type_(tile_type)
    {
    }

    struct TestCollisionInfo
    {
        bool is_colliding;
        units::Game position;
    };

    TestCollisionInfo testCollision(sides::SideType side,
                                    units::Game perpendicular_position,
                                    units::Game leading_position,
                                    bool should_test_slopes) const;

    tiles::TileType tile_type() const
    {
        return tile_type_;
    }

private:

    units::Tile row_, col_;
    tiles::TileType tile_type_;
};

#endif // COLLISION_TILE_H_
