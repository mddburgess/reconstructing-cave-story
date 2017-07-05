#include "collision_tile.h"

using namespace tiles;

namespace
{
    inline float get_slope(const TileType& tile_type)
    {
        const auto right_top = TileType().set(RIGHT_SLOPE).set(TOP_SLOPE);
        const auto left_bottom = TileType().set(LEFT_SLOPE).set(BOTTOM_SLOPE);
        const auto is_positive =
                ((right_top & tile_type) == right_top) ||
                ((left_bottom & tile_type) == left_bottom);
        return is_positive ? 0.5f : -0.5f;
    }

    inline units::Game get_offset(const TileType& tile_type)
    {
        {
            const auto left_top_tall =
                    TileType().set(LEFT_SLOPE).set(TOP_SLOPE).set(TALL_SLOPE);
            const auto right_bottom_short =
                    TileType().set(RIGHT_SLOPE).set(BOTTOM_SLOPE).set(SHORT_SLOPE);
            if ((left_top_tall & tile_type) == left_top_tall ||
                    (right_bottom_short & tile_type) == right_bottom_short)
            {
                return units::tileToGame(1);
            }
        }

        const auto left_bottom_tall =
                TileType().set(LEFT_SLOPE).set(BOTTOM_SLOPE).set(TALL_SLOPE);
        const auto right_top_short =
                TileType().set(RIGHT_SLOPE).set(TOP_SLOPE).set(SHORT_SLOPE);
        if ((left_bottom_tall & tile_type) == left_bottom_tall ||
                (right_top_short & tile_type) == right_top_short)
        {
            return 0.0f;
        }

        return units::kHalfTile;
    }
};

boost::optional<units::Game>
CollisionTile::testCollision(sides::SideType side,
                             units::Game perpendicular_position,
                             units::Game leading_position,
                             bool should_test_slopes) const
{
    if (tile_type_[WALL])
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
    else if (should_test_slopes
             && tile_type_[SLOPE]
             && !tile_type_[slope_flag_from_side(side)])
    {
        const auto row = units::tileToGame(row_);
        const auto col = units::tileToGame(col_);
        const auto slope = get_slope(tile_type_);
        const auto offset = get_offset(tile_type_);
        const auto calculated_position = sides::vertical(side)
                ? slope * (perpendicular_position - col) + offset + row
                : (perpendicular_position - row - offset) / slope + col;

        const auto is_colliding = is_max(side)
                ? leading_position <= calculated_position
                : leading_position >= calculated_position;

        if (is_colliding)
        {
            return calculated_position;
        }
    }

    return boost::none;
}
