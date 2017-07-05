#include "map.h"

#include "sprite.h"
#include "graphics.h"
#include "game.h"
#include "rectangle.h"

#include <memory>


Map* Map::createSlopeTestMap(Graphics& graphics)
{
    Map* map = new Map();

    map->backdrop_ = std::make_unique<FixedBackdrop>("bkBlue", graphics);
    const units::Tile num_rows = 15;
    const units::Tile num_cols = 20;
    map->tiles_ = std::vector<std::vector<Tile>>(
            num_rows, std::vector<Tile>(
                    num_cols, Tile()
            )
    );
    map->background_tiles_ = std::vector<std::vector<std::shared_ptr<Sprite>>>(
            num_rows, std::vector<std::shared_ptr<Sprite>>(
                    num_cols, std::shared_ptr<Sprite>()
            )
    );

    Tile wall_tile(
            tiles::TileType().set(tiles::WALL),
            std::make_shared<Sprite>(
                    graphics, "PrtCave",
                    units::tileToPixel(1),
                    0,
                    units::tileToPixel(1),
                    units::tileToPixel(1)));

    enum { LTT, LTS, RTS, RTT, LBT, LBS, RBS, RBT, NUM_SLOPES };
    Tile slope_tiles[NUM_SLOPES];
    for (int i = 0; i < NUM_SLOPES; ++i)
    {
        slope_tiles[i] = Tile(
                tiles::TileType()
                        .set(tiles::SLOPE)
                        .set(i / 2 % 2 == 0 ? tiles::LEFT_SLOPE : tiles::RIGHT_SLOPE)
                        .set(i / 4 == 0 ? tiles::TOP_SLOPE : tiles::BOTTOM_SLOPE)
                        .set((i + 1) / 2 % 2 == 0 ? tiles::TALL_SLOPE : tiles::SHORT_SLOPE),
                std::make_shared<Sprite>(
                        graphics,
                        "PrtCave",
                        units::tileToPixel(2 + i % 4),
                        units::tileToPixel(i / 4),
                        units::tileToPixel(1),
                        units::tileToPixel(1)));
    }


    units::Tile row = 11;
    for (units::Tile col = 0; col < num_cols; ++col)
    {
        map->tiles_[row][col] = wall_tile;
    }
    --row;
    units::Tile col = 0;
    map->tiles_[row][col++] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[LBT];
    map->tiles_[row][col++] = slope_tiles[RBT];
    map->tiles_[row][col++] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[LBS];
    ++col;
    map->tiles_[row][col++] = slope_tiles[RBS];
    map->tiles_[row][col++] = slope_tiles[RBT];
    map->tiles_[row][col++] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[LBT];
    map->tiles_[row][col++] = slope_tiles[LBS];
    map->tiles_[row][col++] = slope_tiles[RBS];
    map->tiles_[row][col++] = slope_tiles[RBT];
    map->tiles_[row][col] = wall_tile;
    map->tiles_[row-1][col++] = slope_tiles[RBS];
    map->tiles_[row][col] = wall_tile;
    map->tiles_[row-1][col++] = slope_tiles[RBT];
    map->tiles_[row-1][col++] = wall_tile;
    ++col;
    map->tiles_[row][col++] = slope_tiles[RBS];
    map->tiles_[row][col++] = wall_tile;

    col = 0;
    row -= 3;

    map->tiles_[row-1][col] = wall_tile;
    map->tiles_[row][col++] = wall_tile;
    map->tiles_[row-1][col] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[LTT];
    map->tiles_[row-1][col] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[LTS];
    map->tiles_[row-1][col] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[RTS];
    map->tiles_[row-1][col] = wall_tile;
    map->tiles_[row][col++] = slope_tiles[RTT];
    map->tiles_[row-1][col] = wall_tile;
    map->tiles_[row][col++] = wall_tile;

    return map;
}

// static
Map* Map::createTestMap(Graphics& graphics)
{
    Map* map = new Map();

    map->backdrop_ = std::make_unique<FixedBackdrop>("bkBlue", graphics);
    const units::Tile num_rows = 15;
    const units::Tile num_cols = 20;
    map->tiles_ = std::vector<std::vector<Tile>>(
            num_rows, std::vector<Tile>(
                    num_cols, Tile()
            )
    );
    map->background_tiles_ = std::vector<std::vector<std::shared_ptr<Sprite>>>(
            num_rows, std::vector<std::shared_ptr<Sprite>>(
                    num_cols, std::shared_ptr<Sprite>()
            )
    );

    std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(
            graphics, "PrtCave",
            units::tileToPixel(1),
            0,
            units::tileToPixel(1),
            units::tileToPixel(1));

    Tile tile(tiles::TileType().set(tiles::WALL), sprite);
    const units::Tile row = 11;
    for (units::Tile col = 0; col < num_cols; ++col)
    {
        map->tiles_[row][col] = tile;
    }
    map->tiles_[10][5] = tile;
    map->tiles_[9][4] = tile;
    map->tiles_[8][3] = tile;
    map->tiles_[7][2] = tile;
    map->tiles_[10][3] = tile;

    std::shared_ptr<Sprite> chain_top = std::make_shared<Sprite>(
            graphics, "PrtCave",
            units::tileToPixel(11),
            units::tileToPixel(2),
            units::tileToPixel(1),
            units::tileToPixel(1));
    std::shared_ptr<Sprite> chain_middle = std::make_shared<Sprite>(
            graphics, "PrtCave",
            units::tileToPixel(12),
            units::tileToPixel(2),
            units::tileToPixel(1),
            units::tileToPixel(1));
    std::shared_ptr<Sprite> chain_bottom = std::make_shared<Sprite>(
            graphics, "PrtCave",
            units::tileToPixel(13),
            units::tileToPixel(2),
            units::tileToPixel(1),
            units::tileToPixel(1));
    map->background_tiles_[8][2] = chain_top;
    map->background_tiles_[9][2] = chain_middle;
    map->background_tiles_[10][2] = chain_bottom;

    return map;
}

std::vector<CollisionTile> Map::getCollidingTiles(const Rectangle& rectangle) const
{
    const units::Tile first_row = units::gameToTile(rectangle.top());
    const units::Tile last_row = units::gameToTile(rectangle.bottom());
    const units::Tile first_col = units::gameToTile(rectangle.left());
    const units::Tile last_col = units::gameToTile(rectangle.right());
    std::vector<CollisionTile> collision_tiles;

    for (units::Tile row = first_row; row <= last_row; ++row)
    {
        for (units::Tile col = first_col; col <= last_col; ++col)
        {
            collision_tiles.push_back(CollisionTile(row,
                                                    col,
                                                    tiles_[row][col].tile_type));
        }
    }

    return collision_tiles;
}

void Map::drawBackground(Graphics& graphics) const
{
    backdrop_->draw(graphics);
    for (size_t row = 0; row < background_tiles_.size(); ++row)
    {
        for (size_t col = 0; col < background_tiles_[row].size(); ++col)
        {
            if (background_tiles_[row][col]) {
                background_tiles_[row][col]->draw(graphics,
                                                  units::tileToGame(col),
                                                  units::tileToGame(row));
            }
        }
    }
}

void Map::draw(Graphics& graphics) const
{
    for (size_t row = 0; row < tiles_.size(); ++row)
    {
        for (size_t col = 0; col < tiles_[row].size(); ++col)
        {
            if (tiles_[row][col].sprite) {
                tiles_[row][col].sprite->draw(graphics,
                                              units::tileToGame(col),
                                              units::tileToGame(row));
            }
        }
    }
}
