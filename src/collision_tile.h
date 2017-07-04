#ifndef COLLISION_TILE_H_
#define COLLISION_TILE_H_

#include "tile_type.h"
#include "units.h"

struct CollisionTile
{
    CollisionTile(units::Tile row, units::Tile col, tiles::TileType tile_type) :
            row(row),
            col(col),
            tile_type(tile_type)
    {
    }

    units::Tile row, col;
    tiles::TileType tile_type;
};

#endif // COLLISION_TILE_H_
