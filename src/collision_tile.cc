#include "collision_tile.h"

boost::optional<units::Game> CollisionTile::testCollision(sides::SideType side,
                                                          units::Game) const
{
    if (tile_type_ == tiles::WALL_TILE)
    {
        switch (side)
        {
            case sides::TOP_SIDE:
                return units::tileToGame(row_);

            case sides::BOTTOM_SIDE:
                return units::tileToGame(row_ + 1);

            case sides::LEFT_SIDE:
                return units::tileToGame(col_);

            case sides::RIGHT_SIDE:
                return units::tileToGame(col_ + 1);
        }

    }
    return boost::none;
}
